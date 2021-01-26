#include "main.h"
#include "thread.h"
#include "mutex.h"
#include "socket.h"

static io::mutex message_guard;

void lock_message() {
	message_guard.lock();
}

void unlock_message() {
	message_guard.unlock();
}

static void client_run(void* param) {
	io::sock client;
	client.initialize();
	client.open("localhost", "27000");
	if(!client)
		return;
	while(true) {
		char temp[260];
		client.write(temp, sizeof(temp));
		char answer[260];
		client.read(answer, sizeof(answer));
	}
}
io::thread client_thread(client_run, 0);