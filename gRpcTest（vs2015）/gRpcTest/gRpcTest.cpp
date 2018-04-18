// gRpcTest.cpp : 定义控制台应用程序的入口点。
//

/*
*
* Copyright 2015 gRPC authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#include "stdafx.h"

#include <grpc/support/log.h>

#include <iostream>
#include <memory>
#include <string>

#include "GrpcClient.h"
//#include <grpcpp/grpcpp.h>
//
//#ifdef BAZEL_BUILD
//#include "examples/protos/helloworld.grpc.pb.h"
//#else
////#include "helloworld.grpc.pb.h"
//#include "service.grpc.pb.h"
//#endif
//
//using grpc::Channel;
//using grpc::ClientContext;
//using grpc::Status;
////using helloworld::HelloRequest;
////using helloworld::HelloReply;
////using helloworld::Greeter;
//using service::Connect;
//using service::NullReq;
//using service::PingResp;

//class GreeterClient {
//public:
//	GreeterClient(std::shared_ptr<Channel> channel)
//		: stub_(Connect::NewStub(channel)) {}
//
//	// Assembles the client's payload, sends it and presents the response back
//	// from the server.
//	std::string Ping() {
//		// Data we are sending to the server.
//		NullReq request;
//		//request.set_name(user);
//
//		// Container for the data we expect from the server.
//		PingResp reply;
//
//		// Context for the client. It could be used to convey extra information to
//		// the server and/or tweak certain RPC behaviors.
//		ClientContext context;
//
//		// The actual RPC.
//		Status status = stub_->Ping(&context, request, &reply);
//
//		// Act upon its status.
//		if (status.ok()) {
//			return reply.message();
//		}
//		else {
//			std::cout << status.error_code() << ": " << status.error_message()
//				<< std::endl;
//			return "RPC failed";
//		}
//	}
//
//private:
//	std::unique_ptr<Connect::Stub> stub_;
//};

int main(int argc, char** argv) {
	// Instantiate the client. It requires a channel, out of which the actual RPCs
	// are created. This channel models a connection to an endpoint (in this case,
	// localhost at port 50051). We indicate that the channel isn't authenticated
	// (use of InsecureChannelCredentials()).
	GreeterClient greeter(grpc::CreateChannel(
		"localhost:50051", grpc::InsecureChannelCredentials()));
	//std::string user("world");
	//std::string reply = greeter.SayHello(user);
	//std::string reply = greeter.Ping();
	//std::cout << "Greeter received: " << reply << std::endl;

	ActivationReq req;
	req.set_symbol("EURUSD");
	req.set_activation(1);
	req.set_cmd(0);
	req.set_mt4_id(3800);
	req.set_volume(5.00);
	req.set_ticket(4623051);
	req.set_open_time(1522652486);
	req.set_close_time(1522652486);
	req.set_open_price(1.23241);
	req.set_close_price(1.23241);
	req.set_profit(-75.00);
	req.set_sl(0.00);
	req.set_tp(0.00);
	req.set_expiration(0.00);
	req.set_time_stamp(1522652486);

	greeter.Activation(req);

	gpr_set_log_verbosity(GPR_LOG_SEVERITY_DEBUG);
	gpr_log(GPR_DEBUG, "format string %d", 3);
	gpr_log(GPR_INFO, "hello world");
	gpr_log(GPR_ERROR, "%d %s!!", 4, "server");

	system("pause");
	return 0;
}