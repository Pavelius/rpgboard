#include "main.h"

BSDATA(resourcei) = {{},
	{"dungeon", "area"},
	{"characters", "creatures"},
	{"gui", "interface"},
	{"avatars", "interface"},
	{"monsters", "interface"},
};

void resourcei::geturl(stringbuilder& sb) const {
	sb.add("art/");
	if(folder) {
		sb.add(folder);
		sb.add("/");
	}
	sb.add(name);
	sb.add(".pma");
}