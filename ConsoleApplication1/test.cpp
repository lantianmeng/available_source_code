// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include<direct.h>

#include "cJSON.h"

std::string create_json() 
{
	cJSON * root =  cJSON_CreateObject();

	cJSON_AddItemToObject(root, "listenIp", cJSON_CreateString("0.0.0.0"));//根节点下添加
	cJSON_AddItemToObject(root, "listenPort", cJSON_CreateString("16000"));

	return cJSON_Print(root);
}

std::string create_client_json() 
{
	cJSON * root =  cJSON_CreateObject();

	cJSON_AddItemToObject(root, "serverIp", cJSON_CreateString("192.168.3.23"));//根节点下添加
	cJSON_AddItemToObject(root, "listenPort", cJSON_CreateString("16000"));
	cJSON_AddItemToObject(root, "keepalive", cJSON_CreateNumber(30000));

	return cJSON_Print(root);
}

std::string create_transParam_json() 
{
	cJSON * transParamUnit1_1 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit1_1, "transStreamType", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(transParamUnit1_1, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit1_1, "streamRate", cJSON_CreateNumber(128));

	cJSON * transParamUnit1_2 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit1_2, "transStreamType", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(transParamUnit1_2, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit1_2, "streamRate", cJSON_CreateNumber(512));

	cJSON * transParam1 = cJSON_CreateArray();
	cJSON_AddItemToArray(transParam1, transParamUnit1_1);
	cJSON_AddItemToArray(transParam1, transParamUnit1_2);

	cJSON * transChanelInfoUnit1 = cJSON_CreateObject();
	cJSON_AddItemToObject(transChanelInfoUnit1, "transChannelNum", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(transChanelInfoUnit1, "rspAddrIp", cJSON_CreateString("127.0.0.1"));//根节点下添加
	cJSON_AddItemToObject(transChanelInfoUnit1, "rspAddrPort", cJSON_CreateNumber(8888));
	cJSON_AddItemReferenceToObject(transChanelInfoUnit1, "transParam", transParam1);


	cJSON * transParamUnit2_1 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit2_1, "transStreamType", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(transParamUnit2_1, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit2_1, "streamRate", cJSON_CreateNumber(128));

	cJSON * transParamUnit2_2 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit2_2, "transStreamType", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(transParamUnit2_2, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit2_2, "streamRate", cJSON_CreateNumber(512));

	cJSON * transParam2 = cJSON_CreateArray();
	cJSON_AddItemToArray(transParam2, transParamUnit2_1);
	cJSON_AddItemToArray(transParam2, transParamUnit2_2);

	cJSON * transChanelInfoUnit2 = cJSON_CreateObject();
	cJSON_AddItemToObject(transChanelInfoUnit2, "transChannelNum", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(transChanelInfoUnit2, "rspAddrIp", cJSON_CreateString("127.0.0.1"));//根节点下添加
	cJSON_AddItemToObject(transChanelInfoUnit2, "rspAddrPort", cJSON_CreateNumber(8888));
	cJSON_AddItemReferenceToObject(transChanelInfoUnit2, "transParam", transParam2);

	cJSON * transChanelInfos = cJSON_CreateArray();
	cJSON_AddItemToArray(transChanelInfos, transChanelInfoUnit1);
	cJSON_AddItemToArray(transChanelInfos, transChanelInfoUnit2);

	cJSON * root =  cJSON_CreateObject();
	cJSON_AddItemReferenceToObject(root, "transChanelInfos", transChanelInfos);

	return cJSON_Print(root);
}

std::string createJsonOkContent()
{
	cJSON * root =  cJSON_CreateObject();
	
	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(200));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString("OK"));

	return cJSON_Print(root);
}

std::string createJsonOkContent( const std::string & sessionId )
{
	cJSON * root =  cJSON_CreateObject();

	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(200));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString("OK"));
	cJSON_AddItemToObject(root, "sessionId", cJSON_CreateString(sessionId.c_str()));

	return cJSON_Print(root);
}

