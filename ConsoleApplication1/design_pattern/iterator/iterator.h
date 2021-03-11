#ifndef ITERATOR_H
#define ITERATOR_H

#include <list>

class MenuItem;

class iterator
{
public:
	virtual bool HasNext() = 0;
	virtual MenuItem* Next() = 0;
};

class PancakeHouseMenuIterator :public iterator
{
public:
	PancakeHouseMenuIterator(std::list<MenuItem*> menuItems);

	virtual bool HasNext() override;
	virtual MenuItem* Next() override;

private:
	using ItemType = std::list < MenuItem* > ;
	ItemType allItems;
	ItemType::iterator curPosition;
};

class DinerMenuIterator :public iterator
{
public:
	DinerMenuIterator(MenuItem** menuItems, int item_nums);

	virtual bool HasNext() override;
	virtual MenuItem* Next() override;

private:
	MenuItem** allItems;
	int numberOfItems;
	int curPosition;
};

#endif