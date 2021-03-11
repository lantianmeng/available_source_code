#ifndef STRATEGY_H
#define STRATEGY_H

//策略接口
class IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) = 0;
};

//新客户的报价策略
class NewCustomQuoteStrategy:public IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) override
	{
		return orignal_price;//无折扣
	}
};

//老客户的报价策略
class OldCustomQuoteStrategy :public IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) override
	{
		return orignal_price*0.9;//9折
	}
};

//VIP客户的报价策略
class VIPCustomQuoteStrategy :public IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) override
	{
		return orignal_price*0.8;//8折
	}
};
#endif