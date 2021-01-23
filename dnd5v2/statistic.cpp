#include "main.h"

ability_s statistic::all_abilities[] = {Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma};

static int abilities_cost[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	2, 3, 4, 5, 7, 9};

int statistic::getabilityscores() const {
	auto r = 0;
	for(auto v : all_abilities)
		r += maptbl(abilities_cost, abilities[v]);
	return r;
}

int statistic::getabilityscore(int v) {
	return maptbl(abilities_cost, v);
}