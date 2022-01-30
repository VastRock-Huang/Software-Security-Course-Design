#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{

	/*��ʼ���׽��ֿ�*/
	//WinSock�汾
	WORD wVersionRequested = MAKEWORD(2, 2);		//�������ֽ���ϳ�1���ֽ�, ��ʾ�汾��
	WSADATA wsaData;	//�׽�����Ϣ
	int err = WSAStartup(wVersionRequested, &wsaData);		//�����׽��ֿ�
	if (err)
	{
		//cout << "Load Socket Failed!\n";
		return 0;
	}
	//�жϼ��ص��׽��ְ汾�Ƿ����
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return 0;
	}

	/*�����׽���*/
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);		//�������׽���
	//SOCK_STREAM��ʾ��ʽ�׽���(��ӦTCP)
	if (socketServer == INVALID_SOCKET)
	{
		//cout << "Socket ERROR!";
		return 0;
	}

	/*���׽��ֵ����ص�ַ�Ͷ˿�*/
	//SOCKADDR_IN����socket����͸�ֵ��SOCKADDR���ں�������, ��Ϊ�洢IP��ַ�Ľṹ��
	SOCKADDR_IN serverAddr;		//����˵�ַ��Ϣ�ṹ
	serverAddr.sin_family = AF_INET;	//IPV4��ַ
	serverAddr.sin_addr.S_un.S_addr = htons(INADDR_ANY);	//0.0.0.0  �����ַ
	serverAddr.sin_port = htons(5555);		//�˿ں�
	if (bind(socketServer, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		//cout << "Bind Failed!\n";
		//cout << GetLastError() << endl;
		closesocket(socketServer);
		return 0;
	}
	else
		//cout << "Bind!\n";

	/*�����׽���Ϊ����״̬*/
	if (listen(socketServer, 5) < 0)	//���ȴ���ĿΪ5
		//cout << "Listen Failed!\n";
	else
		//cout << "Listen!\n";

	/*��������*/
	SOCKADDR_IN clientAddr;		//�ͻ��˵�ַ��Ϣ�ṹ
	int cliAddrLen = sizeof(SOCKADDR);		//��ʾSOCKADDR��С

	//���ܿͻ��˵ķ�������, �ȴ��ͻ���connect����
	SOCKET socketRecv = accept(socketServer, (SOCKADDR*)&clientAddr, &cliAddrLen);		//�������ӵ��׽���
	if (socketRecv == SOCKET_ERROR)
		//cout << "Receive Connect Failed!\n";
	else
		//cout << "Connect!\n";

	const int  bufSize = 50;	//��������С
	char sendBuf[bufSize]="This is the Server Msg";		//�������ݻ�����
	char recvBuf[bufSize];		//�������ݻ�����

	/*��������*/
		//���������ӵ��׽����н�������
	//cout << "Waiting for data...\n";
	int recvLen = recv(socketRecv, recvBuf, bufSize, 0);
	if (recvLen <= 0) {
		//cout << "Receive Failed!\n Exit!\n";
	}
	else
		//cout << "Client say:" << recvBuf << endl;
	memset(recvBuf, 0, bufSize);

	/*��������*/
	int sendLen = send(socketRecv, sendBuf, bufSize, 0);	//���������ӷ�ʽ���׽��ּ䷢������
	if (sendLen < 0)
		//cout << "Send Failed!";
	else
		//cout << "Send :" << sendBuf;
	memset(sendBuf, 0, bufSize);

	//�ر��׽���
	closesocket(socketRecv);
	closesocket(socketServer);
	//�ر����ӿ�
	WSACleanup();

	return 0;
}
