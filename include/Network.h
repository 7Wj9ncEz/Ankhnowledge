/*
 * Network.h
 *
 *  Created on: Sep 24, 2013
 *      Author: al
 */

#ifndef NETWORK_H_
#define NETWORK_H_
using namespace std;
#include <string>
#include "SDL/SDL_net.h"
#include <vector>
#include "SDL/SDL_thread.h"
#include "GameManager.h"

using namespace std;

class Network {
public:
	static void init();
	static void finish();
	virtual ~Network();
	static int connect(string ipaddress);
	static int listening(void *);
	static void disconnect();
	static void send_message(string message);
	static int receive_message(void *);
	static void receive_thread();
	static string read_message();
	static void close_connection();
	static int contagem(void *);
	static int host();
	static int get_id();
	static bool is_first_time();
	static void set_first_time(bool value);
	static bool did_lose();
	static void set_lost(bool value);
	static bool end_game, connected, disconnected,cancel;
	static void listening_thread();
	static SDL_mutex *mutex2;
	static int player_1_selection;
	static int player_2_selection;

private:
	static int rc;
	static TCPsocket currentSocket, communicationSocket;
	static IPaddress ip, *receiverIp;
	static char buffer[512];
	Network();
	static vector<string> messageQueue;
	static SDL_Thread *thread,*lThread;
	static SDL_mutex *mutex;
	static int id;
	static bool first_time;
	static bool lost;

};

#endif /* NETWORK_H_ */
