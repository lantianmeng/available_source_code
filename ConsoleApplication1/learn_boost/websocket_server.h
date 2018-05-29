#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

bool validate(server *, websocketpp::connection_hdl) {
	//sleep(6);
	return true;
}

void on_http(server* s, websocketpp::connection_hdl hdl) {
	server::connection_ptr con = s->get_con_from_hdl(hdl);

	std::string res = con->get_request_body();

	std::stringstream ss;
	ss << "got HTTP request with " << res.size() << " bytes of body data.";

	con->set_body(ss.str());
	con->set_status(websocketpp::http::status_code::ok);
}

void on_fail(server* s, websocketpp::connection_hdl hdl) {
	server::connection_ptr con = s->get_con_from_hdl(hdl);

	std::cout << "Fail handler: " << con->get_ec() << " " << con->get_ec().message() << std::endl;
}

void on_close(websocketpp::connection_hdl) {
	std::cout << "Close handler" << std::endl;
}

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
	std::cout << "on_message called with hdl: " << hdl.lock().get()
		<< " and message: " << msg->get_payload()
		<< std::endl;

	server::connection_ptr con = s->get_con_from_hdl(hdl);
	boost::asio::ip::tcp::socket& sock = con->get_socket();

	string strReceive = msg->get_payload();
	string strDecode = strReceive;

	websocketpp::http::parser::request rt = con->get_request();
	const string& strUri = rt.get_uri();
	const string& strMethod = rt.get_method();
	const string& strBody = rt.get_body();//只针对post时有数据
	const string& strVersion = rt.get_version();
	const string& strHost = rt.get_header("host");


	// check for a special command to instruct the server to stop listening so
	// it can be cleanly exited.
	if (msg->get_payload() == "stop-listening") {
		s->stop_listening();
		return;
	}

	try {
		s->send(hdl, msg->get_payload(), msg->get_opcode());
	}
	catch (const websocketpp::lib::error_code& e) {
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}
}

class Server
{
public:
	Server(int port_ = 9002) :port(port_) {}
	virtual ~Server() {}

	void start()
	{
		try {
			// Set logging settings
			echo_server.set_access_channels(websocketpp::log::alevel::all);
			echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

			// Initialize Asio
			echo_server.init_asio();

			// Register our message handler
			echo_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));

			echo_server.set_http_handler(bind(&on_http, &echo_server, ::_1));
			echo_server.set_fail_handler(bind(&on_fail, &echo_server, ::_1));
			echo_server.set_close_handler(&on_close);

			echo_server.set_validate_handler(bind(&validate, &echo_server, ::_1));
			//echo_server.set_socket_init_handler();

			// Listen on port 9002
			echo_server.listen(port);

			// Start the server accept loop
			echo_server.start_accept();

			// Start the ASIO io_service run loop
			echo_server.run();
		}
		catch (websocketpp::exception const & e) {
			std::cout << e.what() << std::endl;
		}
		catch (...) {
			std::cout << "other exception" << std::endl;
		}
	}
private:
	int port;
	// Create a server endpoint
	server echo_server;
};