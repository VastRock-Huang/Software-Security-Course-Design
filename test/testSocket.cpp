#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


int main() {
	/*��ʼ���׽��ֿ�*/
	WORD wVersionRequested = MAKEWORD(2, 2);		//WinSock�汾
	WSADATA wsaData;		//�׽�����Ϣ
	int err = WSAStartup(wVersionRequested, &wsaData);	//�����׽��ֿ�
	if (err) {
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}

	/*�ͻ��˴����׽���*/
	SOCKET socketSend = socket(AF_INET, SOCK_STREAM, 0);
	//�ͻ����׽��ֲ���Ҫ��
	if (socketSend == INVALID_SOCKET) {
		//cout << "Socket ERROR!";
		return 0;
	}

	/*���ӷ�����*/
	//���÷�������ַ�˿�
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(5555);

	if (connect(socketSend, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		return 0;
	}
	const int bufSize = 50;
	char sendBuf[bufSize] = "74126985";		//�������ݻ�����
	char recvBuf[bufSize];		//�������ݻ�����

	int sendLen = send(socketSend, sendBuf, bufSize, 0);

	memset(sendBuf, 0, bufSize);

	int recvLen = recv(socketSend, recvBuf, bufSize, 0);
	memset(recvBuf, 0, bufSize);
	
	closesocket(socketSend);
	WSACleanup();
	return 0;
}