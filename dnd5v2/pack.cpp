#include "main.h"

BSDATA(packi) = {
	{"Light armor", {PaddedArmor, LeatherArmor, StuddedLeather}},
	{"Medium armor", {HideArmor, ChainShirt, Breastplate, HalfPlate, ScaleMail}},
	{"Heavy armor", {RingMail, ChainMail, SplintArmor, PlateArmor}},
	{"Shields", {Shield}},
	{"Simple weapons", {Club, Dagger, Greatclub, Handaxe, Javelin, Lighthammer, Mace, Quarterstaff, Sickle, Spear}},
	{"Martial weapons", {Battleaxe, Flail, Glaive, Greataxe, Greatsword, Halberd, Lance, Longsword, Maul, Morningstar, Pike, Rapier, Scimitar, Shortsword, Trident, Warpick, Warhammer, Whip}},
	{"Common languages", {LanguageCommon, LanguageDwarvish, LanguageElvish, LanguageGoblin, LanguageHalfling, LanguageOrc}},
};
assert_enum(packi, CommonLanguages)