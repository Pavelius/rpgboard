#include "main.h"
#include "draw.h"

using namespace draw;

namespace {
struct focusable_element {
	int					id;
	rect				rc;
	operator bool() const { return id != 0; }
};
struct parami {
	int					origin;
	int					maximum;
	int					perpage;
	void correct() {
		if(origin + perpage > maximum)
			origin = maximum - perpage;
		if(origin < 0)
			origin = 0;
	}
};
}
static focusable_element elements[96];
static focusable_element* render_control;
static int				current_focus;
static bool				break_modal;
static int				break_result;
static point			camera;
static point			camera_drag;
static color			color_friendly = color::create(32, 255, 32);
static color			color_hostile = color::create(255, 32, 32);
static drawable*		hotobject;
static point			hotcamera;
static rect				last_window = {0, 0, 900, 600};
static point			tooltips_point;
static short			tooltips_width;
static char				tooltips_text[4096];
static short unsigned	special_hilite_index;
extern rect				sys_static_area;
callback				draw::domodal;
static point			half_grid = {grid_size / 2, grid_size / 2};
const int				size = 50;
const auto				dialog_w = 640;
const auto				dialog_h = 480;
const unsigned char		opacity_button = 220;
const unsigned char		opacity_disabled = 50;
const unsigned char		opacity_hilighted = 200;
const int				tips_width = 200;
const int				window_width = 320;
const int				gui_border = 8;
const int				gui_padding = 4;
static bool				align_grid = true;
static int				focus_stack[16];
static int				focus_level;
static int				focus_pressed;
static variant			current_info;

extern "C" void scale2x(void* void_dst, unsigned dst_slice, const void* void_src, unsigned src_slice, unsigned width, unsigned height);

static const sprite* gres(resource_s id) {
	auto& e = bsdata<resourcei>::elements[id];
	if(!e.data) {
		if(!id)
			return 0;
		char temp[260]; stringbuilder sb(temp);
		e.geturl(sb);
		e.data = (sprite*)loadb(temp);
		if(!e.data)
			e.error = true;
	}
	return (sprite*)e.data;
}

static rect gridrect(point v) {
	return {v.x, v.y, v.x + grid_size, v.y + grid_size};
}

static void set_focus_callback() {
	auto id = getnext(draw::getfocus(), hot.param);
	if(id)
		setfocus(id, true);
}

static void setfocus_callback() {
	current_focus = hot.param;
}

static void openform() {
	if((unsigned)focus_level < sizeof(focus_stack) / sizeof(focus_stack[0]))
		focus_stack[focus_level] = current_focus;
	focus_level++;
	current_focus = 0;
	focus_pressed = 0;
	hot.key = 0;
}

static void closeform() {
	if(focus_level > 0) {
		focus_level--;
		if((unsigned)focus_level < sizeof(focus_stack) / sizeof(focus_stack[0]))
			setfocus(focus_stack[focus_level]);
	}
	hot.key = 0;
}

static focusable_element* getby(int id) {
	if(!id)
		return 0;
	for(auto& e : elements) {
		if(!e)
			return 0;
		if(e.id == id)
			return &e;
	}
	return 0;
}

static focusable_element* getfirst() {
	for(auto& e : elements) {
		if(!e)
			return 0;
		return &e;
	}
	return 0;
}

static focusable_element* getlast() {
	auto p = elements;
	for(auto& e : elements) {
		if(!e)
			break;
		p = &e;
	}
	return p;
}

void draw::addelement(int id, const rect& rc) {
	if(!render_control
		|| render_control >= elements + sizeof(elements) / sizeof(elements[0]) - 1)
		render_control = elements;
	render_control[0].id = id;
	render_control[0].rc = rc;
	render_control[1].id = 0;
	render_control++;
}

int draw::getnext(int id, int key) {
	if(!key)
		return id;
	auto pc = getby(id);
	if(!pc)
		pc = getfirst();
	if(!pc)
		return 0;
	auto pe = pc;
	auto pl = getlast();
	int inc = 1;
	if(key == KeyLeft || key == KeyUp || key == (KeyTab | Shift))
		inc = -1;
	while(true) {
		pc += inc;
		if(pc > pl)
			pc = elements;
		else if(pc < elements)
			pc = pl;
		if(pe == pc)
			return pe->id;
		switch(key) {
		case KeyRight:
			if(pe->rc.y1 >= pc->rc.y1
				&& pe->rc.y1 <= pc->rc.y2
				&& pe->rc.x1 < pc->rc.x1)
				return pc->id;
			break;
		case KeyLeft:
			if(pe->rc.y1 >= pc->rc.y1
				&& pe->rc.y1 <= pc->rc.y2
				&& pe->rc.x1 > pc->rc.x1)
				return pc->id;
			break;
		case KeyDown:
			if(pc->rc.y1 >= pe->rc.y2)
				return pc->id;
			break;
		case KeyUp:
			if(pc->rc.y2 <= pe->rc.y1)
				return pc->id;
			break;
		default:
			return pc->id;
		}
	}
}

