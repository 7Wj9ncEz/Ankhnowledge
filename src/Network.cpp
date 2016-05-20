/*
 * Network.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: al
 */

#include "Network.h"
#include <iostream>

IPaddress Network::ip, * Network::receiverIp;
int Network::rc, Network::id;
TCPsocket Network::currentSocket, Network::communicationSocket;
char Network::buffer[512];
vector<string> Network::messageQueue;
SDL_Thread * Network::thread,* Network::lThread;
bool Network::end_game, Network::connected, Network::first_time, Network::lost, Network::disconnected;
bool Network::cancel;
SDL_mutex *Network::mutex, *Network::mutex2;
int Network::player_1_selection, Network::player_2_selection;

Network::Network() {

}

void Network::init(){
	rc = SDLNet_Init();

	if (rc == -1)
	{
		cout << "Erro na inicializacao da NET: " << SDLNet_GetError() << endl;
	}
	connected = 0;
	currentSocket = 0;
	communicationSocket = 0;
	end_game = false;
	mutex = SDL_CreateMutex();
	mutex2 = SDL_CreateMutex();
	id = -1;
	first_time = false;
	lost = false;
	disconnected = false;
	Network::cancel = false;
	player_1_selection = 0;
	player_2_selection = 0;

}

void Network::finish(){

	messageQueue.clear();

	SDL_KillThread(thread);
	SDL_KillThread(lThread);
	SDL_DestroyMutex(mutex);

	if (currentSocket)
	{
		SDLNet_TCP_Close(currentSocket);
	}
	
	if (communicationSocket)
	{
		SDLNet_TCP_Close(communicationSocket);
	}
	SDLNet_Quit();
}

Network::~Network() {


}

int Network::connect(string ipaddress){

	rc = SDLNet_ResolveHost(&ip, ipaddress.c_str(), 3000);

	if (rc == -1)
	{
		return -1;
	}

	communicationSocket = SDLNet_TCP_Open(&ip);

	if (communicationSocket == NULL)
	{
		return -1;
	}

	id = 2;
	connected = true;
	first_time = true;
	lost = false;

	return 0;
}

void Network::disconnect(){

}

void Network::send_message(string message){
	if (SDLNet_TCP_Send(communicationSocket, (void *) message.c_str(), message.size()+1) < (int)message.size())
	{
		cout << "Erro no envio da MENSAGEM: " << SDLNet_GetError() << endl;
		return;
	}
}

int Network::receive_message(void *){

	while((connected))
	{
		//cout<<"trying to receive message"<<endl;

		if (SDLNet_TCP_Recv(communicationSocket, buffer, 512) > 0)
		{
			if (SDL_mutexP(mutex) == 0)
			{
				string message = buffer;
				//cout<<"recebi a msn: "<<message<<endl;
				messageQueue.push_back(message);
				SDL_mutexV(mutex);
			}
			else
			{
				cout<<"mutex nao funcionou"<<endl;
			}

		}else
		{
			connected = false;
			if (GameManager::current_scene->change_scene("SceneMainMenu") == 1)
					GameManager::fade_screen->fade_in(1,2);
			if (currentSocket)
			{
				SDLNet_TCP_Close(currentSocket);
			}

			if (communicationSocket)
			{
				SDLNet_TCP_Close(communicationSocket);
			}
			currentSocket = NULL;
			communicationSocket = NULL;
			id = -1;
			disconnected = true;
		}

	}

	return 0;
}

void Network::receive_thread(){
	thread = SDL_CreateThread(receive_message, NULL);
}

void Network::listening_thread(){
	lThread = SDL_CreateThread(listening, NULL);
}

string Network::read_message()
{
	string message = "";
	if (SDL_mutexP(mutex) == 0)
	{
		if(!messageQueue.empty())
		{
			message = messageQueue.at(0);
			messageQueue.erase(messageQueue.begin());

		}
	SDL_mutexV(mutex);
	}
	return message;
}

int Network::host()
{
	rc = SDLNet_ResolveHost(&ip, NULL, 3000);

	if (rc == -1)
	{
		return -1;
	}

	currentSocket = SDLNet_TCP_Open(&ip);

	if (currentSocket == NULL)
	{
		return -1;
	}

	listening_thread();

	return 0;
}

int Network::listening(void *)
{
	while(!connected)
	{
		if (SDL_mutexP(mutex2) == 0)
		{
			if (cancel)
			{
				SDL_mutexV(mutex2);
				break;
			}
			SDL_mutexV(mutex2);
		}

		
		if((communicationSocket = SDLNet_TCP_Accept(currentSocket)))
		{
			connected = true;
			first_time = true;
			lost = false;
			id = 1;
			
		}
		SDL_Delay(1);
	}

	return 0;

}

void Network::close_connection(){
	if (currentSocket)
	{
		SDLNet_TCP_Close(currentSocket);
	}

	if (communicationSocket)
	{
		SDLNet_TCP_Close(communicationSocket);
	}
}

int Network::get_id()
{
	return id;
}

bool Network::is_first_time()
{
	return first_time;
}

bool Network::did_lose()
{
	return lost;
}

void Network::set_lost(bool value)
{
	lost = value;
}

void Network::set_first_time(bool value)
{
	first_time = value;
}

