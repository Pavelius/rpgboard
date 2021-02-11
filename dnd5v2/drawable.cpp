#include "main.h"
#include "draw.h"

BSDATAC(drawable, 32)

bool drawable::change_position;

void drawable::setframe(resource_s rid, int frame) {
	this->rid = rid;
	this->frame = frame;
}

void drawable::setmirrorh(bool v) {
	if(v)
		flags |= ImageMirrorH;
	else
		flags &= ~ImageMirrorH;
}

void drawable::setmirrorv(bool v) {
	if(v)
		flags |= ImageMirrorV;
	else
		flags &= ~ImageMirrorV;
}

void drawable::setposition(point v) {
	if(x != v.x) {
		x = v.x;
		change_position = true;
	}
	if(y != v.y) {
		y = v.y;
		change_position = true;
	}
}

bool drawable::ischangedposition(const void* object) {
	return change_position;
}

bool drawable::isblocked(int px, int py) const {
	auto x = px - this->x;
	auto y = py - this->y;
	return false;
}