void draw::setfocus(int id, bool instant) {
	if(instant)
		current_focus = id;
	else if(current_focus != id)
		execute(setfocus_callback, id);
}

int draw::getfocus() {
	return current_focus;
}

void draw::execute(void(*proc)(), int param, const void* object) {
	domodal = proc;
	hot.key = 0;
	hot.param = param;
	hot.object = object;
}

void draw::breakmodal(int result) {
	break_modal = true;
	break_result = result;
	hot.key = 0;
	hot.param = 0;
}

void draw::buttoncancel() {
	breakmodal(0);
}

void draw::buttonok() {
	breakmodal(1);
}

void draw::buttonparam() {
	breakmodal(hot.param);
}

int draw::getresult() {
	return break_result;
}

static bool window(rect rc, bool hilight = true, bool pressable = false, int border = 0) {
	if(border == 0)
		border = gui_border;
	rc.offset(-border, -border);
	auto op = opacity_button;
	auto rs = area(rc);
	if(hilight && rs) {
		if(pressable && hot.pressed)
			rc.offset(1, 1);
		draw::rectf(rc, colors::button);
	} else
		draw::rectf(rc, colors::form, op);
	draw::rectb(rc, colors::form);
	return rs;
}

static void windowm(int x, int& y, int width, const char* title) {
	auto border = gui_border;
	rect rc = {x, y, x + width, y}; textf(rc, title);
	if(rc.x2 < x + width)
		rc.x2 = x + width;
	//rc.y2 += border;
	auto hilited = window(rc, false, false, border);
	textf(x, y, width, title);
	y += rc.height() + border * 2;
}

static bool windowv(int x, int& y, int width, const char* title, unsigned key) {
	auto border = gui_border;
	rect rc = {x, y, x + width, y}; textw(rc, title);
	if(rc.x2 < x + width)
		rc.x2 = x + width;
	rc.y2 += border;
	auto hilited = window(rc, true, true, border);
	auto result = hilited && hot.key == MouseLeft && !hot.pressed;
	if(key && !result && hot.key == key)
		result = true;
	text(rc, title, AlignCenterCenter);
	y += rc.height() + border * 2;
	return result;
}

static void tooltips(int x, int y, int width, const char* format, ...) {
	tooltips_point.x = x;
	tooltips_point.y = y;
	tooltips_width = width;
	stringbuilder sb(tooltips_text);
	sb.addv(format, xva_start(format));
}

static void tooltips(const char* format, ...) {
}

static bool isfocused(const rect& rc, const void* value) {
	addelement((int)value, rc);
	if(!current_focus)
		setfocus((int)value, true);
	else if(area(rc)) {
		switch(hot.key) {
		case MouseLeft:
		case MouseRight:
			if(hot.pressed)
				setfocus((int)value, false);
			break;
		}
	}
	return current_focus == (int)value;
}

static void setposition(int& x, int& y, int& width, int padding = 2) {
	if(padding == -1) {
		x += metrics::edit.x1;
		y += metrics::edit.y1;
		width += metrics::edit.x2 - metrics::edit.x1;
	} else {
		x += padding;
		y += padding;
		width -= padding * 2;
	}
}

static bool buttonv(rect rc, bool checked, bool focused, bool border, bool disabled, const char* string, unsigned key, bool press) {
	bool result = false;
	if(focused && key && hot.key == key)
		result = true;
	auto a = area(rc);
	if(a && hot.key == MouseLeft && hot.pressed == press)
		result = true;
	if(checked)
		a = true;
	color active = colors::button.mix(colors::edit, 128);
	if(a) {
		if(hot.pressed)
			gradh(rc, active.darken(), active.lighten());
		else
			gradh(rc, active.lighten(), active.darken());
	} else
		gradh(rc, colors::button.lighten(), colors::button.darken());
	if(border)
		rectb(rc, focused ? colors::active : colors::border);
	if(string)
		text(rc, string, AlignCenter);
	return result;
}

