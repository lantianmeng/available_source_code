#include "stdafx.h"

#include "observe.h"
#include "subject.h"

void bugao::update(std::string address_name_, double temperature_) 
{
	address_name = address_name_;
	temperature = temperature_;
	show();
}

void bugao::update1(subject *obj)
{
	if (strcmp(typeid(*obj).name(), typeid(WeatherData1).name()) == 0)
	{
		WeatherData1 *pData = dynamic_cast<WeatherData1 *>(obj);
		//WeatherData1 *pData = reinterpret_cast<WeatherData1 *>(obj);

		address_name = pData->get_address_name();
		temperature = pData->get_temperature();

		show();
	}
}