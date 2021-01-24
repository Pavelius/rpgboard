#include "main.h"
#include "draw.h"
#include "io.h"

using namespace draw;

void sprite_create(sprite* p, int count, int cicles, int additional_bytes);
int sprite_store(sprite* ps, const unsigned char* p, int width, int w, int h, int ox, int oy, sprite::encodes mode, unsigned char shadow_index, color* original_pallette, int explicit_frame, unsigned char transparent_index);
void sprite_write(const char* url, const sprite* p);

namespace {
struct imageurl {
	const char*			id;
	point				pos;
};
}

static surface& gettokenform() {
	static surface source("D:/resources/topdown/portraits/pattern.bmp");
	return source;
}

static sprite* create_pma(int count, int size = 1024*1024*16) {
	sprite* p = (sprite*)new char[size];
	sprite_create(p, count, 0, 0);
	return p;
}

static void close_pma(sprite* p, resource_s id) {
	auto& e = bsdata<resourcei>::elements[id];
	char url[260]; stringbuilder sb(url);
	sb.add("art/");
	sb.add(e.folder);
	sb.add("/");
	sb.add("%1.pma", e.name);
	sprite_write(url, p);
	delete p;
}

static void rotate(surface& dst, surface& src) {
	dst.clear();
	dst.resize(src.height, src.width, src.bpp, true);
	for(auto x = 0; x < src.width; x++) {
		for(auto y = 0; y < src.height; y++) {
			auto p1 = dst.ptr(y, x);
			auto p2 = src.ptr(x, y);
			memcpy(p1, p2, dst.bpp / 8);
		}
	}
}

static void add_bmp(sprite* p, const char* id, const char* folder, int x = 0, int y = 0, int sx = -1, int sy = -1, int ox = -1, int oy = -1) {
	char temp[260];
	stringbuilder sb(temp);
	sb.add(folder);
	sb.add("/");
	sb.add("%1.bmp", id);
	surface bmp(temp);
	if(!bmp)
		return;
	if(sx == -1)
		sx = bmp.width;
	if(sy == -1)
		sy = bmp.height;
	if(ox == -1)
		ox = bmp.width/2;
	if(oy == -1)
		oy = bmp.height/2;
	sprite_store(p, bmp.ptr(0, 0), bmp.scanline,
		sx, sy, ox, oy,
		sprite::RAW, 0, 0, -1, 0);
}

static void add_bmp2(sprite* p, const char* id, const char* folder, int x = 0, int y = 0, int sx = -1, int sy = -1, int ox = 0, int oy = 0) {
	char temp[260];
	stringbuilder sb(temp);
	sb.add(folder);
	sb.add("/");
	sb.add("%1.bmp", id);
	surface bmp(temp);
	if(!bmp)
		return;
	if(sx == -1)
		sx = bmp.width;
	if(sy == -1)
		sy = bmp.height;
	ox += bmp.width / 2;
	oy += bmp.height / 2;
	sprite_store(p, bmp.ptr(0, 0), bmp.scanline,
		sx, sy, ox, oy,
		sprite::RAW, 0, 0, -1, 0);
	surface bmr;
	rotate(bmr, bmp);
	sprite_store(p, bmr.ptr(0, 0), bmp.scanline,
		sx, sy, oy, ox,
		sprite::RAW, 0, 0, -1, 0);
}

static void transparent(unsigned char* p) {
	p[0] = 255;
	p[1] = 255;
	p[2] = 255;
	p[3] = 0;
}

static void apply_mask(surface& dst, surface& msk) {
	for(auto y = 0; y < msk.height; y++) {
		for(auto x = 0; x < msk.width; x++) {
			auto n = *msk.ptr(x, y);
			if(n == 255)
				transparent(dst.ptr(x, y));
			else if(n > 0)
				dst.ptr(x, y)[3] = n;
		}
	}
}

static void add_bmp_masked(sprite* p, const char* id, const char* folder) {
	char temp[260];
	stringbuilder sb(temp);
	sb.add(folder);
	sb.add("/");
	sb.add("%1.bmp", id);
	surface bmp(temp);
	if(!bmp)
		return;
	auto& mask = gettokenform();
	apply_mask(bmp, mask);
	auto sx = bmp.width;
	auto sy = bmp.height;
	auto ox = bmp.width / 2;
	auto oy = bmp.height / 2;
	sprite_store(p, bmp.ptr(0, 0), bmp.scanline,
		sx, sy, ox, oy,
		sprite::RLE, 0, 0, -1, 0);
}

