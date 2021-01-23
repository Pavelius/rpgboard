#include "main.h"
#include "draw.h"

BSDATAC(drawable, 32)

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