static bool buttonh(rect rc, bool checked, bool focused, bool border, bool disabled, color value, const char* string, unsigned key, bool press, const char* tips, bool focuse_hotkey = false) {
	draw::state push;
	bool result = false;
	struct rect rcb = {rc.x1 + 1, rc.y1 + 1, rc.x2, rc.y2};
	auto a = area(rcb);
	color active = value.mix(colors::edit, 128);
	color a1 = active.lighten();
	color a2 = active.darken();
	color b1 = value.lighten();
	color b2 = value.darken();
	if(disabled) {
		a = false;
		a2 = a1;
	} else {
		if(focuse_hotkey && focused && key && hot.key == key)
			result = true;
		if(!focuse_hotkey && key && hot.key == key)
			result = true;
		if(a && hot.key == MouseLeft && hot.pressed == press)
			result = true;
		if(checked)
			a = true;
	}
	if(a) {
		if(hot.pressed)
			gradv(rcb, a2, a1);
		else
			gradv(rcb, a1, a2);
	} else
		gradv(rcb, b1, b2);
	if(border && !disabled)
		rectb(rc, colors::border);
	auto rco = rc; rco.offset(2, 2);
	if(focused && !disabled)
		rectx(rco, colors::border);
	if(string)
		text(rc, string, AlignCenterCenter);
	if(tips && a && !hot.pressed) {
		char temp[32];
		if(key)
			tooltips("%1 (%2)", tips, key2str(temp, key));
		else
			tooltips(tips);
	}
	return result;
}

static void clipart_radio(int x, int y, unsigned flags) {
	rect rc = {x, y, x + 16, y + 16};
	circlef(x + 7, y + 6, 6, colors::window);
	circle(x + 7, y + 6, 6, getcolor(colors::border, flags));
	if(flags & Checked) {
		color b = getcolor(rc, colors::text, colors::text.mix(colors::active, 32), flags);
		circlef(x + 7, y + 6, 2, b);
		circle(x + 7, y + 6, 2, b);
	}
}

static bool radio(int x, int& y, int width, const char* label, const void* focus, bool checked, const char* tips) {
	draw::state push;
	setposition(x, y, width, 1);
	rect rc = {x, y, x + width, y};
	rect rc1 = {rc.x1 + 22, rc.y1, rc.x2, rc.y2};
	draw::textw(rc1, label);
	rc1.offset(-2);
	rc.y1 = rc1.y1;
	rc.y2 = rc1.y2;
	rc.x2 = rc1.x2;
	unsigned flags = 0;
	if(isfocused(rc, focus))
		flags |= Focused;
	if(checked)
		flags |= Checked;
	clipart_radio(x + 2, y + imax((rc1.height() - 14) / 2, 0), flags);
	bool need_select = false;
	auto a = area(rc);
	if(a && !isdisabled(flags) && hot.key == MouseLeft) {
		if(!hot.pressed)
			need_select = true;
	}
	if(isfocused(flags)) {
		rectx({rc1.x1, rc1.y1, rc1.x2, rc1.y2}, draw::fore);
		if(!isdisabled(flags) && hot.key == KeySpace)
			need_select = true;
	}
	rc = rc1; rc.offset(2);
	draw::text(rc, label);
	//if(tips && a && !hot.pressed)
	//	tooltips(tips);
	y += rc1.height() + 2;
	return need_select;
}

//static bool checkbox(int x, int& y, int width, const char* label, void* focus, const char* tips) {
//	draw::state push;
//	setposition(x, y, width, 1);
//	rect rc = {x, y, x + width, y};
//	rect rc1 = {rc.x1 + 22, rc.y1, rc.x2, rc.y2};
//	draw::textw(rc1, label);
//	rc.y1 = rc1.y1;
//	rc.y2 = rc1.y2;
//	rc.x2 = rc1.x2;
//	auto focused = isfocused(rc, value);
//	auto v1 = value.getvalue();
//	if(!v1)
//		v1 = 1;
//	if((value.get() & v1) != 0)
//		flags |= Checked;
//	clipart(x + 2, y + imax((rc1.height() - 14) / 2, 0), 0, flags, ":check");
//	decortext(flags);
//	auto a = draw::ishilite(rc);
//	auto need_value = false;
//	if(a && !isdisabled(flags) && hot.key == MouseLeft) {
//		if(!hot.pressed)
//			need_value = true;
//	}
//	if(isfocused(flags)) {
//		draw::rectx({rc1.x1 - 2, rc1.y1 - 1, rc1.x2 + 2, rc1.y2 + 1}, draw::fore);
//		if(hot.key == KeySpace)
//			need_value = true;
//	}
//	draw::text(rc1, label);
//	if(tips && a && !hot.pressed)
//		tooltips(tips);
//	return rc1.height() + 2;
//}