static void add_png(sprite* p, const char* id, const char* suff, const char* folder, int x = 0, int y = 0, int sx = -1, int sy = -1, int ox = -1, int oy = -1) {
	static char temp[260];
	stringbuilder sb(temp);
	sb.add(folder);
	sb.add("/");
	sb.add(id);
	if(suff)
		sb.add(suff);
	sb.add(".png");
	surface bmp(temp);
	if(!bmp)
		return;
	if(sx == -1)
		sx = bmp.width;
	if(sy == -1)
		sy = bmp.height;
	if(ox == -1)
		ox = bmp.width / 2;
	if(oy == -1)
		oy = bmp.height / 2;
	sprite_store(p, bmp.ptr(0, 0), bmp.scanline,
		sx, sy, ox, oy,
		sprite::RLE, 0, 0, -1, 0);
}

static void add_png2(sprite* p, const char* id, const char* folder, int x = 0, int y = 0, int sx = -1, int sy = -1, int ox = 0, int oy = 0) {
	char temp[260];
	stringbuilder sb(temp);
	sb.add(folder);
	sb.add("/");
	sb.add("%1.png", id);
	surface bmp(temp);
	if(!bmp)
		return;
	if(sx == -1)
		sx = bmp.width;
	if(sy == -1)
		sy = bmp.height;
	ox += bmp.width / 2;
	oy += bmp.height / 2;
	sprite_store(p, bmp.ptr(0, 0), bmp.scanline,
		sx, sy, ox, oy,
		sprite::RLE, 0, 0, -1, 0);
	surface bmr;
	rotate(bmr, bmp);
	sprite_store(p, bmr.ptr(0, 0), bmp.scanline,
		sx, sy, oy, ox,
		sprite::RLE, 0, 0, -1, 0);
}

static void create_geomorph() {
	auto count = bsdata<tilei>::source.getcount();
	const char* surl = "D:/resources/geomorph/bmp";
	auto p = create_pma(count*2, 32*1024*1024);
	for(auto& e : bsdata<tilei>())
		add_bmp2(p, e.id, surl);
	close_pma(p, ResDungeon);
}

static void create_sprites() {
	static imageurl source[] = {
		{"Dwarven_fighter_hammer_03"},
		{"Cleric_Blue_48", {0,-8}},
		{"Elf_Rogue_Bow", {0, -8}},
	};
	const auto count = sizeof(source) / sizeof(source[0]);
	const char* surl0 = "D:/resources/topdown/creatures_f0";
	auto p = create_pma(count * 2);
	for(auto& e : source) {
		add_png2(p, e.id, surl0, 0, 0, -1, -1, e.pos.x, e.pos.y);
		//add_png(p, e.id, surl1);
	}
	close_pma(p, ResCharacter);
}

static void create_avatars() {
	static const char* source[] = {
		{"northmen"},
		{"northmen2"},
		{"druid"},
	};
	const auto count = sizeof(source) / sizeof(source[0]);
	const char* surl0 = "D:/resources/topdown/portraits";
	auto p = create_pma(count );
	for(auto id : source)
		add_bmp_masked(p, id, surl0);
	close_pma(p, ResAvatars);
}

static void create_monsters() {
	static const char* source[] = {
		{"skeleton"},
	};
	const auto count = sizeof(source) / sizeof(source[0]);
	const char* surl0 = "D:/resources/topdown/monsters";
	auto p = create_pma(count);
	for(auto id : source)
		add_bmp_masked(p, id, surl0);
	close_pma(p, ResMonsters);
}

static void create_gui() {
	static const char* source[] = {
		{"btn_narrow"},
		{"btn_paper"},
		{"btn_small"},
	};
	const auto count = sizeof(source) / sizeof(source[0]);
	const char* surl0 = "D:/resources/gui";
	auto p = create_pma(count*4);
	for(auto id : source) {
		add_png(p, id, "_off", surl0);
		add_png(p, id, "_over", surl0);
		add_png(p, id, "_down", surl0);
		add_png(p, id, "_grey", surl0);
	}
	close_pma(p, ResGUI);
}

void tilei::exportdata() const {
	char temp[260];
	stringbuilder sb(temp);
	sb.add("export");
	sb.add("/");
	sb.add("%1.txt", id);
	surface bmp(temp);
	io::file file(temp, StreamWrite|StreamText);
	if(!file)
		return;
	for(auto i = 0; i < size; i++) {
		if(i != 0)
			file << ", ";
		file << (int)block[i];
	}
}

void util_main() {
	create_gui();
	//create_monsters();
	//create_avatars();
	//create_sprites();
	//create_geomorph();
}