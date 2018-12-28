#ifndef SUBJECT_H
#define SUBJECT_H

#include "observe.h"

#include <list>
#include <string>
#include <cassert>

class observe;

class subject
{
public:
	//Attech
	void registerObserver(observe * o)
	{
		assert(o != nullptr);
		observers.push_back(o);
	}

	//Detech
	void removeObserver(observe* o)
	{
		observersIter iter = std::find(observers.begin(), observers.end(), o);
		if (iter != observers.end())
		{
			observers.erase(iter);
		}
	}
protected:
	virtual void notifyObservers() = 0;
protected:
	using observersIter = std::list<observe*>::iterator;
	std::list<observe *> observers;
}; 

class WeatherData :public subject
{
public:
	void setData(std::string address_name_, double temperature_)
	{
		address_name = address_name_;
		temperature = temperature_;

		dataChanged();
	}

	void dataChanged()
	{
		notifyObservers();
	}

	std::string get_address_name() { return address_name; }
	double get_temperature() { return temperature; }
protected:
	void notifyObservers() override
	{
		for (observersIter iter = observers.begin(); iter != observers.end(); ++iter)
		{
			(*iter)->update(address_name, temperature);
		}
	}
private:
	std::string address_name;
	double temperature;
};

class WeatherData1 :public subject
{
public:
	void setData(std::string address_name_, double temperature_)
	{
		address_name = address_name_;
		temperature = temperature_;

		setChanged(true);

		notifyObservers();
	}

	void setChanged(bool bDataChanged_)
	{
		bDataChanged = bDataChanged_;
	}

	std::string get_address_name() { return address_name; }
	double get_temperature() { return temperature; }

protected:
	void notifyObservers() override
	{
		if (bDataChanged)
		{
			for (observersIter iter = observers.begin(); iter != observers.end(); ++iter)
			{
				//(*iter)->update(address_name, temperature);
				(*iter)->update1(this);
			}
		}
		setChanged(false);
	}
private:
	bool bDataChanged;
	std::string address_name;
	double temperature;
};
#endif