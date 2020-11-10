#ifndef URLJSONPARSE_HPP_
#define URLJSONPARSE_HPP_

#include "CommandDataDefine.hpp"

class cJSON;
namespace DasParse
{

class CUrlJsonParse
{
public:
	CUrlJsonParse();
	virtual ~CUrlJsonParse();

	ECommand parseUrl(std::string url);

	bool parseGetActiveDevice(const std::string& sJson, std::string &adpterAddr, std::vector<SDevice> &devices);

	bool parseDeviceAdd(const std::string& sJson, SDevice &device);
	bool parseDeviceDel(const std::string& sJson, std::string &deviceAddr);
	bool parsePrepositionGet(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId);
	bool parsePrepositionAdd(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, SPreposition &preposion);
	bool parsePrepositionDel(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &prepositionAddr);
	bool parsePrepositionCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &prepositionAddr);
	bool parsePtzCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &ptzAction, int &speed, std::string &describe);
	bool parseDeviceCtl(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &channelId, int &action, std::string &describe);
	bool parseStreamRequest(const std::string& sJson, std::string &deviceAddr, std::string &resourceId, int &dualStreamType, std::string &describe);

	//OK or Error
	std::string createJsonRsp(int code, const std::string& msg);
	std::string createPrepositionGetRsp(std::vector<SPreposition> prepositionVec, int code, const std::string& msg);
	std::string createStreamRequestRsp(const std::string &streamUrl, int code, const std::string& msg);

	//getActiveDevice and keepalive use
	std::string createJsonAdpterAddr(const std::string &adpterAddr); 
	std::string createJsonDeviceStatus(const std::string &deviceAddr, int status);
	std::string createJsonResourceSyn(const std::string &deviceAddr, const std::vector<SResource>& resourceVec);
	std::string createJsonResourceStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec);
	std::string createJsonResourceActionStatus(const std::string &deviceAddr, const std::vector<SResource>& resourceVec);

private:
	bool parseDeviceNode(cJSON* itemDevice, SDevice &device);
};

}
#endif