static bool button(int& x, int y, int width, const char* text, const void* focus, unsigned key, bool disabled = false) {
	if(!focus)
		focus = text;
	setposition(x, y, width, 2);
	x -= width + metrics::padding * 2;
	rect rc = {x, y, x + width, y + texth() + metrics::padding * 2};
	auto focused = isfocused(rc, focus);
	return buttonh(rc, false, focused, true, disabled, colors::button, text, key, false, 0);
}

static int render_text(int x, int y, int width, const char* string) {
	draw::link[0] = 0;
	auto result = textf(x, y, width, string);
	if(draw::link[0])
		tooltips(x, y, width, draw::link);
	return result;
}

static void breakparam() {
	breakmodal(hot.param);
}

static void keyparam() {
	hot.key = hot.param;
	hot.param = 0;
}

static bool control_board() {
	const int step = 32;
	switch(hot.key) {
	case KeyLeft: camera.x -= step; break;
	case KeyRight: camera.x += step; break;
	case KeyUp: camera.y -= step; break;
	case KeyDown: camera.y += step; break;
	case MouseWheelUp:
		camera.y -= step;
		break;
	case MouseWheelDown:
		camera.y += step;
		break;
	case MouseLeft:
		if(hot.pressed && last_window == hot.hilite) {
			draw::drag::begin(last_window);
			camera_drag = camera;
		} else
			return false;
		break;
	default:
		if(draw::drag::active(last_window)) {
			hot.cursor = CursorAll;
			if(hot.mouse.x >= 0 && hot.mouse.y >= 0)
				camera = camera_drag + (draw::drag::mouse - hot.mouse);
			return true;
		}
		return false;
	}
	return true;
}

void control_standart() {
	if(control_board())
		return;
}

static void render_tooltips(const char* format, int x, int y, int w) {
	if(!format || !format[0])
		return;
	draw::state push;
	draw::font = metrics::font;
	if(!draw::font)
		return;
	rect rc;
	rc.x1 = x + w + gui_border * 2 + gui_padding;
	rc.y1 = y;
	rc.x2 = rc.x1 + tips_width;
	rc.y2 = rc.y1;
	draw::textf(rc, format);
	if(rc.x2 > getwidth() - gui_border - gui_padding) {
		auto w = rc.width();
		rc.x1 = x - gui_border * 2 - gui_padding - w;
		rc.x2 = rc.x1 + w;
	}
	// Correct border
	int height = draw::getheight();
	int width = draw::getwidth();
	if(rc.y2 >= height)
		rc.move(0, height - 2 - rc.y2);
	if(rc.x2 >= width)
		rc.move(width - 2 - rc.x2, 0);
	window(rc, false);
	draw::fore = colors::tips::text;
	draw::textf(rc.x1, rc.y1, rc.width(), format);
}

static void render_tooltips() {
	render_tooltips(tooltips_text, tooltips_point.x, tooltips_point.y, tooltips_width);
	tooltips_text[0] = 0;
}

static void standart_domodal() {
	render_tooltips();
	hot.key = draw::rawinput();
	if(!hot.key)
		exit(0);
}

bool draw::ismodal() {
	domodal = standart_domodal;
	hot.cursor = CursorArrow;
	hot.hilite.clear();
	hotobject = 0;
	render_control = elements;
	if(hot.mouse.x < 0 || hot.mouse.y < 0)
		sys_static_area.clear();
	else
		sys_static_area = {0, 0, draw::getwidth(), draw::getheight()};
	if(!break_modal)
		return true;
	break_modal = false;
	return false;
}

static bool read_sprite(sprite** result, const char* name) {
	if(*result)
		delete *result;
	char temp[260]; stringbuilder sb(temp); sb.add(temp, "art/sprites/%1.pma", name);
	*result = (sprite*)loadb(temp);
	return (*result) != 0;
}

static void end_turn() {
	breakmodal(0);
}

static int render_left() {
	int x = gui_border;
	int y = gui_border;
	return y;
}

static void init_theme() {
	colors::active = color::create(128, 172, 0);
	colors::border = color::create(73, 73, 80);
	colors::button = color::create(41, 31, 67);
	colors::form = color::create(32, 32, 32);
	colors::window = color::create(64, 64, 64);
	colors::text = color::create(255, 255, 255);
	colors::edit = color::create(38, 79, 120);
	colors::special = color::create(255, 244, 32);
	colors::special2 = color::create(32, 244, 32);
	colors::border = colors::window.mix(colors::text, 128);
	colors::tips::text = color::create(255, 255, 255);
	colors::tips::back = color::create(100, 100, 120);
	colors::tabs::back = color::create(255, 204, 0);
	colors::tabs::text = colors::black;
	colors::h1 = colors::text.mix(colors::edit, 64);
	colors::h2 = colors::text.mix(colors::edit, 96);
	colors::h3 = colors::text.mix(colors::edit, 128);
	draw::font = metrics::font;
	draw::fore = colors::text;
	draw::fore_stroke = colors::blue;
}

