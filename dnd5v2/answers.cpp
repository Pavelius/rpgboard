#include "main.h"

int answers::compare(const void* v1, const void* v2) {
	return strcmp(((answers::element*)v1)->text, ((answers::element*)v2)->text);
}

answers::answers() : sc(buffer) {}

void answers::addv(int id, const char* text, const char* format) {
	auto p = elements.add();
	p->id = id;
	p->text = sc.get();
	sc.addv(text, format);
	sc.addsz();
}

void answers::sort() {
	qsort(elements.data, elements.count, sizeof(elements.data[0]), compare);
}

int	answers::random() const {
	if(!elements.count)
		return 0;
	return elements.data[rand() % elements.count].id;
}

int	answers::choose(const char* title, bool allow_cancel, bool interactive, fntext tips) const {
	auto r = choosev(title, allow_cancel ? "Îòìåíà" : 0, interactive, ResNone, 0, 0, 0, tips);
	if(!r)
		return 0;
	return r->id;
}