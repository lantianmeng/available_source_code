#ifndef URLJSONPARSE_HPP_
#define URLJSONPARSE_HPP_

#include <map>
#include "../include/DasServiceTypeDefine.hpp"

class CDasService;
class cJSON;
namespace das
{

typedef bool (*ParseCallback)( const std::string& sJson, std::string& repJson) ;

struct SCmdUrl
{
	std::string url;
	ParseCallback callback;
};

class CUrlJsonParse
{
public:
	CUrlJsonParse();
	virtual ~CUrlJsonParse();

	static bool HandleRequest(const std::string& url, const std::string& sJson, std::string& strRepJson);
	//bool createUrl(ECommand cmd, std::string &url);

	static bool HandleDeviceAdd(const std::string& sJson, std::string& repJson);
	static bool HandleDeviceDel(const std::string& sJson, std::string& repJson);
	static bool HandlePrepositionGet(const std::string& sJson, std::string& repJson);
	static bool HandlePrepositionAdd(const std::string& sJson, std::string& repJson);
	static bool HandlePrepositionDel(const std::string& sJson, std::string& repJson);
	static bool HandlePrepositionCtl(const std::string& sJson, std::string& repJson);
	static bool HandlePtzCtl(const std::string& sJson, std::string& repJson);
	static bool HandleDeviceCtl(const std::string& sJson, std::string& repJson);
	static bool HandleStreamRequest(const std::string& sJson, std::string& repJson);

	//getActiveDevice and keepalive use
	static bool createJsonAdpterAddr(const std::string &adpterAddr, std::string &retJson); 
	static bool createJsonDeviceStatus(const std::string &deviceAddr, int status, std::string &retJson);
	static bool createJsonResourceSyn(const std::string &deviceAddr, const std::vector<SResource>& resourceVec, std::string &retJson);
	static bool createJsonResourceStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec, std::string &retJson);
	static bool createJsonResourceActionStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec, std::string &retJson);

	static bool parseGetActiveDevice(const std::string& sJson, std::string &adpterAddr, std::vector<SDevice> &devices);

private:
	static bool parseDeviceNode(cJSON* itemDevice, SDevice &device);

	static bool parseDeviceAdd(const std::string& sJson, SDevice &device);
	static bool parseDeviceDel(const std::string& sJson, std::string &deviceAddr);
	static bool parsePrepositionGet(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId);
	static bool parsePrepositionAdd(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, SPreposition &preposion);
	static bool parsePrepositionDel(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &prepositionAddr);
	static bool parsePrepositionCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &prepositionAddr);
	static bool parsePtzCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &ptzAction, int &speed, std::string &describe);
	static bool parseDeviceCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &action, std::string &describe);
	static bool parseStreamRequest(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &dualStreamType, std::string &describe);

	//OK or Error
	static bool createJsonRsp(int code, const std::string& msg, std::string &retJson);
	static bool createPrepositionGetRsp(std::vector<SPreposition> prepositionVec, int code, const std::string& msg, std::string &retJson);
	static bool createStreamRequestRsp(const std::string &streamUrl, int code, const std::string& msg, std::string &retJson);
};

}
#endif