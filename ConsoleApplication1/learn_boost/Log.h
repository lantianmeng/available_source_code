#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/thread.hpp>
#include <boost/filesystem.hpp> 
#include "boost/filesystem/path.hpp"  
#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/exception.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/exception/all.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include<stdio.h>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace LOG
{

	enum sign_severity_level
	{
		trace,
		debug,
		info,
		warning,
		error,
		fatal,
		report

	};

	//(BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULTmy_logger,src::logger_mt)

	template< typename CharT, typename TraitsT >
	inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, sign_severity_level lvl)
	{
		static const char* const str[] =
		{
			"trace",
			"debug",
			"info",
			"warning",
			"error",
			"fatal",
			"report"
		};
		if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
			strm << str[lvl];
		else
			strm << static_cast<int>(lvl);
		return strm;
	}

	BOOST_LOG_ATTRIBUTE_KEYWORD(_severity, "Severity", sign_severity_level)
		BOOST_LOG_ATTRIBUTE_KEYWORD(_timestamp, "TimeStamp", boost::posix_time::ptime);
	BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt<sign_severity_level>)
}
		//#define LOG_TRACE \
		//	BOOST_LOG_SEV((my_logger::get()),(trace))<< "(" << __FILE__ << ", " << __LINE__ << ") " 
		//#define LOG_DEBUG \
		//	BOOST_LOG_SEV((my_logger::get()),(debug))<< "(" << __FILE__ << ", " << __LINE__ << ") " 
		//#define LOG_INFO \
		//	BOOST_LOG_SEV((my_logger::get()),(info))<< "(" << __FILE__ << ", " << __LINE__ << ") " 
		//#define LOG_WARNING \
		//	BOOST_LOG_SEV((my_logger::get()),(warning))<< "(" << __FILE__ << ", " << __LINE__ << ") " 
		//#define LOG_ERROR \
		//	BOOST_LOG_SEV((my_logger::get()),(error))<< "(" << __FILE__ << ", " << __LINE__ << ") " 
		//#define LOG_FATAL \
		//	BOOST_LOG_SEV((my_logger::get()),(fatal))<< "(" << __FILE__ << ", " << __LINE__ << ") " 
		//#define LOG_REPORT \
		//	BOOST_LOG_SEV((my_logger::get()),(report))<< "(" << __FILE__ << ", " << __LINE__ << ") " 

		//这些宏像下面那样使用时，显示源代码及行号存在一点问题
		//LOG_INFO << "An informational severity message";
		//LOG_WARNING << "A warning severity message";
		//LOG_ERROR << "An error severity message";
		//LOG_FATAL << "A fatal severity message";

#define LOG_TRACE \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::trace)
#define LOG_DEBUG \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::debug)
#define LOG_INFO \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::info)
#define LOG_WARNING \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::warning)
#define LOG_ERROR \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::error)
#define LOG_FATAL \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::fatal)
#define LOG_REPORT \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(LOG::my_logger::get(), LOG::report)

extern void InitLog(LOG::sign_severity_level _lvl = LOG::info, const char *targetpath = "log");