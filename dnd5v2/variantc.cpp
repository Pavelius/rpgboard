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
		switch(e.type) {
		case Race: result = variant(bsdata<racei>::elements[e.value].base) == v; break;
		}
		if(result != keep)
			continue;
		*p++ = e;
	}
	count = p - data;
}

void variantc::match(state_s v, bool keep) {
	auto p = data;
	for(auto e : *this) {
		auto result = false;
		switch(e.type) {
		case Creature:
			result = bsdata<creaturei>::elements[e.value].is(v);
			break;
		default: continue;
		}
		if(result != keep)
			continue;
		*p++ = e;
	}
	count = p - data;
}

void variantc::match(action_s v, bool keep) {
	auto p = data;
	for(auto e : *this) {
		auto result = false;
		switch(e.type) {
		case Creature:
			result = bsdata<creaturei>::elements[e.value].is(v);
			break;
		default: continue;
		}
		if(result != keep)
			continue;
		*p++ = e;
	}
	count = p - data;
}

static unsigned distancef(point p1, point p2) {
	auto dx = iabs(p1.x - p2.x);
	auto dy = iabs(p1.y - p2.y);
	return dx > dy ? dx : dy;
}

void variantc::range(point start, unsigned v, bool keep) {
	auto p = data;
	for(auto e : *this) {
		point pt;
		switch(e.type) {
		case Creature:
			pt.x = bsdata<creaturei>::elements[e.value].x;
			pt.y = bsdata<creaturei>::elements[e.value].y;
			break;
		default:
			continue;
		}
		auto result = distancef(start, pt) <= v;
		if(result != keep)
			continue;
		*p++ = e;
	}
	count = p - data;
}

static const char* tips_variant(const void* object, stringbuilder& sb) {
	auto pv = (variant*)object;
	return pv->getinfo(sb);
}

variant	variantc::choose(const char* title, int score) const {
	if(getcount() == 1)
		return data[0];
	answers aw;
	for(auto v : *this) {
		int i;
		*((variant*)&i) = v;
		aw.add(i, v.getname());
	}
	auto result = aw.choose(title, false, true, tips_variant);
	if(!result)
		return variant();
	return *((variant*)&result);
}
