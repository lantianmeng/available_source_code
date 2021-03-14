# xml/json中含有特殊字符，怎么处理
<br>特殊字符进行转义，**需要学代码进行测试**

1. cJson解析的测试代码UrlJsonParse.hpp
```
////deviceAdd
//char testJson[] = 
//"{ \
//	\"deviceAddr\":\"192.168.3.72:20000\", \
//	\"deviceType\":1, \
//	\"user\":\"user1\", \
//	\"pwd\":\"password1\", \
//	\"resources\":[\
//	{	\
//	\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\",\
//	\"channelId\":1,\
//	\"resourceType\":1\
//	},\
//	{ \
//	\"resourceId\":\"7582FB91-A28C-435a-8156-68FA65829333\",\
//	\"channelId\":1,\
//	\"resourceType\":1\
//	} \
//	] \
//}";

////deviceDel
//char testJson[] = 
//"{ \
//	\"deviceAddr\":\"192.168.3.72:20000\" \
//}";

////PrepositionGet
//char testJson[] = 
//"{ \
//\"deviceAddr\":\"192.168.3.72:20000\", \
//\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\", \
//\"channelId\":1 \
//}";

////PrepositionAdd
//char testJson[] = 
//"{ \
//\"deviceAddr\":\"192.168.3.72:20000\", \
//\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\", \
//\"channelId\":1, \
//\"prepositionAddr\":1, \
//\"prepositionName\":\"preName1\" \
//}";

////PrepositionDel/PrepositionCtl
//char testJson[] = 
//"{ \
//\"deviceAddr\":\"192.168.3.72:20000\", \
//\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\", \
//\"channelId\":1, \
//\"prepositionAddr\":1 \
//}";

////PtzCtl
//char testJson[] = 
//"{ \
//\"deviceAddr\":\"192.168.3.72:20000\", \
//\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\", \
//\"channelId\":1, \
//\"ptzAction\":1, \
//\"speed\":1, \
//\"describe\":\"111\" \
//}";

////DeviceCtl
//char testJson[] = 
//"{ \
//\"deviceAddr\":\"192.168.3.72:20000\", \
//\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\", \
//\"channelId\":1, \
//\"action\":1, \
//\"describe\":\"111\" \
//}";

////StreamRequest
//char testJson[] = 
//"{ \
//\"deviceAddr\":\"192.168.3.72:20000\", \
//\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\", \
//\"dualStreamType\":1, \
//\"describe\":\"111\" \
//}";

//GetActiveDevice rsp
char testJson[] = 
"{ \
\"adpterAddr\":\"192.168.3.72:20000\",\
\"devices\":\
[{ \
\"deviceAddr\":\"192.168.3.72:20000\", \
\"deviceType\":1, \
\"user\":\"user1\", \
\"pwd\":\"password1\", \
\"resources\":[\
{	\
\"resourceId\":\"3D3ED53F-B56C-48ba-851A-518E78A3DFB9\",\
\"channelId\":1,\
\"resourceType\":1\
},\
{ \
\"resourceId\":\"7582FB91-A28C-435a-8156-68FA65829333\",\
\"channelId\":1,\
\"resourceType\":1\
} \
] \
}, \
{ \
\"deviceAddr\":\"192.168.3.73:20000\", \
\"deviceType\":1, \
\"user\":\"user2\", \
\"pwd\":\"password2\", \
\"resources\":[\
{	\
\"resourceId\":\"8D3ED53F-B56C-48ba-851A-518E78A3DFB0\",\
\"channelId\":1,\
\"resourceType\":1\
},\
{ \
\"resourceId\":\"8582FB91-A28C-435a-8156-68FA65829339\",\
\"channelId\":1,\
\"resourceType\":1\
} \
] \
} \
]}";

	DasParse::CUrlJsonParse parse;
	DasParse::ECommand cmd = parse.parseUrl("http://ip:port/xxx/api/preposition/get");

	std::string deviceAddr = "";
	DasParse::SDevice device;
	std::string resourceId;
	int channelId;
	DasParse::SPreposition prepos;
	
	int prepositionAddr;
	int ptzAction;
	int speed;
	std::string describe;

	//bool ret = parse.parseDeviceAdd(testJson, device);

	std::vector<DasParse::SDevice> devices;
	bool ret = parse.parseGetActiveDevice(testJson, deviceAddr, devices);
	//bool ret = parse.parsePrepositionAdd(testJson, deviceAddr, resourceId, channelId, prepos);
	//bool ret = parse.parsePrepositionCtl(testJson, deviceAddr, resourceId, channelId, prepositionAddr);
	//bool ret = parse.parseDeviceCtl(testJson, deviceAddr, resourceId, channelId, ptzAction, describe);
	//bool ret = parse.parseStreamRequest(testJson, deviceAddr, resourceId, ptzAction, describe);
	
	std::string sRsp = parse.createJsonRsp(200, "OK");
	std::string sRsp1 = parse.createJsonRsp(404, "not found");

	std::vector<DasParse::SPreposition> prepositionVec;
	DasParse::SPreposition pr1;
	pr1.prepositionAddr = 1;
	pr1.prepositionName = "preName1";
	prepositionVec.push_back(pr1);

	pr1.prepositionAddr = 2;
	pr1.prepositionName = "preName2";
	prepositionVec.push_back(pr1);
	std::string sRsp2 = parse.createPrepositionGetRsp(prepositionVec, 200, "success");

	std::string sRsp3 = parse.createStreamRequestRsp("rtmp://xxx/yyy/", 200, "success");


	std::vector<DasParse::SResource> resourceVec;
	DasParse::SResource resource;
	resource.resourceId = "3D3ED53F-B56C-48ba-851A-518E78A3DFB9";
	resource.resourceName = "resName";
	resource.resourceType = 1;
	resourceVec.push_back(resource);

	resource.resourceId = "7582FB91-A28C-435a-8156-68FA65829333";
	resource.resourceName = "resName2";
	resource.resourceType = 1;
	resourceVec.push_back(resource);
	std::string sRsp4 = parse.createJsonResourceSyn("192.168.3.72:20000", resourceVec);
```
