// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define N 1
#define M 2
using namespace std;

int receiveTCP()
{
	struct sockaddr_in local; // информация об адресе клиента

	int s, s1,s2, rc;
	float bufferFloat[N];
	long bufferLong[M];

	local.sin_family = AF_INET;
	local.sin_port = htons(7500);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "Failed to load Winsock library!" << endl;
		system("pause");
		return 0;
	}
	s = socket(AF_INET, SOCK_STREAM, 0);//Создает конечную точку соединения и возвращает ее описатель.
	if (s == INVALID_SOCKET)
	{
		cout << "Call socket error";
		system("pause");
		return 0;
	}

	rc = bind(s, (struct sockaddr *)&local, sizeof(local));//привязати адресу інтерфейсу і номер порту до сокету, що прослуховує.
	if (rc < 0)
	{
		cout << "Call bind error";
		system("pause");
		return 0;
	}

	rc = listen(s, 5);// прослуховувати відомий йому порт
	if (rc)
	{
		cout << "Error during listening" << endl;
		system("pause");
		return 0;
	}

	s1 = accept(s, NULL, NULL);// повертає адресу додатку на іншому кінці зєднання в структурі sockaddr_in, на яку указує параметр addr.
	if (s1 < 0)
	{
		cout << "Error during accepting" << endl;
		system("pause");
		return 0;
	}
	/*s2 = accept(s, NULL, NULL);// повертає адресу додатку на іншому кінці зєднання в структурі sockaddr_in, на яку указує параметр addr.
	if (s2 < 0)
	{
		cout << "Error during accepting" << endl;
		system("pause");
		return 0;
	}
	*/
	rc = recv(s1, (char *)bufferFloat, N*sizeof(float), 0);
	if (rc <= 0)
	{
		cout << "Error during receiving" << endl;
		system("pause");
		return 0;
	}

	cout << "Recieved message: " << endl;
	for (int i = 0; i < N; i++)
		cout << bufferFloat[i] << endl;
	s2 = accept(s, NULL, NULL);
	rc = send(s2, (char*)bufferFloat, N*sizeof(float), 0);

	rc = recv(s2, (char *)bufferLong, M*sizeof(long), 0);
	rc = send(s1, (char*)bufferLong, M*sizeof(long), 0);
	if (rc <= 0)
	{
		cout << "Error during receiving" << endl;
		system("pause");
		return 0;
	}
	cout << endl;

	cout << "Recieved message: " << endl;
	for (int i = 0; i < M; i++)
		cout << bufferLong[i] << endl;

	cout << endl;
	system("pause");

	/*rc = send(s1, (char*)bufferFloat, M*sizeof(long), 0);
	if (rc <= 0)
	{
		cout << "Error during sending the message" << endl;
		system("pause");
		return 0;
	}


	//rc = send(s1, (char*)bufferLong, M*sizeof(char), 0);
	if (rc <= 0)
	{
		cout << "Error during sending the message" << endl;
		system("pause");
		return 0;
	}
	*/
	system("pause");

	return 0;
}

int receiveUDP()
{
	struct sockaddr_in local;
	int rc;
	float bufferFloat[N];

	local.sin_family = AF_INET;
	local.sin_port = htons(7500);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "Failed to load Winsock library!" << endl;
		system("pause");
		return 0;
	}

	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET)
	{
		cout << "Call socket error";
		system("pause");
		return 0;
	}

	rc = bind(s, (struct sockaddr *)&local, sizeof(local));
	if (rc < 0)
	{
		cout << "Error during binding";
		system("pause");
		return 0;
	}

	while (1)
	{
		struct sockaddr_in client;
		int client_addr_size = sizeof(client);
		rc = recvfrom(s, (char *)bufferFloat, N*sizeof(int), 0, (struct sockaddr *)&client, &client_addr_size);
		while(rc>=0)
		{
		cout << "Received message: " << endl;
		for (int i = 0; i < N; i++)
			cout << bufferFloat[i] << endl;
		break;
		}
		}

	system("pause");
	return 0;
}

int main()
{
	receiveTCP();
//	receiveUDP();
	return 0;
}

