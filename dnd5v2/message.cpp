#include "main.h"

void lock_message();
void unlock_message();

static vector<char> messages;

void msgv(const char* format, const char* format_param) {
	lock_message();
	unlock_message();
}