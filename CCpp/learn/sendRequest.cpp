/*
	发送请求 
*/

#include<cstdio>
#include<winsock2.h>
//#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);

	const char *domain="www.baidu.com";
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
		printf("网站连接失败！\n");
		exit(1);
	} else {
		printf("网站连接成功！\n");
	}

	char szHttpRest[1024] = {0};
	sprintf(szHttpRest, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: Keep-Alive\r\n\r\n", domain);

	printf("发送请求：\n");
	printf("%s\n", szHttpRest);

	nRet = send(sockClient , szHttpRest, strlen(szHttpRest) + 1, 0);
	if(nRet<0) {
		printf("请求发送失败！\n");
	} else {
		printf("请求发送成功！\n");
	}
	
	closesocket(sockClient);
	WSACleanup();
	
	return 0;
}
