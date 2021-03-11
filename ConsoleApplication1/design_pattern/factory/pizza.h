#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <string>
#include <cassert>

class ZuoLiao
{
public:
	ZuoLiao(std::string zl_) :zl(zl_){}
	std::string Get() { return zl; }
private:
	std::string zl;
};

class MianFen
{
public:
	MianFen(std::string mf_) :mf(mf_){}
	std::string Get() { return mf; }
private:
	std::string mf;
};

class Pizza
{
public:
	Pizza(double price_, std::string alias_);

	void SetTiaoLiao(const std::string &z, const std::string &m) { zl = new ZuoLiao(z); mf = new MianFen(m); }

	virtual ~Pizza();
	virtual void print();
protected:
	std::string show();
protected:
    double price;
	std::string alias;

	ZuoLiao *zl;
	MianFen *mf;
};

class CheesePizza :public Pizza
{
public:
	CheesePizza(double price_, std::string alias_, std::string style_);

	virtual void print() override;
	std::string &GetStyle();
private:
	std::string style;
};

class BeijingPizza :public Pizza
{
public:
	BeijingPizza(double price_, std::string alias_, std::string created_method_);

	virtual void print() override;
	std::string &GetMethod();
private:
	std::string created_method;
};

#endif