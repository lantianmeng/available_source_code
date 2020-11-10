#ifndef COMMANDDATADEFINE_HPP_
#define COMMANDDATADEFINE_HPP_

#include <string>
#include <vector>

namespace DasParse
{
	enum ECommand
	{
		DEVICE_ADD,               //增加设备
		DEVICE_DEL,               //删除设备
		PREPOSITION_GET,          //获取预置位
		PREPOSITION_ADD,          //添加预置位
		PREPOSITION_DEL,          //删除预置位
		PREPOSITION_CTL,          //选中预置位
		PTZ_CTL,                  //云台控制
		DEVICE_CTL,               //控制命令
		STREAM_REQUEST,            //请求流
		NO_SUPPORT
	};
	
	struct SResource
    {
    	std::string resourceId;    //资源ID
		std::string resourceName;  //资源名称
		int resourceType;          //资源类型 1：视频资源，2：告警资源，3：风机，4：照明灯，5：卷帘门，6：车道指示灯，7：红绿灯，8：方向指示灯
		int channelId;             //通道号
		int onlineStatus;          //在线状态 0：离线，1：在线
		int actionStatus;          //工作状态  其值的含义需结合资源类型resourceType来定义
		std::string reserved;      //保留字段

		SResource()
		{
			resourceId = "";
			resourceName = "";
			resourceType = 0;
			channelId = 0;
			onlineStatus = 0;
			actionStatus = 0;
			reserved = "";
		}
	};

	struct SDevice
	{
		std::string deviceAddr;   //设备地址
		std::string user;         //用户名
		std::string pwd;          //密码
		int deviceType;           //设备类型

		std::vector<SResource> resourceVec;
	};

	struct SPreposition
	{
		int prepositionAddr;
		std::string prepositionName;
	};
}
#endif