#ifndef STRATEGY_H
#define STRATEGY_H

//���Խӿ�
class IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) = 0;
};

//�¿ͻ��ı��۲���
class NewCustomQuoteStrategy:public IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) override
	{
		return orignal_price;//���ۿ�
	}
};

//�Ͽͻ��ı��۲���
class OldCustomQuoteStrategy :public IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) override
	{
		return orignal_price*0.9;//9��
	}
};

//VIP�ͻ��ı��۲���
class VIPCustomQuoteStrategy :public IQuoteStrategy
{
public:
	virtual double GetPrice(double orignal_price) override
	{
		return orignal_price*0.8;//8��
	}
};
#endif