void draw::initialize() {
	init_theme();
	create(-1, -1, 900, 600, WFResize | WFMinmax | WFMaximized, 32);
	setcaption("D&D5 emulator");
}

void drawable::paint(int x0, int y0, bool allow_select) const {
	x0 += x; y0 += y;
	rect rc = {x0 - 24, y0 - 24, x0 + 24, y0 + 24};
	if(allow_select && area(rc)) {
		hot.cursor = CursorHand;
		hotobject = const_cast<drawable*>(this);
	}
	image(x0, y0, gres(rid), frame, flags);
}

static point point_param;

static void set_creature_position() {
	auto p = (creaturei*)hot.object;
	if(align_grid)
		point_param = m2s(s2m(point_param)) + half_grid;
	p->setposition(point_param);
}

void creaturei::paint(int x0, int y0, bool allow_drag, bool allow_click) const {
	x0 += x; y0 += y;
	rect rc = {x0 - 24, y0 - 24, x0 + 24, y0 + 24};
	auto drag_active = drag::active();
	if(drag::active(rc)) {
		x0 += hot.mouse.x - drag::mouse.x;
		y0 += hot.mouse.y - drag::mouse.y;
	}
	if(drag_active != drag::active()) {
		point_param.x = x + hot.mouse.x - drag::mouse.x;
		point_param.y = y + hot.mouse.y - drag::mouse.y;
		execute(set_creature_position, 0, (void*)this);
		x0 += hot.mouse.x - drag::mouse.x;
		y0 += hot.mouse.y - drag::mouse.y;
	}
	drawable::paint(x0 - x, y0 - y, allow_click);
	if(type == Race) {
		auto push = fore;
		fore = color_friendly;
		if(is(Hostile))
			fore = color_hostile;
		circle(x0, y0, 32);
		circle(x0, y0, 33);
		circle(x0, y0, 31);
		if(hotobject == this) {
			if(allow_click)
				circle(x0, y0, 30);
			if(hot.pressed) {
				if(allow_drag && hot.key == MouseLeft && !drag::active()) {
					drag::begin(rc);
				} else if(allow_click)
					circle(x0, y0, 29);
			}
		}
		fore = push;
	}
}

static void render_main() {
	last_window = {0, 0, getwidth(), getheight()};
	rectf(last_window, colors::black);
	hotcamera = camera;
	hotcamera.x -= last_window.width() / 2;
	hotcamera.y -= last_window.height() / 2;
	if(area(last_window)) {
	}
	for(auto& e : bsdata<drawable>())
		e.paint(-hotcamera.x, -hotcamera.y, false);
	for(auto& e : bsdata<creaturei>())
		e.paint(-hotcamera.x, -hotcamera.y, true, true);
}

point draw::choosepoint() {
	point result = {-1, -1};
	while(ismodal()) {
		render_main();
		domodal();
		control_standart();
	}
	return result;
}

static bool labelb(int x, int& y, int w, const char* text, const void* param, unsigned key) {
	rect rc = {x, y, x + w, y};
	textf(rc, text);
	auto result = false;
	auto hilite = area(rc);
	if(hilite && hot.key == MouseLeft && !hot.pressed)
		result = true;
	else if(key && hot.key == key)
		result = true;
	rect r1 = rc; r1.offset(-metrics::padding, -metrics::padding);
	if(hilite) {
		hot.cursor = CursorHand;
		if(hot.pressed) {
			//r1.offset(-2, -2);
			//gradv(r1, colors::button, colors::button.mix(colors::border));
			rectf(r1, colors::border);
			rectb(r1, colors::button);
		} else {
			rectf(r1, colors::button);
			rectb(r1, colors::button.mix(colors::border));
		}
	}
	y += textf(rc.x1, rc.y1, w, text) + metrics::padding + 1;
	return result;
}

static bool control_dialog() {
	int i;
	switch(hot.key) {
	case KeyUp:
	case KeyDown:
	case KeyLeft:
	case KeyRight:
	case KeyTab:
		i = getnext(current_focus, hot.key);
		if(i == current_focus)
			return false;
		setfocus(i, true);
		break;
	default:
		return false;
	}
	return true;
}

static void answer_select() {
	auto p = (int*)hot.object;
	*p = hot.param;
}

