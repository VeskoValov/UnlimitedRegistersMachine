#pragma once
#include "Machine.h"
class CommandList
{
private:
	Machine machine;
	std::map<std::string, int> commandList;
public:
	CommandList();

	void run();

};

