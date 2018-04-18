#include "stdafx.h"
#include "Log.h"

using namespace LOG;

void InitLog(LOG::sign_severity_level _lvl, const char *targetpath)
{
	boost::shared_ptr<logging::core> core = logging::core::get();
	//typedef sinks::synchronous_sink<sinks::text_file_backend> TextSink;
	typedef sinks::asynchronous_sink<sinks::text_file_backend> TextSink;
	// init sink1
	std::string sttr(targetpath);
	sttr += "\\%Y%m%d__%H_%M_%S.%N.log";
	boost::shared_ptr<sinks::text_file_backend> backend1 = boost::make_shared<sinks::text_file_backend>(
		keywords::file_name = sttr.c_str(),
		keywords::open_mode = std::ios::app,
		keywords::rotation_size = 256 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(boost::gregorian::greg_day(1), 0, 0, 0),
		keywords::min_free_space = 100 * 1024 * 1024);

	boost::shared_ptr<TextSink> sink1(new TextSink(backend1));
	sink1->locked_backend()->set_file_collector(sinks::file::make_collector(
		keywords::target = targetpath,                          // where to store rotated files  
		keywords::max_size = 1024 * 1024 * 1024,              // maximum total size of the stored files, in bytes  
		keywords::min_free_space = 1024 * 1024 * 1024        // minimum free space on the drive, in bytes  
	));
	sink1->set_formatter(
		expr::format("[%1%][%2%][%3%]:%4%")
		//expr::format("%1%:[%2%][%3%][%4%]:%5%")
		//% expr::format_named_scope("Scopes", boost::log::keywords::format = "%f:%l")
		% expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
		% expr::attr<sign_severity_level>("Severity")
		% expr::attr<attrs::current_thread_id::value_type>("ThreadID")
		% expr::smessage
		// % expr::format_named_scope("Scopes", boost::log::keywords::format = "%n [%f : %l]")
	);
	sink1->set_filter(expr::attr<sign_severity_level>("Severity") >= _lvl);
	sink1->locked_backend()->scan_for_files();//
	backend1->auto_flush(true);
	core->add_sink(sink1);


	//¿ØÖÆÌ¨
	auto asink = logging::add_console_log(std::clog, keywords::format = expr::stream
		<< expr::format_date_time(_timestamp, "%Y-%m-%d %H:%M:%S.%f")
		<< " <" << _severity
		<< ">: " << expr::smessage);
	asink->set_filter(expr::attr< sign_severity_level >("Severity") >= _lvl);
	core->add_sink(asink);

	logging::add_common_attributes();
	core->add_global_attribute("Scopes", attrs::named_scope());
}