static int slider(int x, int& y, int w, const char* title, int value, bool plus, bool minus) {
	setposition(x, y, w, 1);
	rect rc = {x, y, x + w, y + texth() + 4};
	unsigned flags = 0;
	auto focused = isfocused(rc, title);
	if(focused)
		rectx(rc, colors::border);
	rc.offset(2, 2);
	text(rc.x1, rc.y1, title);
	auto h1 = rc.height();
	auto w1 = h1 + 2;
	auto x2 = rc.x2;
	auto result = 0;
	if(buttonh({x2 - w1, rc.y1, x2, rc.y1 + h1}, false, focused, true, !plus, colors::button, "+", '+', false, 0, true))
		result = 1;
	x2 -= w1 + 2;
	if(buttonh({x2 - w1, rc.y1, x2, rc.y1 + h1}, false, focused, true, !minus, colors::button, "-", '-', false, 0, true))
		result = -1;
	x2 -= w1 + 2 + textw('0') * 3;
	char temp[8]; stringbuilder sb(temp);
	sb.add("%1i", value);
	text(x2, rc.y1, temp);
	y += rc.height() + 5;
	return result;
}

static void render_description(int x, int y, int w) {
	if(!current_info)
		return;
	auto w2 = 200;
	char temp[1024]; stringbuilder sb(temp);
	auto p = current_info.getinfo(sb);
	if(!p)
		return;
	auto push_font = font;
	font = metrics::font;
	textf(x, y, w, p);
	font = push_font;
}

static void set_info() {
	current_info = hot.param;
}

static void render_left(int x, int y, int w, int v) {
	if(v < 2)
		return;
	char temp[260]; stringbuilder sb(temp);
	sb.add("�������� ��� [%1i]", v);
	textf(x, y, w, temp);
}

static void dialog(int& x, int& y, const char* header, const char* description) {
	auto push_font = font;
	auto push_fore = fore;
	x = (getwidth() - dialog_w) / 2;
	y = (getheight() - dialog_h) / 2 - texth() - gui_border * 4;
	if(y < gui_border * 2)
		y = gui_border * 2;
	window({x, y, x + dialog_w, y + dialog_h}, false);
	if(header) {
		font = metrics::h1;
		fore = colors::h1;
		y += textf(x, y, dialog_w, header);
	}
	if(description) {
		font = metrics::h2;
		fore = colors::text;
		y += textf(x, y, dialog_w, description) + metrics::padding * 2;
	}
	fore = push_fore;
	font = push_font;
}

static void footer(int& x, int& y) {
	x = (getwidth() - dialog_w) / 2 + dialog_w;
	y = (getheight() - dialog_h) / 2 - texth() - gui_border * 4;
	if(y < gui_border * 2)
		y = gui_border * 2;
	y += dialog_h - texth() - gui_border * 2;
}

static void right_dialog(int& x, int& y) {
	x = getwidth() - window_width - gui_border * 2;
	y = gui_border * 2;
}

static void right_panel(int& x, int& y, const char* title, bool cancel_button) {
	right_dialog(x, y);
	auto y2 = getheight() - gui_border * 2;
	window({x, y, x + window_width, y2}, false, false);
	rect rh = {x, y, x + window_width, y + 12};
	if(title) {
		auto push_font = font;
		font = metrics::h1;
		draw::text(rh.x1, rh.y1, title);
		font = push_font;
	}
	if(cancel_button) {
		rect rc;
		rc.x1 = getwidth() - gui_border * 2 - 16;
		rc.y1 = y + 4;
		rc.x2 = rc.x1 + 12;
		rc.y2 = rc.y1 + 12;
		auto result = window(rc, true, true);
		if((result && hot.key == MouseLeft && !hot.pressed) || hot.key == KeyEscape)
			execute(buttoncancel);
	}
}

static void* choose_element(const char* title, const void* current_value, void** data, unsigned data_count, fntext getname, array* source) {
	openform();
	parami params = {};
	params.maximum = data_count;
	params.perpage = ((200 - 6 - 16 - 6) / (texth() + 4));
	auto found_current = false;
	for(unsigned i = 0; i < data_count; i++) {
		if(data[i] == current_value) {
			found_current = true;
			params.origin = i;
		}
	}
	if(!found_current)
		current_value = 0;
	params.correct();
	setfocus((int)current_value, true);
	int x, y;
	while(ismodal()) {
		render_main();
		right_panel(x, y, title, true);
		void* current_element = 0;
		for(auto i = params.origin; i < params.maximum; i++) {
			char temp[260]; stringbuilder sb(temp);
			auto pt = data[i];
			auto pn = getname(pt, sb);
			if(!pn)
				pn = "���";
			y += 2;
		}
		domodal();
		if(control_board())
			continue;
	}
	closeform();
	return (void*)getresult();
}

