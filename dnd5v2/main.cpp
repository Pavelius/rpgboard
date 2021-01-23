#include "main.h"

void util_main();

static point half_grid = {grid_size / 2, grid_size / 2};

static void test_characters() {
	drawable* pd;
	creaturei* p;
	pd = bsdata<drawable>::add();
	pd->setframe(ResDungeon, 0);
	pd->setposition({0, 0});
	pd->setmirrorv(true);
	pd = bsdata<drawable>::add();
	pd->setframe(ResDungeon, 1);
	pd->setposition({0, 512});
	pd->setmirrorv(true);
	pd->setmirrorh(true);
	pd = bsdata<drawable>::add();
	pd->setframe(ResDungeon, 2);
	pd->setposition({512, 0});
	pd->setmirrorv(true);
	pd = bsdata<drawable>::add();
	pd->setframe(ResDungeon, 2);
	pd->setposition({512, 512});
	p = bsdata<creaturei>::add();
	p->setkind(DwarfHill);
	p->setframe(ResAvatars, 0);
	p->setposition(m2s({3, 3}) - half_grid);
	p = bsdata<creaturei>::add();
	p->setkind(Human);
	p->setframe(ResAvatars, 1);
	p->setposition(m2s({0, 4}) - half_grid);
	p = bsdata<creaturei>::add();
	p->setkind(Human);
	p->setframe(ResMonsters, 0);
	p->setposition(m2s({0, -2}) - half_grid);
	p->set(Hostile);
}

static void add_character() {
	creaturei e;
	if(!e.generate(true))
		return;
	auto p = bsdata<creaturei>::add();
	if(!p)
		return;
	*p = e;
}

static void test_choose() {
	creaturei e;
	e.choose_frame(ResAvatars, "Выбирайте портрет", "Выбирайте портрет вашего персонажа", {70, 70});
}

static void menu_handle() {
	while(true) {
		answers aw;
		aw.add(1, "Персонажи");
		aw.add(1, "Настройки");
		auto id = aw.choose(0);
		if(id == 1)
			add_character();
	}
}

int main(int argc, char* argv[]) {
	auto u1 = sizeof(creaturei);
	auto u2 = sizeof(statistic);
	varianti::localization("ru", false);
	varianti::localization("debug", true);
	srand(clock());
	util_main();
	draw::initialize();
	test_characters();
	//add_character();
	menu_handle();
	//test_choose();
	//while(true) {
	//	auto pt = draw::choosepoint();
	//	pt = m2s(s2m(pt)) - half_grid;
	//	bsdata<creaturei>::elements[0].setposition(pt);
	//}
	//bsdata<tilei>::elements[3].edit();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}