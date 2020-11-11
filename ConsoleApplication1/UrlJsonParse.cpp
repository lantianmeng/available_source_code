
#include <boost/bind.hpp>

#include "../include/DasServiceExp.hpp"
#include "DasService.hpp"
#include "UrlJsonParse.hpp"
#include "cJSON.h"
#include "DasService.hpp"

namespace das
{

static const int g_ERROR_CODE = 404;
static const char*  g_ERROR_MSG = "fail";
static const char*  g_NO_SUPPORT = "/default/noSupport";

static const SCmdUrl g_CMD_URL[] = 
{
	{"/api/device/add", &CUrlJsonParse::HandleDeviceAdd}, 
	{"/api/device/del", &CUrlJsonParse::HandleDeviceDel}, 
	{"/api/preposition/get", &CUrlJsonParse::HandlePrepositionGet}, 
	{"/api/preposition/add", &CUrlJsonParse::HandlePrepositionAdd},
	{"/api/preposition/del", &CUrlJsonParse::HandlePrepositionDel},
	{"/api/preposition/ctl", &CUrlJsonParse::HandlePrepositionCtl},
	{"/api/ptz/ctl", &CUrlJsonParse::HandlePtzCtl},
	{"/api/device/ctl", &CUrlJsonParse::HandleDeviceCtl},
	{"/api/stream/request", &CUrlJsonParse::HandleStreamRequest},
//	{GET_ACTIVE_DEVICE, "/api/device/getActiveDevice"},
//	{KEEPALIVE, "/api/server/keepAlive"},
//	{DEVICE_STATUS, "/api/device/status"},
//	{RESOURCE_SYN, "/api/resource/syn"},
//	{RESOURCE_STATUS, "/api/resource/status"},
//	{RESOURCE_ACTION_STATUS, "/api/resource/actionStatus"},
	{g_NO_SUPPORT, NULL}
};   


CUrlJsonParse::CUrlJsonParse()
{
	
}

CUrlJsonParse::~CUrlJsonParse()
{

}

//bool CUrlJsonParse::Init()
//{
//	m_callbackMap.insert(std::make_pair("/api/device/add", &CUrlJsonParse::HandleDeviceAdd));
//	m_callbackMap.insert(std::make_pair("/api/device/del", &CUrlJsonParse::HandleDeviceDel));
//	m_callbackMap.insert(std::make_pair("/api/preposition/get", &CUrlJsonParse::HandlePrepositionGet));
//
//	return true;
//}
//
//bool CUrlJsonParse::Fini()
//{
//	m_callbackMap.clear();
//	return true;
//}

bool CUrlJsonParse::HandleRequest(const std::string& url, const std::string& sJson, std::string& strRepJson)
{
	////直接解析
	//std::size_t pos = url.find("/api/");
	//if(pos != std::string::npos)
	//{
	//	strReqCmd = url.substr(pos, url.length() - pos);
	//}

	bool ret = false;
	//遍历数组
	for (int i = 0; g_CMD_URL[i].url != g_NO_SUPPORT; ++i)
	{
		if (url == g_CMD_URL[i].url)
		{
			ret = (g_CMD_URL[i].callback)(sJson, strRepJson);
			break;
		}
	}
	return ret;
}

//bool CUrlJsonParse::createUrl(ECommand cmd, std::string &url)
//{
//	bool ret = false;
//
//	//遍历数组
//	int i = 0;
//	for (; g_CMD_URL[i].cmd != NO_SUPPORT; ++i)
//	{
//		if (cmd == g_CMD_URL[i].cmd)
//		{
//			url = g_CMD_URL[i].url;
//			ret = true;
//			break;
//		}
//	}
//
//	return ret;
//}

bool CUrlJsonParse::parseDeviceAdd(const std::string& sJson, SDevice &device)
{
	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	bool ret = parseDeviceNode(root, device);

	cJSON_Delete(root);

	return ret;
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
				break;
			}
			resources.resourceId = itemResourceId->valuestring;

			cJSON* itemChannelId = cJSON_GetObjectItem(itemResource, "channelId");
			if (!itemChannelId)
			{
				break;
			}
			resources.channelId = itemChannelId->valueint;

			cJSON* itemResourceType = cJSON_GetObjectItem(itemResource, "resourceType");
			if (!itemChannelId)
			{
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
	cJSON_Delete(root);

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
	cJSON_Delete(root);
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

	cJSON_Delete(root);
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
	cJSON_Delete(root);
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
	cJSON_Delete(root);
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
	cJSON_Delete(root);
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
	cJSON_Delete(root);
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
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createJsonRsp(int code, const std::string& msg, std::string &retJson)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return false;

	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(code));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString(msg.c_str()));

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createPrepositionGetRsp(std::vector<SPreposition> prepositionVec, int code, const std::string& msg, std::string &retJson)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return false;

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

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createStreamRequestRsp(const std::string &streamUrl, int code, const std::string& msg, std::string &retJson)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return false;

	cJSON_AddItemToObject(root, "streamUrl", cJSON_CreateString(streamUrl.c_str()));
	cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(code));
	cJSON_AddItemToObject(root, "msg", cJSON_CreateString(msg.c_str()));

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createJsonAdpterAddr(const std::string &adpterAddr, std::string &retJson)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return false;

	cJSON_AddItemToObject(root, "adpterAddr", cJSON_CreateString(adpterAddr.c_str()));

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createJsonDeviceStatus(const std::string &deviceAddr, int status, std::string &retJson)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return false;

	cJSON_AddItemToObject(root, "deviceAddr", cJSON_CreateString(deviceAddr.c_str()));
	cJSON_AddItemToObject(root, "status", cJSON_CreateNumber(status));

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createJsonResourceSyn(const std::string &deviceAddr, const std::vector<SResource>& resourceVec, std::string &retJson)
{
	cJSON * root =  cJSON_CreateObject();
	if (!root) return false;

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

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createJsonResourceStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec, std::string &retJson)
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

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::createJsonResourceActionStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec, std::string &retJson)
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

	retJson = cJSON_Print(root);
	cJSON_Delete(root);
	return true;
}

