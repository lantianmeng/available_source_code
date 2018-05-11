#pragma once

#include <iostream>
#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>  
#include <boost/algorithm/string.hpp>

#include "Log.h"

#include <vector>
#include <string>

using namespace std;

class Config
{
public:

	bool InitConfig(const std::string &ini_file_name)
	{
		try
		{
			boost::property_tree::ptree pt;
			boost::property_tree::ini_parser::read_ini(ini_file_name, pt);

			// ¶Á×Ö¶Î 
			//std::cout << pt.get<std::string>("LOG.SIZE") << std::endl;
			//std::cout << pt.get<std::string>("LOG.LEVEL") << std::endl;
			log_level = (LOG::sign_severity_level)std::stoi(pt.get<std::string>("LOG.LEVEL"));



			map<string, double> m_mapSlipPoint;
			std::string strReqSlipPointList = pt.get<std::string>("SlipPoint.ReqSlipPointList");
			boost::trim(strReqSlipPointList);
			LOG_INFO << "strReqSlipPointList: " << strReqSlipPointList;

			std::vector<std::string> vecSlipPoint;
			boost::split(vecSlipPoint, strReqSlipPointList, boost::is_any_of(","));

			std::vector<std::string> vecPoint;
			for (vector<string>::iterator it = vecSlipPoint.begin(); it != vecSlipPoint.end(); it++)
			{
				boost::split(vecPoint, *it, boost::is_any_of(":"));
				m_mapSlipPoint[vecPoint[0]] = std::stod(vecPoint[1]);
			}
		}
		catch (std::exception &e)
		{
			std::cout << "error:" << e.what() << std::endl;
			return false;
		}

		return true;
	}

	LOG::sign_severity_level GetLogLevel(){ return log_level; }
private:
	LOG::sign_severity_level log_level;
};