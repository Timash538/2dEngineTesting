#pragma once
#include <WS2tcpip.h>
#include <iostream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class Server {
	void startupWinsock();
};