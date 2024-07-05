#include "Register.h"

Register::Register()
{
	this->cells = {};
}

void Register::zero(size_t address)
{
	this->cells[address] = 0;
}

void Register::inc(size_t address)
{
	this->cells[address]++;
}

void Register::move(size_t r_address, size_t l_address)
{
	if (this->cells.find(l_address) == this->cells.end() ||
		this->cells.find(l_address) == this->cells.end()) {
		return;
	}
	this->cells[l_address] = this->cells[r_address];
}

void Register::set(size_t address, int value)
{
	this->cells[address] = value;
}

int Register::return_value(size_t address)
{
	return this->cells[address];
}

int Register::size() const
{
	return this->cells.size();
}

void Register::print_cell(size_t address)
{
	if (this->cells.find(address) == this->cells.end()) {
		return;
	}
	std::cout << this->cells[address] << ' ';
}

std::map<const int, int>::const_iterator Register::begin() const
{
	return this->cells.begin();
}

std::map<const int, int>::const_iterator Register::end() const
{
	return this->cells.end();
}

//void Register::zero(size_t address)
//{
//	if (!cells.empty() && this->cells.back().second < address) {
//		this->cells.push_back(std::pair<int, int>(0, address));
//		return;
//	}
//	std::list<std::pair<int, int>>::iterator cell;
//	for (cell = this->cells.begin(); 
//		 cell != this->cells.end();
//		 cell++) {
//
//		if (cell->second == address) {
//			cell->first = 0;
//			return;
//		}
//		if (cell->second > address) {
//			break;
//		}
//	}
//
//	this->cells.insert(cell, std::pair<int, int>(0, address));
//}