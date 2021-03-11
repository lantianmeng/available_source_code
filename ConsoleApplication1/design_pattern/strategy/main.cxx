// strategy.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "context.h"
#include <memory>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<IQuoteStrategy> strategy = std::make_shared<OldCustomQuoteStrategy>();

	std::shared_ptr<stratege_context> s_context = std::make_shared<stratege_context>(strategy.get());
	std::cout << "�ۿۼ۸�" << s_context->GetPrice(100) << std::endl;

	std::shared_ptr<IQuoteStrategy> strategy_vip = std::make_shared<VIPCustomQuoteStrategy>();
	s_context.reset(new stratege_context(strategy_vip.get()));
	std::cout << "�ۿۼ۸�" << s_context->GetPrice(100) << std::endl;

	system("pause");
	return 0;
}

