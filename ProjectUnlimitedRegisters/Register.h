#pragma once
#include <map>
#include <iostream>

class Register
{
private:
	std::map<const int, int> cells;
public:
	Register();

	void zero(size_t address); // Writes the value 0 to the cell with address n.
	void inc(size_t address); // Increments the value written in the address cell by one.
	void move(size_t r_address, size_t l_address); // Assigns the cell with address y the value of the cell with address x.

	void set(size_t address, int value); // Changes to y the contents of the cell with address x.
	int return_value(size_t address); // Returns the contents of the cell at the address.
	int size() const; // Returns the size of the register.
	void print_cell(size_t address); // Prints the contents of a cell at the address.

	std::map<const int, int>::const_iterator begin() const;
	std::map<const int, int>::const_iterator end() const;
};

