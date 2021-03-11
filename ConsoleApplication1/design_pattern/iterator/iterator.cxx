#include "stdafx.h"

#include "iterator.h"
#include "aggregate.h"

PancakeHouseMenuIterator::PancakeHouseMenuIterator(std::list<MenuItem*> menuItems) :allItems(menuItems)
{
	curPosition = allItems.begin();
}

bool PancakeHouseMenuIterator::HasNext()
{
	bool ret = true;
	if (curPosition == allItems.end())
	{
		ret = false;
	}

	return ret;
}

MenuItem* PancakeHouseMenuIterator::Next()
{
	MenuItem *t = *curPosition;
	++curPosition;
	return t;
}

DinerMenuIterator::DinerMenuIterator(MenuItem** menuItems, int item_nums) :allItems(menuItems), numberOfItems(item_nums), curPosition(0)
{
}

bool DinerMenuIterator::HasNext()
{
	bool ret = true;
	if (curPosition >= numberOfItems)
	{
		ret = false;
	}

	return ret;
}

MenuItem* DinerMenuIterator::Next()
{
	MenuItem *t = allItems[curPosition];
	++curPosition;
	return t;
}