bool CUrlJsonParse::parseGetActiveDevice(const std::string& sJson, std::string &adpterAddr, std::vector<SDevice> &devices)
{
	bool ret = true;

	cJSON * root = NULL;

	root = cJSON_Parse(sJson.c_str());     
	if (!root) 
	{
		return false;
	}

	cJSON* itemAdpterAddr = cJSON_GetObjectItem(root, "adpterAddr");
	if (!itemAdpterAddr)
	{
		cJSON_Delete(root);
		return false;
	}
	adpterAddr = itemAdpterAddr->valuestring;

	cJSON* itemDevices = cJSON_GetObjectItem(root, "devices");
	if (!itemDevices)
	{
		cJSON_Delete(root);
		return false;
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

	cJSON_Delete(root);
	return ret;
}

bool CUrlJsonParse::HandleDeviceAdd(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	SDevice device;
	if(!parseDeviceAdd(sJson, device))
	{
		return false;
	}

	bool ret = dasService->HandleDeviceAdd(device);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandleDeviceDel(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	if(!parseDeviceDel(sJson, deviceAddr))
	{
		return false;
	}

	bool ret = dasService->HandleDeviceDel(deviceAddr);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandlePrepositionGet(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int channelId;
	if(!parsePrepositionGet(sJson, deviceAddr, resourceId, channelId))
	{
		return false;
	}

	std::vector<SPreposition> prepositionVec;
	bool ret = dasService->HandlePreposiotionGet(deviceAddr, resourceId, channelId, prepositionVec);
	bool ret1 = false;
	if (ret)
	{
		ret1 = createPrepositionGetRsp(prepositionVec, 200, "success", repJson);
	}
	else
	{
		ret1 = createJsonRsp(g_ERROR_CODE, g_ERROR_MSG, repJson);
	}

	return ret && ret1;
}

bool CUrlJsonParse::HandlePrepositionAdd(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int channelId;
	SPreposition prepos;
	if(!parsePrepositionAdd(sJson, deviceAddr, resourceId, channelId, prepos))
	{
		return false;
	}

	bool ret = dasService->HandlePrepositionAdd(deviceAddr, resourceId, channelId, prepos);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandlePrepositionDel(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int channelId;
	int prepositionAddr;
	if(!parsePrepositionDel(sJson, deviceAddr, resourceId, channelId, prepositionAddr))
	{
		return false;
	}

	bool ret = dasService->HandlePrepositionDel(deviceAddr, resourceId, channelId, prepositionAddr);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandlePrepositionCtl(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int channelId;
	int prepositionAddr;
	if(!parsePrepositionCtl(sJson, deviceAddr, resourceId, channelId, prepositionAddr))
	{
		return false;
	}

	bool ret = dasService->HandlePrepositionCtl(deviceAddr, resourceId, channelId, prepositionAddr);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandlePtzCtl(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int channelId;
	int ptzAction;
	int speed;
	std::string describe = "";
	if(!parsePtzCtl(sJson, deviceAddr, resourceId, channelId, ptzAction, speed, describe))
	{
		return false;
	}

	bool ret = dasService->HandlePtzCtl(deviceAddr, resourceId, channelId, ptzAction, speed, describe);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandleDeviceCtl(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int channelId;
	int action;
	std::string describe = "";
	if(!parseDeviceCtl(sJson, deviceAddr, resourceId, channelId, action, describe))
	{
		return false;
	}

	bool ret = dasService->HandleDeviceCtl(deviceAddr, resourceId, channelId, action, describe);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = createJsonRsp(code, msg, repJson);

	return ret && ret1;
}

bool CUrlJsonParse::HandleStreamRequest(const std::string& sJson, std::string& repJson)
{
	boost::shared_ptr< IDasService > dasService;
	if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_DasService_DasService, dasService)) 
	{
		return false;
	}

	std::string deviceAddr = "";
	std::string resourceId = "";
	int dualStreamType;
	std::string describe = "";
	if(!parseStreamRequest(sJson, deviceAddr, resourceId, dualStreamType, describe))
	{
		return false;
	}

	std::string streamUrl = "";
	bool ret = dasService->HandleStreamRequest(deviceAddr, resourceId, dualStreamType, describe, streamUrl);
	int code = ret ? 200 : g_ERROR_CODE;
	std::string msg = ret ? "success":g_ERROR_MSG;

	bool ret1 = false;
	if (ret)
	{
		ret1 = createStreamRequestRsp(streamUrl, 200, "success", repJson);
	}
	else
	{
		ret1 = createJsonRsp(g_ERROR_CODE, g_ERROR_MSG, repJson);
	}

	return ret && ret1;
}

}
