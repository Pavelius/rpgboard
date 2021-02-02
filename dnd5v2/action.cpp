#include "main.h"

BSDATA(actioni) = {
	{"EndTurn", Instantaneous},
	{"Ambush", StandartAction},
	{"Attack", StandartAction},
	{"Dash", StandartAction},
	{"Disengage", StandartAction},
	{"Dodge", StandartAction},
	{"Feint", StandartAction},
	{"Hide", StandartAction},
	{"Ready", StandartAction},
	{"Search", StandartAction},
	{"UseItem", StandartAction},
};
assert_enum(actioni, ActionUseItem)

static creaturei* getally(const variantc& source, creaturei* exclude, state_s state, bool keep) {
	for(auto v : source) {
		auto p = v.getcreature();
		if(!p)
			continue;
		if(p == exclude)
			continue;
		if(p->is(state) != keep)
			continue;
		return p;
	}
	return 0;
}

bool creaturei::use(action_s id, bool run) {
	auto& ei = bsdata<actioni>::elements[id];
	if(ei.duration == StandartAction) {
		if(get(StandartActionSlot) <= 0)
			return false;
	}
	if(ei.duration == BonusAction) {
		if(get(BonusActionSlot) <= 0)
			return false;
	}
	switch(id) {
	case ActionEndTurn:
		if(get(Movement) <= 0)
			return false;
		if(run)
			set(Movement, 0);
		break;
	case ActionAttack:
		if(true) {
			variantc creatures(bsdata<creaturei>::source);
			creatures.match(Hostile, !is(Hostile));
			creatures.range(*this, grid_size, true);
			if(!creatures)
				return false;
			if(run) {
				auto target = creatures.choose(0).getcreature();
				if(target)
					attack(target, 0, 0);
			}
		}
		break;
	case ActionFeint:
		if(true) {
			variantc creatures(bsdata<creaturei>::source);
			if(!getally(creatures, this, Hostile, is(Hostile)))
				return false;
			creatures.match(Hostile, !is(Hostile));
			creatures.match(ActionFeint, false);
			creatures.range(*this, grid_size, true);
			if(!creatures)
				return false;
			if(run) {
				auto target = creatures.choose(0).getcreature();
				if(target)
					attack(target, 0, 0);
			}
		}
		break;
	case ActionHide:
		if(is(ActionHide))
			return false;
		if(!isreadytohide())
			return false;
		if(run)
			set(ActionHide);
		break;
	case ActionDisengage:
		if(true) {
			variantc creatures(bsdata<creaturei>::source);
			creatures.match(Hostile, !is(Hostile));
			creatures.range(*this, grid_size, true);
			if(!creatures)
				return false;
			if(run)
				set(ActionDisengage);
		}
		break;
	}
	return true;
}