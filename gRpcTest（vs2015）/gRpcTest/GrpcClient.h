#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
//#include "helloworld.grpc.pb.h"
#include "activation.grpc.pb.h"
#include "trade.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
//using helloworld::HelloRequest;
//using helloworld::HelloReply;
//using helloworld::Greeter;
using service::MT4Callback;
using service::ActivationReq;
using service::NullResp;

class GreeterClient {
public:
	GreeterClient(std::shared_ptr<Channel> channel)
		: stub_(MT4Callback::NewStub(channel)) {}

	// Assembles the client's payload, sends it and presents the response back
	// from the server.
	void Activation(ActivationReq data) {
		// Data we are sending to the server.
		ActivationReq request(data);
		//request.set_name(user);

		// Container for the data we expect from the server.
		NullResp reply;

		// Context for the client. It could be used to convey extra information to
		// the server and/or tweak certain RPC behaviors.
		ClientContext context;

		// The actual RPC.
		Status status = stub_->Activation(&context, request, &reply);

		// Act upon its status.
		//if (status.ok()) {
		//	return reply.message();
		//}
		//else {
		//	std::cout << status.error_code() << ": " << status.error_message()
		//		<< std::endl;
		//	return "RPC failed";
		//}
	}

private:
	std::unique_ptr<MT4Callback::Stub> stub_;
};

class TradeClient {
public:
	TradeClient(std::shared_ptr<Channel> channel)
		: stub_(::mt4api::Trade::NewStub(channel)) {}

	// Assembles the client's payload, sends it and presents the response back
	// from the server.
	bool OpenOrder(const ::mt4api::TradeOpenReq& request, ::mt4api::TradeOpenResp* response) {
		// Data we are sending to the server.
		//ActivationReq request(data);
		//request.set_name(user);

		// Container for the data we expect from the server.
		//NullResp reply;

		// Context for the client. It could be used to convey extra information to
		// the server and/or tweak certain RPC behaviors.
		//ClientContext context; // as class data member

		// The actual RPC.
		Status status = stub_->Open(&context, request, response);

		// Act upon its status.
		if (status.ok()) {
			return true;
		}
		else {
			std::cout << status.error_code() << ": " << status.error_message()
				<< std::endl;
			return false;
		}
	}

private:
	std::unique_ptr<::mt4api::Trade::Stub> stub_;
	// Context for the client. It could be used to convey extra information to
	// the server and/or tweak certain RPC behaviors.
	ClientContext context;
};