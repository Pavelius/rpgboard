#include "main.h"

BSDATA(actioni) = {
	{"Ambush", StandartAction},
	{"Attack", StandartAction},
	{"Dash", StandartAction},
	{"Disengage", StandartAction},
	{"Dodge", StandartAction},
	{"Help", StandartAction},
	{"Hide", StandartAction},
	{"Ready", StandartAction},
	{"Search", StandartAction},
	{"UseItem", StandartAction},
};
assert_enum(actioni, ActionUseItem)

bool creaturei::use(action_s id, bool run) {
	switch(id) {
	case ActionAttack:
		return true;
	default: return false;
	}
}