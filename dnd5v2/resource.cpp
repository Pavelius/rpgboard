#include "main.h"

BSDATA(resourcei) = {{},
	{"dungeon", "area"},
	{"avatars", "interface"},
	{"monsters", "interface"},
	{"npc", "scenery"},
};
assert_enum(resourcei, ResNPC)

void resourcei::geturl(stringbuilder& sb) const {
	sb.add("art/");
	if(folder) {
		sb.add(folder);
		sb.add("/");
	}
	sb.add(name);
	sb.add(".pma");
}