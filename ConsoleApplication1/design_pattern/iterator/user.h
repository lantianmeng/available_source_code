#ifndef USER_H
#define USER_H

#include <memory>

#include "iterator.h"
#include "aggregate.h"

class PancakeHouseMenu;
class DinerMenu;

class waitress
{
public:
	waitress(std::shared_ptr<Menu> p_menu, std::shared_ptr<Menu> d_menu) :pancake_menu(p_menu), diner_menu(d_menu) {}
	void printMenu()
	{
		iterator* p_iter = pancake_menu->CreateIterator();
		iterator* d_iter = diner_menu->CreateIterator();
		printMenu(p_iter);
		printMenu(d_iter);
		delete p_iter;
		delete d_iter;
		p_iter = nullptr;
		d_iter = nullptr;
	}
private:
	void printMenu(iterator* iter)
	{
		while (iter->HasNext())
		{
			MenuItem *p_menu = iter->Next();
			std::cout << p_menu->GetName() << "\t"
				<< p_menu->GetDescription() << "\t"
				<< p_menu->GetVegetarian() << "\t"
				<< p_menu->GetPrice() << std::endl;
		}
	}
private:
	std::shared_ptr<Menu> pancake_menu;
	std::shared_ptr<Menu> diner_menu;
};
#endif