const char* test_name(const void* object, stringbuilder& sb) {
	return "None";
}

void choose_elements() {
	void* source[2] = {};
	choose_element("Test", 0, source, 2, test_name, 0);
}

variant variantc::chooseg(const char* header, const char* description, int score) const {
	int x, y;
	openform();
	if(*this)
		current_info = data[0];
	while(ismodal()) {
		render_main();
		dialog(x, y, header, description);
		auto x1 = x, y0 = y;
		x += metrics::padding * 2;
		const auto w2 = 180;
		for(auto& e : *this) {
			auto checked = (e == current_info);
			if(radio(x, y, w2, e.getname(), &e, checked, 0))
				execute(set_info, e);
		}
		render_left(x1, y, w2, score);
		render_description(x + w2 + metrics::padding * 2, y0, dialog_w - w2 - (x - x1) - metrics::padding * 2);
		footer(x, y);
		if(button(x, y, 100, "OK", 0, KeyEnter))
			execute(buttonparam, current_info);
		if(button(x, y, 100, "Cancel", 0, KeyEscape))
			execute(buttonparam, 0);
		domodal();
		if(control_dialog())
			continue;
		control_standart();
	}
	closeform();
	return getresult();
}

static void set_num8() {
	auto p = (unsigned char*)hot.object;
	*p = hot.param;
}

static void set_num32() {
	auto p = (unsigned*)hot.object;
	*p = hot.param;
}

static int getpluar(int v) {
	switch(v) {
	case 1: return 0;
	case 2: case 3: case 4: return 1;
	default: return 2;
	}
}

static void render_cost(int x, int y, int w, int v, int m) {
	static const char* text_score[] = {"����", "����", "�����"};
	char temp[260]; stringbuilder sb(temp);
	if(v >= m)
		return;
	sb.add("�������� ��� [%1i] %2", m - v, maptbl(text_score, getpluar(m - v)));
	textf(x, y, w, temp);
}

int	statistic::choose_frame(resource_s resource, const char* header, const char* description, point size) {
	int x, y;
	auto ps = gres(resource);
	if(!ps)
		return -1;
	int current = 0;
	openform();
	while(ismodal()) {
		render_main();
		dialog(x, y, header, description);
		auto x1 = x, y0 = y;
		x += metrics::padding * 2;
		const auto w = dialog_w;
		auto mx = dialog_w / size.x;
		auto my = dialog_h / size.y;
		for(auto ty = 0; ty < my; ty++) {
			for(auto tx = 0; tx < mx; tx++) {
				auto frame = ty * mx + tx;
				if(frame >= ps->count)
					break;
				rect rc;
				rc.x1 = x + tx * size.x;
				rc.y1 = y + ty * size.y;
				rc.x2 = rc.x1 + size.x - 1;
				rc.y2 = rc.y1 + size.y - 1;
				auto focus = &ps->get(frame);
				auto focused = isfocused(rc, focus);
				if(area(rc)) {
					if(hot.pressed)
						rectf(rc, colors::border, 64);
					else
						rectf(rc, colors::border, 32);
					if(hot.key == MouseLeft && hot.pressed)
						setfocus((int)focus, false);
					if((hot.key == MouseLeft && !hot.pressed)
						|| (focused && hot.key == KeyEnter))
						execute(set_num32, frame, &current);
				}
				if(current == frame) {
					rectb(rc, colors::active);
					rectb({rc.x1 + 1, rc.y1 + 1, rc.x2 - 1, rc.y2 - 1}, colors::active);
				}
				if(focused) {
					auto r1 = rc;
					r1.offset(2, 2);
					rectx(r1, colors::border);
				}
				image(rc.x1 + size.x / 2, rc.y1 + size.y / 2, ps, frame, 0);
			}
		}
		footer(x, y);
		if(button(x, y, 100, "OK", "OK", KeyEnter))
			execute(buttonparam, current);
		if(button(x, y, 100, "Cancel", "Cancel", KeyEscape))
			execute(buttonparam, -1);
		domodal();
		if(control_dialog())
			continue;
		control_standart();
	}
	closeform();
	return getresult();
}

