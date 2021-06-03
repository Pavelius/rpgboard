#include "comsrv.h"
#include "crt.h"
#include "socket.h"

using namespace comsrv;

static io::sock	s;

static bool read(void* data, unsigned size) {
	if(!s)
		return false;
	while(size) {
		auto r = s.read(data, size);
		if(r <= 0) {
			disconnect();
			return false;
		}
		size -= r;
		data = (char*)data + r;
	}
	return true;
}

static packet readresult() {
	packet result = {};
	if(!read(&result, sizeof(result)))
		return {InvalidRead, 0};
	return result;
}

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

void comsrv::post(type_s code, unsigned param) {
	packet result = {};
	result.type = code;
	result.param = param;
	write(&result, sizeof(result));
}

packet comsrv::post(type_s code, const void* data, unsigned size) {
	post(code, size);
	write(data, size);
	return readresult();
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
	return !post(querry, &header, sizeof(header));
}

void comsrv::disconnect() {
	s.stop();
	s.close();
}