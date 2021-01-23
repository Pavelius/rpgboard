#include "main.h"

BSDATA(racei) = {
	{"Dwarf", Dwarf},
	{"Elf", Elf},
	{"Halfling", Halfling},
	{"Human", Human},
	{"DwarfHill", Dwarf},
	{"DwarfMountain", Dwarf},
	{"ElfWood", Elf},
	{"ElfHight", Elf},
	{"HalflingLightfoot", Halfling},
	{"HalflingStout", Halfling},
};
assert_enum(racei, HalflingStout)