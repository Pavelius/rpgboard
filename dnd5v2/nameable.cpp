#include "main.h"

void nameablei::setkind(variant v) {
	*static_cast<variant*>(this) = v;
}

race_s nameablei::getrace() const {
	switch(type) {
	case Race: return race_s(value);
	default: return Human;
	}
}