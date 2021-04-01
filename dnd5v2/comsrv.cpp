#include "comsrv.h"
#include "stringbuilder.h"

extern "C" int						strcmp(const char* s1, const char* s2);
extern "C" void*					memset(void* destination, int value, unsigned size);

using namespace comsrv;

nameable::nameable(const char* v) {
	stringbuilder sb(id);
	sb.add(v);
}

bool nameable::operator==(const char* v) const {
	return strcmp(id, v) == 0;
}

bool nameable::operator!=(const char* v) const {
	return strcmp(id, v) != 0;
}

void nameable::clear() {
	memset(this, 0, sizeof(*this));
}

bool hello::check(int major, int minor) const {
	if(this->major < major)
		return false;
	else if(this->major == major) {
		if(this->minor < minor)
			return false;
	}
	return true;
}