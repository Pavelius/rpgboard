#pragma once

#define COMSRV_NAME "Communication server"

namespace comsrv {
enum type_s {
	NoError,
	InvalidQuerryType, InvalidP1, InvalidP2,
	InvalidInputFormat, InvalidProtocol, InvalidProtocolVersion, InvalidLoginOrPassword,
	CreateChat=1000, JoinChat, GetInfo, GetData, PutData, GetUsers,
};
const int			major = 0;
const int			minor = 1;
struct nameable {
	char			id[32];
	constexpr nameable() : id() {}
	nameable(const char* v);
	constexpr explicit operator bool() const { return id[0] != 0; }
	bool operator==(const char* v) const;
	bool operator!=(const char* v) const;
	void			clear();
};
struct resable : nameable {
	unsigned		rid;
};
struct hello {
	nameable		protocol;
	short			minor, major;
	nameable		chat;
	nameable		user;
	nameable		password;
	bool			check(int minor, int major) const;
};
struct user : resable {
	unsigned		roles;
	unsigned		last_activity;
	unsigned		last_update;
};
struct packet {
	type_s			type;
	int				p1, p2;
};
void				runserver(const char* port);
bool				connect(const char* url, const char* port, type_s querry, const char* chat, const char* user, const char* password);
void				disconnect();
void				post(type_s code, int p1, int p2);
void				post(type_s code, const void* data, unsigned size, int p2 = 0);
}
