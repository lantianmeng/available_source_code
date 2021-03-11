#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <memory>

#include "receiver.h"

//抽象类，即Command接口
class Command
{
public:
	Command(std::shared_ptr<Light> receiver_) :receiver(receiver_) {}
	virtual void execute() = 0;
protected:
	std::shared_ptr<Light> receiver; //命令的接收者
};

//开灯命令
class LightOnCommand :public Command
{
public:
	LightOnCommand(std::shared_ptr<Light> receiver_) :Command(receiver_) {}
	virtual void execute() override { receiver->On(); }
};

//关灯命令
class LightOffCommand :public Command
{
public:
	LightOffCommand(std::shared_ptr<Light> receiver_) :Command(receiver_) {}
	virtual void execute() override { receiver->Off(); }
};

#endif