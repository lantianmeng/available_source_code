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
#include "trade.grpc.pb.h"
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

bool OpenOrder(int& nCMD, int& nOrderBy, std::string& strSymbol, int&  nVolume, double& fMarketOpenPrice, double& fSL, double& fTP, int& nOrderID, __time32_t& nOpenTime, double& fOpenPrice, std::string& strComment, int &error_code)
{
	nOrderID = 5035561;
	nOpenTime = 15000977554;
	fOpenPrice = 1.2045;
	error_code = 0;
	return true;
}

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

class TradeServiceImpl final : public ::mt4api::Trade::Service
{
public:
	// 开仓
	::grpc::Status Open(::grpc::ServerContext* context, const ::mt4api::TradeOpenReq* request, ::mt4api::TradeOpenResp* response) override
	{
		bool bRet = false;
		int RetCode = -1;

		std::string Symbol = request->symbol();
		int MT4ID = request->mt4id();
		int CMD = request->cmd();
		int Volume = request->volume();
		double OpenPrice = request->openprice();
		double SL = request->sl();
		double TP = request->tp();

		double dbMarketOpenPrice = OpenPrice;

		int Ticket = 0;
		__time32_t OpenTime = 0;
		std::string comment = "message";

		//auto ret = m_ThreadPool.commit(std::bind(&CMT4Manager::OpenOrder, this,
		//	CMD, MT4ID, Symbol, Volume, dbMarketOpenPrice, SL, TP,
		//	std::ref(Ticket), std::ref(OpenTime), std::ref(OpenPrice), std::ref(comment), std::ref(RetCode)));
		
		std::function<bool(int& nCMD, int& nOrderBy, std::string& strSymbol, int&  nVolume, double& fMarketOpenPrice, double& fSL, double& fTP,
			int& nOrderID, __time32_t& nOpenTime, double& fOpenPrice, std::string& strComment, int &error_code)>
			fun = std::bind(OpenOrder,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7,
				std::placeholders::_8, std::placeholders::_9, std::placeholders::_10, std::placeholders::_11, std::placeholders::_12);

		auto ret = fun(CMD, MT4ID, Symbol, Volume, dbMarketOpenPrice, SL, TP,
			std::ref(Ticket), std::ref(OpenTime), std::ref(OpenPrice), std::ref(comment), std::ref(RetCode));

		google::protobuf::Arena arena;
		if (ret)
		{
			bRet = true;
			::mt4api::TradeOpenData* data = google::protobuf::Arena::CreateMessage<::mt4api::TradeOpenData>(&arena);
			data->set_symbol(Symbol);
			data->set_mt4id(MT4ID);
			data->set_cmd(CMD);
			data->set_volume(Volume);
			data->set_ticket(Ticket);
			data->set_opentime(OpenTime);
			data->set_openprice(OpenPrice);
			data->set_sl(SL);
			data->set_tp(TP);

			response->set_allocated_data(data);
		}

		response->set_code(RetCode);

		//auto ret = Singleton<CMT4Manager>::GetInstance()->HandleOpenOrder(request, response);
		return ret ? ::grpc::Status::OK : ::grpc::Status(::grpc::StatusCode::DO_NOT_USE, "MT4 Error");
		//return ::grpc::Status::OK;
	}

	// 平仓
	::grpc::Status Close(::grpc::ServerContext* context, const ::mt4api::TradeCloseReq* request, ::mt4api::TradeCloseResp* response) override
	{
		//Singleton<CMT4Manager>::GetInstance()->HandleCloseOrder(request, response);
		return ::grpc::Status::OK;
	}

	// 更新订单
	::grpc::Status Update(::grpc::ServerContext* context, const ::mt4api::TradeUpdateReq* request, ::mt4api::TradeUpdateResp* response) override
	{
		//Singleton<CMT4Manager>::GetInstance()->HandleModifyOrder(request, response);
		return ::grpc::Status::OK;
	}
};

void RunServer(int port) {
	std::string server_address("0.0.0.0:" + std::to_string(port));
	GreeterServiceImpl service;
	TradeServiceImpl trade_service;

	ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	builder.RegisterService(&trade_service);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}