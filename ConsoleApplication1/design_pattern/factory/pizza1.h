#ifndef PIZZA1_H
#define PIZZA1_H

#include <iostream>
#include "abstractFactory.h"

class Pizza1
{
public:
	Pizza1(TiaoLiaoAbstactFactory *factory_) :factory(factory_), zl(nullptr), mf(nullptr)
	{

	}

	virtual Pizza1* Create()
	{
		return this;
	}

	virtual ~Pizza1()
	{
		if (zl) delete zl; zl = nullptr;
		if (mf) delete mf; mf = nullptr;
	}

	void print()
	{
		assert(zl != nullptr && mf != nullptr);
		std::cout << zl->Get() << " " << mf->Get();
	}
protected:
	TiaoLiaoAbstactFactory* factory;
	ZuoLiao *zl;
	MianFen *mf;
};

class NyStylePizza1 : public Pizza1
{
public:
	NyStylePizza1(TiaoLiaoAbstactFactory *factory_) : Pizza1(factory_)
	{

	}

	virtual Pizza1* Create()
	{
		zl = factory->CreateZuoLiao();
		mf = factory->CreateMianFen();

		return this;
	}
};

class BeijingPizza1 : public Pizza1
{
public:
	BeijingPizza1(TiaoLiaoAbstactFactory *factory_) : Pizza1(factory_)
	{
	}

	virtual Pizza1* Create()
	{
		zl = factory->CreateZuoLiao();
		mf = factory->CreateMianFen();

		return this;
	}

	~BeijingPizza1()
	{
	}
};
#endif