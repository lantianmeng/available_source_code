// observer_subject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include "observe.h"
#include "subject.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<bugao> concreateObserver(new bugao);
	std::shared_ptr<WeatherData> concreateSubject(new WeatherData);
	concreateSubject->registerObserver(concreateObserver.get());
	concreateSubject->setData("beijing", 24.4);

	concreateSubject->removeObserver(concreateObserver.get());
	concreateSubject->setData("wuhan", 30.5);

	std::shared_ptr<WeatherData1> concreateSubject1(new WeatherData1);
	concreateSubject1->registerObserver(concreateObserver.get());
	concreateSubject1->setData("wuhan", 30.5);

	system("pause");
	return 0;
}