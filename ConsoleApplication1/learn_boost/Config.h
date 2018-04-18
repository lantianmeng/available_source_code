#pragma once

#include <iostream>
#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>  
 
#include "Log.h"

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