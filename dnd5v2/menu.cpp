#include "main.h"
#include "draw.h"

static void disonnect_game() {
	if(dlgask("Вы действительно хотите **отключиться** от текущей игры? Не волнуйтесь, все ваши несохраненные данные будут сохранены перед выходом."))
		return;
}

BSDATA(menu) = {
	{"character", "root"},
	{"settings", "root"},
	{"network", "settings"},
	{"grafic", "settings", },
	{"user", "settings"},
	{"create_game", "game"},
	{"connect", "game"},
	{"disconnect", "game", disonnect_game},
	{"reconnect", "game"},
};
BSDATAF(menu)

const menu* menu::choose(const char* name, bool allow_back) {
	answers aw;
	return choose(aw, name, allow_back);
}

const menu* menu::choose(answers& aw, const char* name, bool allow_back) {
	for(auto& e : bsdata<menu>()) {
		if(strcmp(e.parent, name) == 0)
			aw.add((int)&e, e.name);
	}
	if(!aw.elements)
		return 0;
	return (menu*)aw.choose(0, allow_back, true);
}

void menu::run(const char* parent) {
	while(true) {
		auto m = menu::choose(parent, true);
		if(!m)
			return;
		if(m->command)
			m->command();
		run(m->id);
	}
}

static bool dlgaskv(const char* format) {
	answers aw;
	aw.add(1, "Да");
	auto p = aw.choosev(format, "Нет", true, ResNPC, 10);
	if(!p)
		return false;
	return true;
}

bool dlgask(const char* format, ...) {
	char temp[2048]; stringbuilder sb(temp); sb.add(format, xva_start(format));
	return dlgaskv(temp);
}