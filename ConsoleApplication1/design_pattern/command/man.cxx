// command.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "client.h"
#include "receiver.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<SimpleRemoteControl> remote = std::make_shared<SimpleRemoteControl>();
	std::shared_ptr<Light> light = std::make_shared<Light>();

	std::shared_ptr<LightOnCommand> lighton = std::make_shared<LightOnCommand>(light);
	remote->setCommand(lighton);
	remote->buttonPressed();

	std::shared_ptr<LightOffCommand> lightoff = std::make_shared<LightOffCommand>(light);
	remote->setCommand(lightoff);
	remote->buttonPressed();

	system("pause");
	return 0;
}