std::string createJsonQueryTransCoderStatusInfo() 
{
	cJSON * transParamUnit1_1 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit1_1, "transStreamType", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(transParamUnit1_1, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit1_1, "streamRate", cJSON_CreateNumber(128));
	cJSON_AddItemToObject(transParamUnit1_1, "isDistribute", cJSON_CreateNumber(0));

	cJSON * transParamUnit1_2 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit1_2, "transStreamType", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(transParamUnit1_2, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit1_2, "streamRate", cJSON_CreateNumber(512));
	cJSON_AddItemToObject(transParamUnit1_2, "isDistribute", cJSON_CreateNumber(0));

	cJSON * transParam1 = cJSON_CreateArray();
	cJSON_AddItemToArray(transParam1, transParamUnit1_1);
	cJSON_AddItemToArray(transParam1, transParamUnit1_2);

	cJSON * transChanelInfoUnit1 = cJSON_CreateObject();
	cJSON_AddItemToObject(transChanelInfoUnit1, "transChannelNum", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(transChanelInfoUnit1, "rspAddrIp", cJSON_CreateString("127.0.0.1"));//根节点下添加
	cJSON_AddItemToObject(transChanelInfoUnit1, "rspAddrPort", cJSON_CreateNumber(8888));
	cJSON_AddItemToObject(transChanelInfoUnit1, "status", cJSON_CreateString("Normal"));
	cJSON_AddItemReferenceToObject(transChanelInfoUnit1, "transParam", transParam1);


	cJSON * transParamUnit2_1 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit2_1, "transStreamType", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(transParamUnit2_1, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit2_1, "streamRate", cJSON_CreateNumber(128));
	cJSON_AddItemToObject(transParamUnit2_1, "isDistribute", cJSON_CreateNumber(0));

	cJSON * transParamUnit2_2 =  cJSON_CreateObject();
	cJSON_AddItemToObject(transParamUnit2_2, "transStreamType", cJSON_CreateNumber(1));
	cJSON_AddItemToObject(transParamUnit2_2, "frameRate", cJSON_CreateNumber(25));
	cJSON_AddItemToObject(transParamUnit2_2, "streamRate", cJSON_CreateNumber(512));
	cJSON_AddItemToObject(transParamUnit2_2, "isDistribute", cJSON_CreateNumber(0));

	cJSON * transParam2 = cJSON_CreateArray();
	cJSON_AddItemToArray(transParam2, transParamUnit2_1);
	cJSON_AddItemToArray(transParam2, transParamUnit2_2);

	cJSON * transChanelInfoUnit2 = cJSON_CreateObject();
	cJSON_AddItemToObject(transChanelInfoUnit2, "transChannelNum", cJSON_CreateNumber(2));
	cJSON_AddItemToObject(transChanelInfoUnit2, "rspAddrIp", cJSON_CreateString("127.0.0.1"));//根节点下添加
	cJSON_AddItemToObject(transChanelInfoUnit2, "rspAddrPort", cJSON_CreateNumber(8888));
	cJSON_AddItemToObject(transChanelInfoUnit2, "status", cJSON_CreateString("Normal"));
	cJSON_AddItemReferenceToObject(transChanelInfoUnit2, "transParam", transParam2);

	cJSON * transChanelInfos = cJSON_CreateArray();
	cJSON_AddItemToArray(transChanelInfos, transChanelInfoUnit1);
	cJSON_AddItemToArray(transChanelInfos, transChanelInfoUnit2);

	cJSON * root =  cJSON_CreateObject();

	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(200));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString("OK"));
	cJSON_AddItemReferenceToObject(root, "transChanelInfos", transChanelInfos);

	return cJSON_Print(root);
}

