#include "main.h"

BSDATA(savei) = {
	{"SaveVsStrenght", Strenght},
	{"SaveVsDexterity", Dexterity},
	{"SaveVsConstitution", Constitution},
	{"SaveVsIntellegence", Intellegence},
	{"SaveVsWisdow", Wisdow},
	{"SaveVsCharisma", Charisma},
	{"SaveVsCharm", Wisdow},
	{"SaveVsFear", Wisdow},
	{"SaveVsPoison", Constitution},
};
assert_enum(savei, SaveVsPoison)