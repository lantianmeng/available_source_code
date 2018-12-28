#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <string>
#include <cassert>

#include "abstractFactory.h"

class Pizza
{
public:
	Pizza(double price_, std::string alias_);
	Pizza(double price_, std::string alias_, TiaoLiaoAbstactFactory *factory_);
	void SetFactory(TiaoLiaoAbstactFactory *factory_);
	void PrepareTiaoLiao();
	virtual ~Pizza();
	virtual void print();
protected:
	std::string show();
protected:
    double price;
	std::string alias;

	TiaoLiaoAbstactFactory* factory;
	ZuoLiao *zl;
	MianFen *mf;
};

class CheesePizza :public Pizza
{
public:
	CheesePizza(double price_, std::string alias_, std::string style_);
	CheesePizza(double price_, std::string alias_, std::string style_, TiaoLiaoAbstactFactory *factory_);
	virtual void print() override;
	std::string &GetStyle();
private:
	std::string style;
};

class BeijingPizza :public Pizza
{
public:
	BeijingPizza(double price_, std::string alias_, std::string created_method_);
	BeijingPizza(double price_, std::string alias_, std::string created_method_, TiaoLiaoAbstactFactory *factory_);
	virtual void print() override;
	std::string &GetMethod();
private:
	std::string created_method;
};

#endif