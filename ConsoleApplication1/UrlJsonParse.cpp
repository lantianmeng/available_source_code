#include "UrlJsonParse.hpp"
#include "cJSON.h"

namespace DasParse
{

static const std::string REQ_CMD[] = 
{
	"/api/device/add", 
	"/api/device/del", 
	"/api/preposition/get", 
	"/api/preposition/add",
	"/api/preposition/del",
	"/api/preposition/ctl",
	"/api/ptz/ctl",
	"/api/device/ctl",
	"/api/stream/request"
};

CUrlJsonParse::CUrlJsonParse()
{

}

CUrlJsonParse::~CUrlJsonParse()
{

}

ECommand CUrlJsonParse::parseUrl(std::string url)
{
	ECommand eCmd = NO_SUPPORT;
	std::string strReqCmd = "";

	//直接解析
	std::size_t pos = url.find("/api/");
	if(pos != std::string::npos)
	{
		strReqCmd = url.substr(pos, url.length() - pos);
	}

	//遍历数组，返回下标
	for (int i = 0; i < sizeof(REQ_CMD)/sizeof(REQ_CMD[0]); ++i)
	{
		if (strReqCmd == REQ_CMD[i])
		{
			eCmd = static_cast<ECommand>(i);
			break;
		}
	}

	return eCmd;
}

bool CUrlJsonParse::parseDeviceAdd(const std::string& sJson, SDevice &device)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	if (!parseDeviceNode(root, device))
	{
		return false;
	}

	return true;
}

bool CUrlJsonParse::parseDeviceNode(cJSON* itemDevice, SDevice &device)
{    
	if (!itemDevice) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(itemDevice, "deviceAddr");
	if (!itemDeviceAddr)
	{
		return false;
	}
	std::string deviceAddr = itemDeviceAddr->valuestring;
	device.deviceAddr = deviceAddr;

	cJSON* itemDeviceType = cJSON_GetObjectItem(itemDevice, "deviceType");
	if (!itemDeviceType)
	{
		return false;
	}
	int deviceType = itemDeviceType->valueint;
	device.deviceType = deviceType;

	cJSON* itemUser = cJSON_GetObjectItem(itemDevice, "user");
	if (!itemUser)
	{
		return false;
	}
	std::string user = itemUser->valuestring;
	device.user = user;

	cJSON* itemPwd = cJSON_GetObjectItem(itemDevice, "pwd");
	if (!itemPwd)
	{
		return false;
	}
	std::string pwd = itemPwd->valuestring;
	device.pwd = pwd;

	cJSON* itemResources = cJSON_GetObjectItem(itemDevice, "resources");
	if (!itemResources)
	{
		return false;
	}

	SResource resources;
	device.resourceVec.clear();
	for (int i = 0; i < cJSON_GetArraySize(itemResources); ++i)
	{
		cJSON * itemResource = cJSON_GetArrayItem(itemResources, i);
		if(itemResource)
		{
			cJSON* itemResourceId = cJSON_GetObjectItem(itemResource, "resourceId");
			if (!itemResourceId)
			{
				cJSON_Delete(itemResource);
				break;
			}
			resources.resourceId = itemResourceId->valuestring;

			cJSON* itemChannelId = cJSON_GetObjectItem(itemResource, "channelId");
			if (!itemChannelId)
			{
				cJSON_Delete(itemResource);
				break;
			}
			resources.channelId = itemChannelId->valueint;

			cJSON* itemResourceType = cJSON_GetObjectItem(itemResource, "resourceType");
			if (!itemChannelId)
			{
				cJSON_Delete(itemResource);
				break;
			}
			resources.resourceType = itemResourceType->valueint;

			device.resourceVec.push_back(resources);
		}
	}

	return true;
}

bool CUrlJsonParse::parseDeviceDel(const std::string& sJson, std::string &deviceAddr)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}

	deviceAddr = itemDeviceAddr->valuestring;

	return true;
}

bool CUrlJsonParse::parsePrepositionGet(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemChannelId = cJSON_GetObjectItem(root, "channelId");
	if (!itemChannelId)
	{
		cJSON_Delete(root);
		return false;
	}
	channelId = itemChannelId->valueint;

	return true;
}

bool CUrlJsonParse::parsePrepositionAdd(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, SPreposition &preposion)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemChannelId = cJSON_GetObjectItem(root, "channelId");
	if (!itemChannelId)
	{
		cJSON_Delete(root);
		return false;
	}
	channelId = itemChannelId->valueint;

	cJSON* itemPrepositionAddr = cJSON_GetObjectItem(root, "prepositionAddr");
	if (!itemPrepositionAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	int prepositionAddr = itemPrepositionAddr->valueint;
	preposion.prepositionAddr = prepositionAddr;

	cJSON* itemPrepositionName = cJSON_GetObjectItem(root, "prepositionName");
	if (!itemPrepositionName)
	{
		cJSON_Delete(root);
		return false;
	}
	std::string prepositionName = itemPrepositionName->valuestring;
	preposion.prepositionName = prepositionName;

	return true;
}

