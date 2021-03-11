#ifndef AGGREGATE_H
#define AGGREGATE_H

#include <string>
#include <iostream>

class MenuItem
{
public:
	MenuItem(){}
	MenuItem(const std::string& name, const std::string& description, bool vegetarian, double price) 
		:m_name(name), 
		m_description(description), 
		m_vegetarian(vegetarian),
		m_price(price) 
	{
	}
	
	std::string GetName() { return m_name; }
	std::string GetDescription() { return m_description; }
	bool GetVegetarian() { return m_vegetarian; }
	double GetPrice() { return m_price; }
private:
	std::string m_name;
	std::string m_description;
	bool m_vegetarian;//素食
	double m_price;
};

//Menu类，即为aggregate
class Menu
{
public:
	virtual ~Menu(){}
	virtual iterator* CreateIterator() = 0;
};

//pancake 烙饼
class PancakeHouseMenu : public Menu
{
public:
	PancakeHouseMenu()
	{
		AddItem("K&B's Pancake Breakfast", "Pancake with scrambled eggs, and toast", true, 2.99);
		AddItem("Blueberry Pancakes", "Pancakes made with fresh blueberries ", false, 3.49);
	}

	~PancakeHouseMenu()
	{
		for (ItemType::iterator iter = menuItems.begin(); iter != menuItems.end(); ++iter)
		{
			delete *iter;
		}
	}

	virtual iterator* CreateIterator() override
	{
		return new PancakeHouseMenuIterator(menuItems); //使用完成后，需手动delete
	}
private:
	void AddItem(const std::string& name, const std::string& description, bool vegetarian, double price)
	{
		menuItems.push_back(new MenuItem(name, description, vegetarian, price));
	}
private:
	using ItemType = std::list < MenuItem* > ;
	ItemType menuItems;
};


class DinerMenu : public Menu
{
	const int MAX_ITEMS = 6;
public:
	DinerMenu()
	{
		menuItems = new MenuItem*[MAX_ITEMS];
		numberOfItems = 0;

		AddItem("vegetarian BLT", "Bacon with lettuce", true, 2.89);
		AddItem("soup of the day", "with a side of potato salad", false, 3.29);
	}

	~DinerMenu()
	{
		delete [] menuItems;
	}

	virtual iterator* CreateIterator() override
	{
		return new DinerMenuIterator(menuItems, numberOfItems);
	}

private:
	void AddItem(const std::string& name, const std::string& description, bool vegetarian, double price)
	{
		MenuItem * item = new MenuItem(name, description, vegetarian, price);
		if (numberOfItems >= MAX_ITEMS)
		{
			std::cout << "Sorry, menu is full" << std::endl;
		}
		else
		{
			menuItems[numberOfItems++] = item;
		}
	}
private:
	MenuItem** menuItems; //MenuItem[MAX_ITEMS] 指针数组
	int numberOfItems;
	
};
#endif

