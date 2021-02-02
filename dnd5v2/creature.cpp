#include "main.h"

BSDATAC(creaturei, 128)
static rollstati last_roll;

static bool isallowmove(const creaturei* p) {
	return p->get(StandartActionSlot) > 0
		|| p->get(Movement) > 0;
}

void creaturei::uicombat() {
	while(isallowmove(this)) {
		change_position = false;
		answers aw;
		for(auto i = ActionAmbush; i <= ActionUseItem; i = (action_s)(i + 1)) {
			if(!use(i, false))
				continue;
			auto& e = bsdata<actioni>::elements[i];
			aw.add((int)&e, e.name);
		}
		aw.sort();
		menu::select(aw, "root");
		if(use(ActionEndTurn, false)) {
			auto& e = bsdata<actioni>::elements[ActionEndTurn];
			aw.add((int)&e, e.name);
		}
		auto pe = aw.choosev(0, 0, true, ResNone, 0, ischangedposition, 0);
		if(!pe)
			continue;
		auto p = (void*)pe->id;
		if(bsdata<menu>::source.indexof(p) != -1) {
			auto m = (menu*)p;
			if(m->command)
				m->command();
			menu::run(m->id);
		} else if(bsdata<actioni>::source.indexof(p) != -1) {
			auto pa = (actioni*)p;
			auto id = (action_s)(pa - bsdata<actioni>::elements);
			if(use(id, true)) {
				switch(pa->duration) {
				case StandartAction: add(StandartActionSlot, -1); break;
				case BonusAction: add(BonusActionSlot, -1); break;
				}
			}
		}
	}
}

bool creaturei::attack(creaturei* target, int bonus, int advantages) {
	if(target->is(ActionDodge))
		advantages--;
	if(target->is(ActionFeint))
		advantages++;
	auto d = roll(advantages);
	auto r = d + bonus;
	auto a = target->get(ArmorClass);
	if(d == 1 || d < a)
		return false;
	return true;
}

int creaturei::roll20(bool halfling_luck) {
	auto r = 1 + rand() % 20;
	if(r == 1 && halfling_luck)
		r = 1 + rand() % 20;
	return r;
}

int creaturei::roll(int advantages) const {
	last_roll.r1 = roll20(is(Lucky));
	last_roll.r2 = roll20(is(Lucky));
	auto r = last_roll.r1;
	if(advantages > 0) {
		if(last_roll.r2 > last_roll.r1)
			r = last_roll.r2;
	} else if(advantages < 0) {
		if(last_roll.r2 < last_roll.r1)
			r = last_roll.r2;
	}
	return r;
}

void creaturei::beforecombatround() {
	set(Movement, get(Speed));
	set(BonusActionSlot, 1);
	set(StandartActionSlot, 1);
}

void creaturei::aftercombatround() {

}

bool creaturei::isreadytohide() const {
	auto keep = is(Hostile);
	for(auto& e : bsdata<creaturei>()) {
		if(!e.is(Active))
			continue;
		if(e.is(Hostile) != keep)
			return false;
	}
	return true;
}