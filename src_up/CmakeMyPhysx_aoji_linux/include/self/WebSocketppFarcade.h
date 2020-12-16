#pragma once
#include<iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>
#include<functional>
using namespace std;
namespace WebSocketppFarcade
{
	void Listen();
	void Connect(string uri);
	void Send(string message);
	void Close();

	void SetRecieveMessage(function<void(string)> func);
}