bool getConfig(const std::string& json_str, std::string &ip, std::string& port)
{
	cJSON * root = NULL;

	root = cJSON_Parse(json_str.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemIp = cJSON_GetObjectItem(root, "listenIp");
	cJSON* itemPort = cJSON_GetObjectItem(root, "listenPort");
	
	if (!itemIp || !itemPort)
	{
		cJSON_Delete(root);
		return false;
	}

	ip = itemIp->valuestring;
	port = itemPort->valuestring;


	cJSON_Delete(root);
	return true;
}

bool getConfig(const std::string& json_str, std::string &ip, std::string& port, int &keepalive)
{
	cJSON * root = NULL;

	root = cJSON_Parse(json_str.c_str());     
	if (!root) 
	{
		return false;
	}


	cJSON* itemIp = cJSON_GetObjectItem(root, "serverIp");
	cJSON* itemPort = cJSON_GetObjectItem(root, "listenPort");
	cJSON* itemKeepalive = cJSON_GetObjectItem(root, "keepalive");
	if (!itemIp || !itemPort || !itemKeepalive)
	{
		cJSON_Delete(root);
		return false;
	}

	ip = itemIp->valuestring;
	port = itemPort->valuestring;
	keepalive = itemKeepalive->valueint;

	cJSON_Delete(root);
	return true;
}

bool getSessionId(const std::string& strJson, std::string & sessionId)
{
	cJSON * root = NULL;

	root = cJSON_Parse(strJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemSessionId = cJSON_GetObjectItem(root, "sessionId");
	if (!itemSessionId)
	{
		cJSON_Delete(root);
		return false;
	}

	sessionId = itemSessionId->valuestring;

	return true;
}


bool create_file(const std::string& file_name, const std::string& content)
{
	std::ofstream outfile(file_name.c_str());
	if (!outfile)
	{
		return false;
	}
	outfile.write(content.c_str(), content.length());
	outfile.close();

	return true;
}

bool get_file(const std::string& file_name, std::string &content)
{
	std::ifstream infile(file_name.c_str());
	if (!infile)
	{
		return false;
	}

	char configBuf[2048] = {0};
	infile.read(configBuf, sizeof(configBuf));
	content = configBuf;
	infile.close();

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
    long year = 2020;
    long month = 8;
    long day = 5;
    long hour = 3;
    long mini = 23;
    long sec = 34;
	char dateTime[64];
    _snprintf(dateTime, sizeof(dateTime), "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, mini, sec  );
    std::cout << std::string(dateTime) << std::endl;

	//create_file("JSMvcServer.json", create_json());
	//create_file("JSMvcClient.json", create_client_json());
	//create_file("InitTransParam.json", create_transParam_json());

	std::string ip = "";
	std::string port = "";

	std::string server_config = "";
	get_file("JSMvcServer.json", server_config);
	getConfig(server_config, ip, port);
	std::cout << "server_config ip:" << ip << " port:" << port << std::endl;


	int keepalive = 0;
	std::string client_config = "";
	get_file("JSMvcClient.json", client_config);
	getConfig(client_config, ip, port, keepalive);
	std::cout << "client_config ip:" << ip << " port:" << port << " keepalive:"<< keepalive << std::endl;

	char szBuf[4096] = {0};
	getcwd(szBuf, sizeof(szBuf));
	std::string absoluteFilePath = "..\\config\\app\\JSMvcServer.json";
	get_file(absoluteFilePath, client_config);
	std::cout << "absoluteFilePath:" << absoluteFilePath << " content:" << client_config << std::endl;

	//std::cout << createJsonOkContent() << std::endl;
	std::string strOkContent = createJsonOkContent("11111111-11111111-11111111-11111111");
	std::string sessionId = "";
	getSessionId(strOkContent, sessionId);
	std::cout << strOkContent << std::endl;
	std::cout << sessionId << std::endl;
	//std::cout << createJsonQueryTransCoderStatusInfo() << std::endl;

	system("pause");
	return 0;
}

