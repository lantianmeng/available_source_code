#include "stdafx.h"
#include "factory.h"
#include "pizza.h"
#include <iostream>

Pizza::Pizza(double price_, std::string alias_)
	:price(price_),
	alias(alias_),
	zl(nullptr),
	mf(nullptr)
{

}

Pizza::~Pizza()
{
	if (zl) delete zl; zl = nullptr;
	if (mf) delete mf; mf = nullptr;
}

void Pizza::print()
{
	std::cout << show() << std::endl;
}

std::string Pizza::show()
{
	std::string temp("");
	temp = "price:" + std::to_string(price) + " alias:" + alias;

	if (zl) temp += " zuoliao:" + zl->Get();
	if (mf) temp += " mianfen:" + mf->Get();

	return temp;
}

CheesePizza::CheesePizza(double price_, std::string alias_, std::string style_)
	:Pizza(price_, alias_),
	style(style_)
{
}

void CheesePizza::print()
{
	std::cout << "CheesePizza:" << show() << " style:" << style << std::endl;
}

std::string & CheesePizza::GetStyle()
{
	return style;
}

BeijingPizza::BeijingPizza(double price_, std::string alias_, std::string created_method_)
	:Pizza(price_, alias_),
	created_method(created_method_)
{

}

void BeijingPizza::print()
{
	std::cout << "BeijingPizza:" << show() << " created_method:" << created_method << std::endl;
}

std::string & BeijingPizza::GetMethod()
{
	return created_method;
}
