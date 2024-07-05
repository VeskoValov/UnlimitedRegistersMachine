#include "CommandList.h"

CommandList::CommandList()
{
	machine = {};
	commandList = { {"/zero", 0}, {"/set", 1}, {"/copy", 2}, {"/mem", 3}, {"/load", 4}, 
		{"/run", 5}, {"/add", 6}, {"/quote", 7}, {"/code", 8}, {"/help", 9}, {"/exit", 10}, {"/comment", 11} };

}

void CommandList::run()
{
	std::cout << "Welcome!" << std::endl;
	std::string command = " ", values;
	int commandNum;
	while (true) {
		std::getline(std::cin, command, ' ');
		std::getline(std::cin, values);
		std::cin.clear();
		if (commandList.find(command) == commandList.end()) {
			std::cout << "Invalid command! Please try again." << '\n';
		}
		else {
			commandNum = this->commandList[command];
			switch (commandNum) 
			{
				case 0: 
				{
					int index = 0;
					while (values[index] != ' ') {
						index++;
					}
					this->machine.zero(atoi(values.c_str()), atoi((values.substr(index, values.size() - 1)).c_str()));
				} break;
				case 1: 
				{
					int index = 0;
					while (values[index] != ' ') {
						index++;
					}
					this->machine.set(atoi(values.c_str()), atoi((values.substr(index, values.size() - 1)).c_str()));
				} break;
				case 2:
				{
					std::string::reverse_iterator it = values.rbegin();
					int b_index = 0;
					while (*it != ' ') {
						b_index++;
						it++;
					}
					int index = 0;
					while (values[index] != ' ') {
						index++;
					}
					this->machine.copy(atoi(values.c_str()), atoi((values.substr(index, b_index)).c_str()), 
						atoi((values.substr(values.size() - b_index - 1, values.size() - 1)).c_str()));
				} break;
				case 3:
				{
					int index = 0;
					while (values[index] != ' ') {
						index++;
					}
					std::cout << "/comment Output is ";
					this->machine.mem(atoi(values.c_str()), atoi((values.substr(index, values.size() - 1)).c_str()));
					std::cout << '\n';
				} break;
				case 4: 
				{
					std::ifstream fi(values);
					if (fi.good()) {
						this->machine.load(fi);
						std::cout << "/comment File loaded successfully!" << '\n';
						fi.close();
					}
					else {
						std::cout << "/comment Path does not exist!" << '\n';
					}
				} break;
				case 5:
				{
					this->machine.run_instructions();
				} break;
				case 6:
				{
					std::ifstream fi(values);
					if (fi.good()) {
						this->machine.add(fi);
						std::cout << "/comment File added successfully!" << '\n';
						fi.close();
					}
					else {
						std::cout << "/comment Path does not exist!" << '\n';
					}
				} break;
				case 7:
				{
					if (commandList.find(values) == commandList.end()) {
						std::cout << "/comment Invalid operator! Please try again." << '\n';
						continue;
					}
					this->machine.qoute(values);
				} break;
				case 8:
				{
					this->machine.code();
				} break;
				case 9:
				{
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/zero x y: - Resets memory cells with addresses from x to y inclusive." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/set x y: Changes to y the contents of the cell with address x." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/copy x y z: Copies the contents of z consecutive cells, starting from address x " << std::endl;
					std::cout << "in the corresponding z consecutive cells starting from address y." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/mem x y: Prints the contents of cells with to standard output addresses from x to y inclusive." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/load <filename>: Loads an MRI program from a text file." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/run: Executes the loaded program." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/add <filename>: Extends the loaded MFA program with operators read from a text file." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/quote <string>: Adds a new statement (instruction or command) at the end of the loaded program." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/code: Outputs a program loaded in memory to the standard output." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
					std::cout << "/comment <string>: No effect, serves to add a comment." << std::endl;
					std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
				} break;
				case 10:
				{
					exit(0);
				}
			}
		}

	}
}