bool CUrlJsonParse::parsePrepositionDel(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &prepositionAddr)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemChannelId = cJSON_GetObjectItem(root, "channelId");
	if (!itemChannelId)
	{
		cJSON_Delete(root);
		return false;
	}
	channelId = itemChannelId->valueint;

	cJSON* itemPrepositionAddr = cJSON_GetObjectItem(root, "prepositionAddr");
	if (!itemPrepositionAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	prepositionAddr = itemPrepositionAddr->valueint;

	return true;
}

bool CUrlJsonParse::parsePrepositionCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &prepositionAddr)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemChannelId = cJSON_GetObjectItem(root, "channelId");
	if (!itemChannelId)
	{
		cJSON_Delete(root);
		return false;
	}
	channelId = itemChannelId->valueint;

	cJSON* itemPrepositionAddr = cJSON_GetObjectItem(root, "prepositionAddr");
	if (!itemPrepositionAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	prepositionAddr = itemPrepositionAddr->valueint;

	return true;
}

bool CUrlJsonParse::parsePtzCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &ptzAction, int &speed, std::string &describe)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemChannelId = cJSON_GetObjectItem(root, "channelId");
	if (!itemChannelId)
	{
		cJSON_Delete(root);
		return false;
	}
	channelId = itemChannelId->valueint;

	cJSON* itemPtzAction = cJSON_GetObjectItem(root, "ptzAction");
	if (!itemPtzAction)
	{
		cJSON_Delete(root);
		return false;
	}
	ptzAction = itemPtzAction->valueint;

	cJSON* itemSpeed = cJSON_GetObjectItem(root, "speed");
	if (!itemSpeed)
	{
		cJSON_Delete(root);
		return false;
	}
	speed = itemSpeed->valueint;

	cJSON* itemDescribe = cJSON_GetObjectItem(root, "describe");
	if (!itemDescribe)
	{
		cJSON_Delete(root);
		return false;
	}
	describe = itemDescribe->valuestring;

	return true;
}

bool CUrlJsonParse::parseDeviceCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &action, std::string &describe)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemChannelId = cJSON_GetObjectItem(root, "channelId");
	if (!itemChannelId)
	{
		cJSON_Delete(root);
		return false;
	}
	channelId = itemChannelId->valueint;

	cJSON* itemAction = cJSON_GetObjectItem(root, "action");
	if (!itemAction)
	{
		cJSON_Delete(root);
		return false;
	}
	action = itemAction->valueint;

	cJSON* itemDescribe = cJSON_GetObjectItem(root, "describe");
	if (!itemDescribe)
	{
		cJSON_Delete(root);
		return false;
	}
	describe = itemDescribe->valuestring;

	return true;
}

bool CUrlJsonParse::parseStreamRequest(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &dualStreamType, std::string &describe)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemDeviceAddr = cJSON_GetObjectItem(root, "deviceAddr");
	if (!itemDeviceAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	deviceAddr = itemDeviceAddr->valuestring;

	cJSON* itemResourceId = cJSON_GetObjectItem(root, "resourceId");
	if (!itemResourceId)
	{
		cJSON_Delete(root);
		return false;
	}
	resourceId = itemResourceId->valuestring;

	cJSON* itemDualStreamType = cJSON_GetObjectItem(root, "dualStreamType");
	if (!itemDualStreamType)
	{
		cJSON_Delete(root);
		return false;
	}
	dualStreamType = itemDualStreamType->valueint;

	cJSON* itemDescribe = cJSON_GetObjectItem(root, "describe");
	if (!itemDescribe)
	{
		cJSON_Delete(root);
		return false;
	}
	describe = itemDescribe->valuestring;

	return true;
}

std::string CUrlJsonParse::createJsonRsp(int code, const std::string& msg)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(code));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString(msg.c_str()));

	return cJSON_Print(root);
}

std::string CUrlJsonParse::createPrepositionGetRsp(std::vector<SPreposition> prepositionVec, int code, const std::string& msg)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(code));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString(msg.c_str()));

	cJSON * prepositions = cJSON_CreateArray();
	if (prepositions)
	{
		for (int i = 0; i < prepositionVec.size(); ++i)
		{
			cJSON * prepositionsUnit = cJSON_CreateObject();
			if (!prepositionsUnit) continue;

			cJSON_AddItemToObject(prepositionsUnit, "prepositionAddr", cJSON_CreateNumber(prepositionVec[i].prepositionAddr));
			cJSON_AddItemToObject(prepositionsUnit, "prepositionName", cJSON_CreateString(prepositionVec[i].prepositionName.c_str()));

			cJSON_AddItemToArray(prepositions, prepositionsUnit);
		}

		cJSON_AddItemReferenceToObject(root, "prepositions", prepositions);
	}

	return cJSON_Print(root);
}

