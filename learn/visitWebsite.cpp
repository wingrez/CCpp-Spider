/*
	������վ
*/

#include<cstdio>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);

	char *domain="www.baidu.com";
	hostent *pHost= gethostbyname(domain);
	const char *pIp=inet_ntoa(*((struct in_addr *)pHost->h_addr));
	printf("%s\n", pIp);

	SOCKADDR_IN  webServerAddr;
	webServerAddr.sin_family = AF_INET;
	webServerAddr.sin_addr.S_un.S_addr=inet_addr(pIp);
	webServerAddr.sin_port = htons(80);

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	int nRet = connect(sockClient, (struct sockaddr*)&webServerAddr, sizeof(webServerAddr));

	if(nRet<0) {
		printf("��վ����ʧ�ܣ�\n");
	} else {
		printf("��վ���ӳɹ���\n");
	}
	
	closesocket(sockClient);
	WSACleanup();

	return 0;
}