bool statistic::choose_ability(const char* header, const char* description, int score_maximum) {
	int x, y;
	openform();
	while(ismodal()) {
		render_main();
		dialog(x, y, header, description);
		auto x1 = x, y0 = y;
		x += metrics::padding * 2;
		const auto w2 = 220;
		auto cost = getabilityscores();
		for(auto v : all_abilities) {
			variant vr = v;
			auto current = abilities[v];
			auto allow_plus = current < 15 && (cost + (getabilityscore(abilities[v] + 1) - getabilityscore(abilities[v]))) <= score_maximum;
			auto allow_minus = current > 8;
			auto r = slider(x, y, w2, vr.getname(), abilities[v], allow_plus, allow_minus);
			if(r == 1)
				execute(set_num8, abilities[v] + 1, &abilities[v]);
			else if(r == -1)
				execute(set_num8, abilities[v] - 1, &abilities[v]);
			if((void*)current_focus == vr.getname())
				current_info = vr;
		}
		render_cost(x, y + metrics::padding * 2, w2, getabilityscores(), score_maximum);
		render_description(x + w2 + 4, y0, dialog_w - w2 - (x - x1) - 4);
		footer(x, y);
		if(button(x, y, 100, "OK", "OK", KeyEnter, cost < score_maximum))
			execute(buttonok);
		if(button(x, y, 100, "Cancel", "Cancel", KeyEscape))
			execute(buttoncancel);
		domodal();
		if(control_dialog())
			continue;
		control_standart();
	}
	closeform();
	return getresult();
}

static int show_picture(int x, int y, resource_s id, unsigned frame) {
	auto ps = gres(id);
	if(!ps)
		return 0;
	auto& f = ps->get(frame);
	rect rc = {x, y, x + f.sx, y + f.sy};
	auto mode = 1;
	if(f.sx == 160 && f.encode == ps->RAW8) {
		rc = {x, y, x + f.sx * 2, y + f.sy * 2};
		mode = 2;
	}
	rc.offset(-gui_border);
	draw::rectf(rc, colors::form, opacity_button);
	if(mode==2) {
		surface bm(f.sx, f.sy, 32);
		auto push = canvas;
		canvas = &bm;
		image(0, 0, ps, 0, 0, 0);
		canvas = push;
		scale2x(ptr(x, y), canvas->scanline, bm.ptr(0, 0), bm.scanline, bm.width, bm.height);
	} else
		image(x, y, ps, frame, 0);
	return rc.height();
}

const answers::element* answers::choosev(const char* title, const char* cancel_text, bool interactive, resource_s id, short unsigned frame) const {
	int x, y;
	if(!elements)
		return 0;
	openform();
	while(ismodal()) {
		render_main();
		right_dialog(x, y);
		if(id)
			y += show_picture(x, y, id, frame);
		if(title) {
			windowm(x, y, window_width, title);
			y += metrics::padding;
		}
		for(auto& e : elements) {
			if(windowv(x, y, window_width, e.text, 0))
				execute(breakparam, (int)&e);
			y += 2;
		}
		if(cancel_text) {
			if(windowv(x, y, window_width, cancel_text, KeyEscape))
				execute(breakparam, 0);
		}
		domodal();
		control_standart();
	}
	closeform();
	return (element*)getresult();
}

static void set_border() {
	auto p = (unsigned char*)hot.object;
	*p ^= (unsigned char)hot.param;
}

static void render_hilite(int x, int y, int w, int h, unsigned char& b, unsigned char f) {
	rect rc = {x, y, x + w, y + h};
	if((b & f) != 0)
		rectf(rc, colors::red, 0x80);
	if(area(rc)) {
		hot.cursor = CursorHand;
		rectf(rc, colors::blue, 0x80);
		if(hot.key == MouseLeft && hot.pressed)
			execute(set_border, f, &b);
	}
}

static void render_grid(int x, int y, tilei* p, short unsigned index) {
	//render_hilite(x + 16, y - 8, 32, 16, b, 1);
	//render_hilite(x - 8, y + 16, 16, 32, b, 2);
	//render_hilite(x - 8, y - 8, 16, 16, b, 4);
	auto f = 1 << (7 - (index % 8));
	auto& b = p->block[index / 8];
	render_hilite(x + 10, y + 10, 44, 44, b, f);
}

void tilei::edit() {
	while(ismodal()) {
		rect rc = {0, 0, getwidth(), getheight()};
		rectf(rc, colors::black);
		rc.x2 -= 200;
		auto ps = gres(ResDungeon);
		auto nm = this - bsdata<tilei>::elements;
		auto x0 = rc.width() / 2;
		auto y0 = rc.height() / 2;
		image(x0, y0, ps, nm * 2, 0);
		for(auto x = 0; x < 8; x++) {
			for(auto y = 0; y < 8; y++) {
				auto x1 = x0 - x * 64 + 4 * 64 - grid_size;
				auto y1 = y0 - y * 64 + 4 * 64 - grid_size;
				render_grid(x1, y1, this, y * size + x);
			}
		}
		domodal();
		switch(hot.key) {
		case 'E':
			exportdata();
			break;
		}
	}
}