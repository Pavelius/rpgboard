#include "main.h"

BSDATA(generatei) = {
	{"ChooseAbilities", 3},
	{"ChooseAlignment", 4},
	{"ChooseBackground", 4},
	{"ChooseClass", 2},
	{"ChooseGender", 4},
	{"ChooseRace", 1},
};
assert_enum(generatei, ChooseRace)

void creaturei::finish() {
	//	setbase();
}

void creaturei::create(race_s race, class_s clas, gender_s gender) {
	clear();
	setkind(race);
	random_ability(clas);
	set(clas, 1);
	apply(race, 0, false);
	apply(clas, 0, false);
	apply(race, 1, false);
	apply(clas, 1, false);
	finish();
}

static variant choose_step(variantc& source, generate_s id, bool interactive, bool sort) {
	if(!interactive)
		return source.random();
	char temp[260]; stringbuilder sb(temp);
	sb.add("��� %1i.", bsdata<generatei>::elements[id].index);
	sb.adds(bsdata<generatei>::elements[id].name);
	sb.add(".");
	if(sort)
		source.sort();
	variant v1 = source.chooseg(temp, bsdata<generatei>::elements[id].text);
	source.clear();
	return v1;
}

static variant choose_race(bool interactive) {
	variantc source(bsdata<racei>::source);
	source.matchbs(true);
	variant v1 = choose_step(source, ChooseRace, interactive, true);
	source.select(bsdata<racei>::source);
	source.matchbs(false);
	source.match(v1, true);
	if(source) {
		source.sort();
		v1 = choose_step(source, ChooseRace, interactive, true);
	}
	return v1;
}

static variant choose_class(bool interactive) {
	variantc source(bsdata<classi>::source);
	source.sort();
	return choose_step(source, ChooseClass, interactive, true);
}

static variant choose_alignment(bool interactive) {
	variantc source(bsdata<alignmenti>::source);
	source.sort();
	return choose_step(source, ChooseAlignment, interactive, true);
}

static variant choose_gender(bool interactive) {
	variantc source(bsdata<genderi>::source);
	source.sort();
	return choose_step(source, ChooseGender, interactive, true);
}

static variant choose_background(bool interactive) {
	variantc source(bsdata<backgroundi>::source);
	source.sort();
	return choose_step(source, ChooseBackground, interactive, true);
}

static int compare_best_ability(const void* p1, const void* p2) {
	return *((char*)p2) - *((char*)p1);
}

static int random_4d6() {
	char source[4];
	for(auto& e : source)
		e = rand() % 6 + 1;
	qsort(source, sizeof(source) / sizeof(source[0]), sizeof(source[0]), compare_best_ability);
	return source[0] + source[1] + source[2];
}

//void creaturei::random_ability(class_s c) {
//	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
//		abilities[i] = (rand() % 6) + (rand() % 6) + (rand() % 6) + 3;
//	auto maximum = Strenght; int maximum_value = abilities[Strenght];
//	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
//		if(abilities[i] > maximum_value) {
//			maximum_value = abilities[i];
//			maximum = i;
//		}
//	}
//	iswap(abilities[maximum], abilities[bsdata<classi>::elements[c].ability]);
//}

void statistic::random_ability(class_s clas) {
	char temp[6];
	for(auto& e : temp)
		e = random_4d6();
	qsort(temp, sizeof(temp) / sizeof(temp[0]), sizeof(temp[0]), compare_best_ability);
	adat<ability_s, 6> source;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		source.add(i);
	source.shuffle();
	auto& ei = bsdata<classi>::elements[clas];
	for(unsigned i = 0; i < sizeof(ei.abilities) / sizeof(ei.abilities[0]); i++) {
		auto im = source.indexof(ei.abilities[i]);
		if(im == -1)
			continue;
		iswap(source[i], source[im]);
	}
	for(unsigned i = 0; i < sizeof(temp) / sizeof(temp[0]); i++)
		abilities[source[i]] = temp[i];
}

bool statistic::choose_ability(generate_s id) {
	char temp[260]; stringbuilder sb(temp);
	sb.add("��� %1i.", bsdata<generatei>::elements[id].index);
	sb.adds(bsdata<generatei>::elements[id].name);
	sb.add(".");
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		abilities[i] = 10;
	return choose_ability(temp, bsdata<generatei>::elements[id].text, 27);
}

void creaturei::generate(bool interactive) {
	variant v;
	v = choose_race(false);
	if(!v)
		return;
	auto race = (race_s)v.value;
	v = choose_class(false);
	if(!v)
		return;
	//auto cls = (class_s)v.value;
	auto cls = Rogue;
	if(false)
		choose_ability(ChooseAbilities);
	else
		random_ability(cls);
	v = choose_gender(false);
	if(!v)
		return;
	auto gender = (gender_s)v.value;
	v = choose_alignment(false);
	if(!v)
		return;
	auto alignment = (alignment_s)v.value;
	//v = choose_background(interactive);
	v = Criminal;
	if(!v)
		return;
	auto background = (background_s)v.value;
	auto race_parent = bsdata<racei>::elements[race].base;
	set(cls, 1);
	if(race_parent != race)
		apply(race_parent, 0, false);
	apply(race, 0, false);
	apply(background, 0, false);
	apply(cls, 1, interactive);
	finish();
}