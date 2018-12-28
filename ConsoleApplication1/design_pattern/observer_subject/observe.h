#ifndef OBSERVE_H
#define OBSERVE_H

#include <iostream>
#include <string>

class subject;
class WeatherData1;

class observe
{
public:
	virtual void update(std::string address_name, double temperature) = 0;
	virtual void update1(subject *obj) = 0;
};

class bugao :public observe
{
public:
	void update(std::string address_name_, double temperature_) override;

	void update1(subject *obj) override;

	void show()
	{
		std::cout << "address_name:" << address_name << " temperature:" << temperature << std::endl;
	}
private:
	std::string address_name;
	double temperature;
};
#endif