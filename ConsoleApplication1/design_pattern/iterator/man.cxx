// iterator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iterator.h"
#include "user.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<PancakeHouseMenu> p_menu = std::make_shared<PancakeHouseMenu>();
	std::shared_ptr<DinerMenu> d_menu = std::make_shared<DinerMenu>();

	std::shared_ptr<waitress> ww = std::make_shared<waitress>(p_menu, d_menu);
	ww->printMenu();

	system("pause");

	return 0;
}

