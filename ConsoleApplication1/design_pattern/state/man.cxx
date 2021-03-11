// state.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Machine.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<GumballMachine> mm = std::make_shared<GumballMachine>(5);
	mm->TurnCrank();

	mm->InsertQuarter();
	mm->TurnCrank();
	mm->Dispense();

	system("pause");
	return 0;
}

