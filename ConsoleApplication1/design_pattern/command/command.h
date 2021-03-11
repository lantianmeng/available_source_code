#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <memory>

#include "receiver.h"

//�����࣬��Command�ӿ�
class Command
{
public:
	Command(std::shared_ptr<Light> receiver_) :receiver(receiver_) {}
	virtual void execute() = 0;
protected:
	std::shared_ptr<Light> receiver; //����Ľ�����
};

//��������
class LightOnCommand :public Command
{
public:
	LightOnCommand(std::shared_ptr<Light> receiver_) :Command(receiver_) {}
	virtual void execute() override { receiver->On(); }
};

//�ص�����
class LightOffCommand :public Command
{
public:
	LightOffCommand(std::shared_ptr<Light> receiver_) :Command(receiver_) {}
	virtual void execute() override { receiver->Off(); }
};

#endif