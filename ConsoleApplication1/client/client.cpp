// client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "websocket_client.h"
#include <iostream>

int main()
{
	Client websocket_client("127.0.0.1", 19201);
	if (!websocket_client.Connect())
	{
		std::cout << "connect fail";
	}

	system("pause");
    return 0;
}

