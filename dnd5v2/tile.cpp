#include "main.h"

BSDATA(tilei) = {
	{"cave_pc", 8, {16, 20, 192, 17, 5, 136, 19, 135}},
	{"cave_pc2", 8, {155, 137, 225, 152, 136, 131, 199, 231}},
	{"cave_ps", 8, {231, 176, 137, 1, 49, 136, 132, 231}},
	{"cave_s2", 8, {132, 56, 32, 164, 37, 12, 16, 167}},
	{"cave_pt", 8, {64, 16, 0, 40, 5, 160, 0, 4}},
	{"cave_px", 8, {229, 32, 9, 16, 32, 9, 37, 164}},
	{"cave_crystal", 8, {39, 0, 0, 129, 0, 0, 0, 165}},
	{"cave_spider", 8},
	{"cave_lair", 8},
	{"cave_treasure", 8},
	{"cave_treasure2", 8},
};
BSDATAF(tilei)

bool tilei::isblocked(tilei::indext i) const {
	return (block[i / 8] & (1 << (i % 8))) != 0;
}