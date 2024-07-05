#pragma once
#include "Register.h"
#include <vector>
#include <string>
#include <fstream>
#include <string.h>

class Machine
{
private:
	Register reg;
	std::vector<std::pair<std::string, int>> loaded_program;
	size_t last_instruct_num;

public:
	Machine();

	int get_reg(size_t address);
	std::pair<std::string, int> get_operator(size_t index);
	size_t get_last_instruct_num() const;

	void zero(int start, int end); // Resets memory cells with addresses from x to y inclusive.
	void set(int address, int value); // Changes to y the contents of the cell with address x.
	void copy(int first_start, int second_start, int address_number); // Copies the contents of z consecutive cells, starting from address x
																			  //in the corresponding z consecutive cells starting from address y.
	void mem(size_t start_address, size_t end_address); // Prints the contents of cells with to standard output addresses from x to y inclusive.
	void qoute(std::string operat); // Adds a new statement (instruction or command) at the end of the loaded program. 
	void load(std::istream& in); // Loads an MRI program from a text file.
	void add(std::istream& in); // Extends the loaded MFA program with operators read from a text file.
	void run_instructions(); // Executes the loaded program.

	void code() const; // Outputs a program loaded in memory to the standard output.
};

