#include "socket.h"
#include "crt.h"

namespace {
class server {
	char			uid[16];
	char			name[32];
	unsigned		time_start;
	unsigned		time_active;
public:
	void			start();
	void			send(void* data, unsigned size);
};
class client : public socket {
	char			name[32];
	char			command[2048];
	server*			host;
	unsigned		time_start;
	unsigned		time_active;
public:
	server*			getserver() const { return host; }
	void			read();
};
}
BSDATAC(server, 32)
BSDATAC(client, 32 * 16)