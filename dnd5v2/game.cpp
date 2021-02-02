#include "main.h"

gamei game;

void gamei::combat() {
	while(true) {
		variantc creatures(bsdata<creaturei>::source);
		creatures.match(Active, true);
		for(auto v : creatures) {
			auto p = v.getcreature();
			if(!p)
				continue;
			p->beforecombatround();
		}
		for(auto v : creatures) {
			auto p = v.getcreature();
			if(!p)
				continue;
			p->uicombat();
		}
		for(auto v : creatures) {
			auto p = v.getcreature();
			if(!p)
				continue;
			p->aftercombatround();
		}
	}
}