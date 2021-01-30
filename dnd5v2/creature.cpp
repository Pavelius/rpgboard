#include "main.h"

BSDATAC(creaturei, 128)

void creaturei::uicombat() {
	while(true) {
		answers aw;
		for(auto i = ActionAmbush; i <= ActionUseItem; i = (action_s)(i + 1)) {
			if(!use(i, false))
				continue;
			auto& e = bsdata<actioni>::elements[i];
			aw.add(variant(&e), e.name);
		}
		auto p = menu::choose(aw, "root", false);
		if(bsdata<menu>::source.indexof(p) != -1) {
			auto m = (menu*)p;
			if(m->command)
				m->command();
			menu::run(m->id);
		}
	}
}