#include "main.h"
#include "comsrv.h"

bool network::connect() {
	return comsrv::connect("localhost", "9090", comsrv::CreateChat, "default", "pavel", "");
}

void network::disconnect() {

}