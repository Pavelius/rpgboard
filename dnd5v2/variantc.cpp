#include "main.h"

static int compare(const void* v1, const void* v2) {
	auto p1 = (variant*)v1;
	auto p2 = (variant*)v2;
	return strcmp(p1->getname(), p2->getname());
}

void variantc::sort() {
	qsort(data, count, sizeof(data[0]), compare);
}

void variantc::select(const array& source) {
	auto sz = source.getsize();
	auto pe = source.end();
	for(auto p = source.begin(); p<pe; p += sz)
		add(p);
}

void variantc::exclude(variant v) {
	auto p = data;
	for(auto e : *this) {
		if(e == v)
			continue;
		*p++ = e;
	}
	count = p - data;
}

//variant variantc::chooseg(const char* step, const char* title, int score) const {
//	answers aw;
//	for(auto v : *this)
//		aw.add(v, v.getname());
//	return aw.chooseg(step, title, score);
//}

void variantc::matchbs(bool keep) {
	auto p = data;
	for(auto e : *this) {
		if(e.type == Race) {
			auto result = bsdata<racei>::elements[e.value].base == e.value;
			if(result != keep)
				continue;
		}
		*p++ = e;
	}
	count = p - data;
}

void variantc::match(variant v, bool keep) {
	auto p = data;
	for(auto e : *this) {
		auto result = false;
		if(e.type == Race)
			result = variant(bsdata<racei>::elements[e.value].base) == v;
		if(result != keep)
			continue;
		*p++ = e;
	}
	count = p - data;
}