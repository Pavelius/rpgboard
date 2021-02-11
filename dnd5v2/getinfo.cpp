#include "main.h"

static void addh(stringbuilder& sb, const char* title) {
	sb.addn("**");
	sb.add(title);
	sb.add(":**");
}

static void addlu(stringbuilder& sb, variant v, int level) {
	for(auto& e : bsdata<levelupi>()) {
		if(e.object != v || e.level != level)
			continue;
		addh(sb, e.name);
		sb.adds(e.text);
	}
}

template<> const char* getinfo<racei>(const void* object, stringbuilder& sb) {
	auto p = (racei*)object;
	sb.add(p->text);
	addlu(sb, variant(p), 0);
	return sb.begin();
}