#include "main.h"

static void addh(stringbuilder& sb, const char* title) {
	sb.addn("[!");
	sb.add(title);
	sb.add(":]");
}

static void addlu(stringbuilder& sb, variant v, int level) {
	for(auto& e : bsdata<levelupi>()) {
		if(e.object != v || e.level != level)
			continue;
		addh(sb, e.name);
		if(strcmp(e.id, "Speed") == 0) {
			creaturei player = {};
			player.set(Speed, 6);
			player.apply(e.source);
			sb.adds(e.text, player.get(Speed) * 5);
		} else if(strcmp(e.id, "Ability Score Increase") == 0) {
			creaturei player = {};
			for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
				player.set(i, 10);
			auto first = false;
			player.apply(e.source);
			for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
				if(player.get(i) == 10)
					continue;
				if(first)
					sb.add(",");
				sb.adds("%1%+2i", bsdata<abilityi>::elements[i].name, player.get(i) - 10);
				first = true;
			}
			sb.adds(e.text, player.get(Speed) * 5);
		} else
			sb.adds(e.text);
	}
}

template<> const char* getinfo<racei>(const void* object, stringbuilder& sb) {
	auto p = (racei*)object;
	sb.add(p->text);
	addlu(sb, variant(p), 0);
	return sb.begin();
}