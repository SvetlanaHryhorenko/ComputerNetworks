// Client.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define N 1
#define M 2

using namespace std;

int sendTCP()
{
	struct sockaddr_in peer;
	int s, rc;
	float bufferFloat[N];
	long bufferLong[M];

	for (int i = 0; i < N; i++)
		bufferFloat[i] = (i + 10) * 16;

	for (int i = 0; i < M; i++)
		bufferLong[i] = i + 1;

	peer.sin_family = AF_INET;
	peer.sin_port = htons(7500);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");

	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)//функція ініціалізації Winsock.
	{
		cout << "Failed to load Winsock library!" << endl;
		system("pause");
		return 0;
	}

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		cout << "Socket call error" << endl;
		system("pause");
		return 0;
	}

	rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
	if (rc)
	{
		cout << "Connect call error" << endl;
		system("pause");
		return 0;
	}

	rc = send(s, (char*)bufferFloat, N*sizeof(float), 0);
	if (rc <= 0)
	{
		cout << "Error during sending the message" << endl;
		system("pause");
		return 0;
	}

	rc = recv(s, (char *)bufferLong, M*sizeof(long), 0);
		cout << "Recieved message: " << endl;
	for (int i = 0; i < M; i++)
		cout << bufferLong[i] << endl;
	/*rc = send(s, (char*)bufferLong, M*sizeof(long), 0);
	if (rc <= 0)
	{
		cout << "Error during sending the message" << endl;
		system("pause");
		return 0;
	}

	
	rc = recv(s, (char*)bufferFloat, N*sizeof(int), 0);
	if (rc <= 0)
	{
		cout << "Error during receiving the message" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "Sent message (integers):" << endl;
		for (int i = 0; i < N; i++)
			cout << bufferFloat[i] << endl;
	}
	cout << endl;

	rc = recv(s, (char*)bufferLong, M*sizeof(char), 0);
	if (rc <= 0)
	{
		cout << "Error during receiving the message" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "Sent message (chars):" << endl;
		for (int i = 0; i < M; i++)
			cout << bufferLong[i] << endl;
	}
	cout << endl;
	*/
	system("pause");
	return 0;
}

int sendUDP()
{
	struct sockaddr_in peer;
	float bufferFloat[N];
	for (int i = 0; i < N; i++)
		bufferFloat[i] = (i + 10) * 16.18;

	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		cout << "Failed to load Winsock library!" << endl;
		system("pause");
		return 0;
	}

	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);//Создает конечную точку соединения и возвращает ее описатель.
	peer.sin_family = AF_INET;/*набор протоколов*/
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	peer.sin_port = htons(7500);

	/*if (sendto(s, (char*)bufferFloat, sizeof(int)*N, 0, (struct sockaddr *)&peer, sizeof(peer)) < 0)
	{
		cout << "Error during sending the message" << endl;
		closesocket(s);
		WSACleanup();
		system("pause");
		return 0;
	}
	*/
	while(sendto(s, (char*)bufferFloat, sizeof(int)*N, 0, (struct sockaddr *)&peer, sizeof(peer)) >= 0)
	{cout << "Sending was successful!" << endl;}
	system("pause");
	closesocket(s);
	return 0;
}
int main()
{
	sendTCP();
	//sendUDP();
	return 0;
}