std::string CUrlJsonParse::createStreamRequestRsp(const std::string &streamUrl, int code, const std::string& msg)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "streamUrl", cJSON_CreateString(streamUrl.c_str()));
	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(code));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString(msg.c_str()));

	return cJSON_Print(root);
}

std::string CUrlJsonParse::createJsonAdpterAddr(const std::string &adpterAddr)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "adpterAddr", cJSON_CreateString(adpterAddr.c_str()));

	return cJSON_Print(root);
}

std::string CUrlJsonParse::createJsonDeviceStatus(const std::string &deviceAddr, int status)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "deviceAddr", cJSON_CreateString(deviceAddr.c_str()));
	cJSON_AddItemToObject(root, "status", cJSON_CreateNumber(status));

	return cJSON_Print(root);
}

std::string CUrlJsonParse::createJsonResourceSyn(const std::string &deviceAddr, const std::vector<SResource>& resourceVec)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "deviceAddr", cJSON_CreateString(deviceAddr.c_str()));
	
	cJSON * resources = cJSON_CreateArray();
	if (resources)
	{
		for (int i = 0; i < resourceVec.size(); ++i)
		{
			cJSON * resourceUnit = cJSON_CreateObject();
			if (!resourceUnit) continue;

			cJSON_AddItemToObject(resourceUnit, "resourceId", cJSON_CreateString(resourceVec[i].resourceId.c_str()));
			cJSON_AddItemToObject(resourceUnit, "resourceName", cJSON_CreateString(resourceVec[i].resourceName.c_str()));
			cJSON_AddItemToObject(resourceUnit, "resourceType", cJSON_CreateNumber(resourceVec[i].resourceType));

			cJSON_AddItemToArray(resources, resourceUnit);
		}

		cJSON_AddItemReferenceToObject(root, "resources", resources);
	}

	return cJSON_Print(root);
}

std::string CUrlJsonParse::createJsonResourceStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "deviceAddr", cJSON_CreateString(deviceAddr.c_str()));

	cJSON * resources = cJSON_CreateArray();
	if (resources)
	{
		for (int i = 0; i < resourceVec.size(); ++i)
		{
			cJSON * resourceUnit = cJSON_CreateObject();
			if (!resourceUnit) continue;

			cJSON_AddItemToObject(resourceUnit, "resourceId", cJSON_CreateString(resourceVec[i].resourceId.c_str()));
			cJSON_AddItemToObject(resourceUnit, "status", cJSON_CreateNumber(resourceVec[i].onlineStatus));

			cJSON_AddItemToArray(resources, resourceUnit);
		}

		cJSON_AddItemReferenceToObject(root, "resources", resources);
	}
	return cJSON_Print(root);
}

std::string CUrlJsonParse::createJsonResourceActionStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return "";

	cJSON_AddItemToObject(root, "deviceAddr", cJSON_CreateString(deviceAddr.c_str()));

	cJSON * resources = cJSON_CreateArray();
	if (resources)
	{
		for (int i = 0; i < resourceVec.size(); ++i)
		{
			cJSON * resourceUnit = cJSON_CreateObject();
			if (!resourceUnit) continue;

			cJSON_AddItemToObject(resourceUnit, "resourceId", cJSON_CreateString(resourceVec[i].resourceId.c_str()));
			cJSON_AddItemToObject(resourceUnit, "resourceType", cJSON_CreateNumber(resourceVec[i].resourceType));
			cJSON_AddItemToObject(resourceUnit, "actionStatus", cJSON_CreateNumber(resourceVec[i].actionStatus));
			cJSON_AddItemToObject(resourceUnit, "describe", cJSON_CreateString(resourceVec[i].reserved.c_str()));

			cJSON_AddItemToArray(resources, resourceUnit);
		}

		cJSON_AddItemReferenceToObject(root, "resources", resources);
	}
	return cJSON_Print(root);
}

bool CUrlJsonParse::parseGetActiveDevice(const std::string& sJson, std::string &adpterAddr, std::vector<SDevice> &devices)
{
	bool ret = true;
	do 
	{
		cJSON * root = NULL;

		root = cJSON_Parse(sJson.c_str());     
		if (!root) 
		{
			ret = false;
			break;
		}

		cJSON* itemAdpterAddr = cJSON_GetObjectItem(root, "adpterAddr");
		if (!itemAdpterAddr)
		{
			cJSON_Delete(root);
			ret = false;
			break;
		}
		adpterAddr = itemAdpterAddr->valuestring;

		cJSON* itemDevices = cJSON_GetObjectItem(root, "devices");
		if (!itemDevices)
		{
			cJSON_Delete(root);
			ret = false;
			break;
		}

		SDevice device;
		for (int i = 0; i < cJSON_GetArraySize(itemDevices); ++i)
		{
			cJSON * itemDevice = cJSON_GetArrayItem(itemDevices, i);
			if (parseDeviceNode(itemDevice, device))
			{
				devices.push_back(device);
			}
			else
			{
				ret = false;
				break;
			}
		}

	} while (0);

	return ret;
}

}
