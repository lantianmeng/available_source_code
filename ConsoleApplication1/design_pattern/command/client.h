#ifndef CLIENT_H
#define CLIENT_H

#include "command.h"

//ʹ��������࣬��client
class SimpleRemoteControl
{
public:
	void setCommand(std::shared_ptr<Command> slot_){ slot = slot_; }
	void buttonPressed(){ slot->execute(); }
private:
	std::shared_ptr<Command> slot;
};

#endif