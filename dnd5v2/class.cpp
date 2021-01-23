#include "main.h"

BSDATA(classi) = {
	{"Cleric", {Wisdow, Strenght, Constitution}, 8, {SaveVsWisdow, SaveVsCharisma}},
	{"Fighter", {Strenght, Dexterity, Constitution}},
	{"Rogue", {Dexterity, Charisma, Strenght}},
	{"Wizard", {Intellegence, Dexterity, Charisma}},
};
assert_enum(classi, Wizard)