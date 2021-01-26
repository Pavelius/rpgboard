#include "main.h"

#define META(T) bsdata<T>::source_ptr
#define METANN(T) bsdata<T>::source_ptr
#define LOCMN(T) {FO(T, name),FO(T, text)}, {}, getinfo<T>

BSDATA(varianti) = {{""},
	{"Ability", META(abilityi), LOCMN(abilityi)},
	{"Alignment", META(alignmenti), LOCMN(alignmenti)},
	{"Background", META(backgroundi), LOCMN(backgroundi)},
	{"Class", META(classi), LOCMN(classi)},
	{"Creature", METANN(creaturei)},
	{"Damage", META(damagei)},
	{"Domain", META(domaini), LOCMN(domaini)},
	{"FightingStyle", META(fighting_stylei), LOCMN(fighting_stylei)},
	{"Gender", META(genderi), LOCMN(genderi)},
	{"Generate", META(generatei), LOCMN(generatei)},
	{"Item", META(itemi), LOCMN(languagei)},
	{"Language", META(languagei), LOCMN(languagei)},
	{"Levelup", META(levelupi), LOCMN(levelupi)},
	{"Menu", META(menu), LOCMN(menu)},
	{"Modifier"},
	{"Pack", META(packi), LOCMN(packi)},
	{"Race", META(racei), LOCMN(racei)},
	{"Save", META(savei)},
	{"School", META(schooli), LOCMN(schooli)},
	{"Skill", META(skilli), LOCMN(skilli)},
	{"Spell", META(spelli), LOCMN(spelli)},
	{"Trait", META(traiti)},
};
assert_enum(varianti, Trait)

variant::variant(const void* v) {
	for(auto& e : bsdata<varianti>()) {
		if(!e.source)
			continue;
		auto i = e.source->indexof(v);
		if(i == -1)
			continue;
		type = (variant_s)(&e - bsdata<varianti>::elements);
		value = i;
		return;
	}
	type = NoVariant;
	value = 0;
}

void* variant::getobject() const {
	auto& e = bsdata<varianti>::elements[type];
	if(!e.source)
		return 0;
	return e.source->ptr(value);
}

const char* variant::getname() const {
	auto& e = bsdata<varianti>::elements[type];
	if(!e.source || !e.locale[0])
		return "No name";
	return *((const char**)((char*)e.source->ptr(value) + e.locale[0]));
}

const char* variant::getinfo(stringbuilder& sb) const {
	auto& e = bsdata<varianti>::elements[type];
	if(!e.source || !e.getinfo)
		return 0;
	return e.getinfo(e.source->ptr(value), sb);
}

static void checklocalization() {
#ifdef _DEBUG
	for(auto& e : bsdata<varianti>()) {
		if(!e.source || !e.locale[0])
			continue;
		for(unsigned i = 0; i < e.source->getcount(); i++) {
			auto p = (char*)e.source->ptr(i);
			auto id = *((const char**)(p));
			auto p1 = *((const char**)(p + e.locale[0]));
			if(!p1 || !p1[0]) {
				//draw::mslog("Empthy name for [%1] type in element [-%2]", e.id, id);
			}
		}
	}
#endif
}

bool savel(const char* url, array& source, unsigned* fields, int fields_count, unsigned* special, int special_count);
bool readl(const char* url, array& source, unsigned* fields, int fields_count, unsigned* special, int special_count);

void varianti::localization(const char* locale_id, bool writemode) {
	const auto fields_count = sizeof(varianti::locale) / sizeof(varianti::locale[0]);
	for(auto& e : bsdata<varianti>()) {
		if(!e.source || !e.locale[1])
			continue;
		char temp[260]; stringbuilder sb(temp);
		sb.add("locale/%1/%2.txt", locale_id, e.id);
		auto special_count = zlen(e.special);
		if(writemode)
			savel(temp, *e.source, e.locale, fields_count, e.special, special_count);
		else
			readl(temp, *e.source, e.locale, fields_count, e.special, special_count);
	}
	if(!writemode)
		checklocalization();
}