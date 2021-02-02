#include "main.h"

typedef short unsigned indext;
const short unsigned mps = 32;
const indext Blocked = 0xFFFF;

static unsigned short	path_stack[256*4];
static unsigned char	path_push;
static unsigned char	path_pop;

inline int gx(indext i) {
	return i % mps;
}

inline int gy(indext i) {
	return i / mps;
}

inline indext gi(int x, int y) {
	return y * mps + x;
}

static indext to(indext i, direction_s d) {
	if(i == Blocked)
		return i;
	auto x = gx(i);
	auto y = gy(i);
	switch(d) {
	case Left: return (x <= 0) ? Blocked : gi(x - 1, y);
	case Right: return (x >= mps - 1) ? Blocked : gi(x + 1, y);
	case Up: return (y <= 0) ? Blocked : gi(x, y - 1);
	case UpLeft: return (x <= 0 || y <= 0) ? Blocked : gi(x - 1, y - 1);
	case UpRight: return (x >= mps - 1 || y <= 0) ? Blocked : gi(x + 1, y - 1);
	case Down: return (y >= mps - 1) ? Blocked : gi(x, y + 1);
	case DownLeft: return (x <= 0 || y >= mps - 1) ? Blocked : gi(x - 1, y + 1);
	case DownRight: return (x >= mps - 1 || y >= mps - 1) ? Blocked : gi(x + 1, y + 1);
	default: return Blocked;
	}
}

static void snode(indext index, short unsigned* pathmap, unsigned char* costmap, short unsigned cost) {
	if(index == Blocked)
		return;
	auto c = costmap[index];
	if(!c)
		return;
	auto a = pathmap[index] + c;
	if(a && cost + c >= a)
		return;
	path_stack[path_push++] = index;
	pathmap[index] = cost;
}

static void makewave(indext start, indext* pathmap, unsigned char* costmap) {
	if(start == Blocked || !pathmap)
		return;
	path_push = 0;
	path_pop = 0;
	path_stack[path_push++] = start;
	pathmap[start] = 1;
	while(path_push != path_pop) {
		auto i = path_stack[path_pop++];
		auto cost = pathmap[i];
		snode(to(i, Left), pathmap, costmap, cost);
		snode(to(i, Right), pathmap, costmap, cost);
		snode(to(i, Up), pathmap, costmap, cost);
		snode(to(i, Down), pathmap, costmap, cost);
		snode(to(i, UpLeft), pathmap, costmap, cost);
		snode(to(i, UpRight), pathmap, costmap, cost);
		snode(to(i, DownLeft), pathmap, costmap, cost);
		snode(to(i, DownRight), pathmap, costmap, cost);
	}
}