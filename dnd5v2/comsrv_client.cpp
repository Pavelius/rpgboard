#include "comsrv.h"
#include "crt.h"
#include "socket.h"

using namespace comsrv;

static io::sock			s;

static void write(const void* data, unsigned size) {
	if(!s)
		return;
	while(size) {
		auto r = s.write(data, size);
		if(r <= 0) {
			s.stop();
			s.close();
			return;
		}
		size -= r;
		data = (char*)data + r;
	}
}

void comsrv::post(type_s code, int p1, int p2) {
	packet result = {};
	result.type = code;
	result.p1 = p1;
	result.p2 = p2;
	write(&result, sizeof(result));
}

void comsrv::post(type_s code, const void* data, unsigned size, int p2) {
	post(code, size, p2);
	write(data, size);
}

static bool read(void* data, unsigned size) {
	if(!s)
		return false;
	while(size) {
		auto r = s.read(data, size);
		if(r <= 0) {
			s.stop();
			s.close();
			return false;
		}
		size -= r;
		data = (char*)data + r;
	}
	return true;
}

static bool read(packet& e) {
	return read(&e, sizeof(e));
}

bool comsrv::connect(const char* url, const char* port, type_s querry, const char* chat, const char* user, const char* password) {
	if(s.open(url, port) != 0)
		return false;
	hello header = {};
	header.protocol = COMSRV_NAME;
	header.minor = minor;
	header.major = major;
	header.chat = chat;
	header.user = user;
	header.password = password;
	post(querry, &header, sizeof(header));
	packet result = {}; read(result);
	if(result.type != NoError)
		return false;
	return true;
}

void comsrv::disconnect() {
	s.stop();
	s.close();
}