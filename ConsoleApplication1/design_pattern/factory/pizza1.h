#ifndef PIZZA1_H
#define PIZZA1_H

#include "pizza.h"

//有两种产品 CheesePizza和BeijingPizza
//虽然在此demo里他们有一个共同的基类，但实际也可以是两种不相关的产品
class CheesePizza_ATiaoLiao :public CheesePizza
{
public:

};

class BeijingPizza_ATiaoLiao :public BeijingPizza
{
public:

};

class CheesePizza_BTiaoLiao :public CheesePizza
{
public:

};

class BeijingPizza_BTiaoLiao :public BeijingPizza
{
public:

};
#endif