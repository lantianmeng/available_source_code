#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
//#include "helloworld.grpc.pb.h"
#include "activation.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
//using helloworld::HelloRequest;
//using helloworld::HelloReply;
//using helloworld::Greeter;
using service::MT4Callback;
using service::ActivationReq;
using service::NullResp;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public MT4Callback::Service {
	Status Activation(ServerContext* context, const ActivationReq* request,
		NullResp* reply) override {
		//std::string prefix("Hello ");
		//reply->set_message(prefix + request->name());
		std::cout << "symbol:" << request->symbol() << " "
			<< "activation:" << request->activation() << " "
			<< "cmd:" << request->cmd() << " "
			<< "mt4_id:" << request->mt4_id() << " "
			<< "volume:" << request->volume() << " "
			<< "ticket:" << request->ticket() << " "
			<< "open_time:" << request->open_time() << " "
			<< "close_time:" << request->close_time() << " "
			<< "close_price:" << request->open_price() << " "
			<< "profit:" << request->profit() << " "
			<< "sl:" << request->sl() << " "
			<< "tp:" << request->tp() << " "
			<< "expiration:" << request->expiration() << " "
			<< "time_stamp:" << request->time_stamp() << " "
			//<< "action_type:" << request->action_type() << " "
			<< std::endl;
		return Status::OK;
	}
};

void RunServer(int port) {
	std::string server_address("0.0.0.0:" + std::to_string(port));
	GreeterServiceImpl service;

	ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}