#include "Machine.h"

Machine::Machine()
{
	this->reg = {};
	this->loaded_program = {};
	this->last_instruct_num = 0;
}

int Machine::get_reg(size_t address)
{
	return this->reg.return_value(address);
}

std::pair<std::string, int> Machine::get_operator(size_t index)
{
	return this->loaded_program[index];
}

size_t Machine::get_last_instruct_num() const
{
	return this->last_instruct_num;
}

void Machine::zero(int start, int end)
{
	if (start < 0 || end < 0) {
		std::cout << "Invalid input parameters!" << '\n';
		return;
	}
	for (int i = start; i <= end; i++) {
		this->reg.zero(i);
	}
}

void Machine::set(int address, int value)
{
	if (address < 0 || value < 0) {
		std::cout << "Invalid input parameters!" << '\n';
		return;
	}
	this->reg.set(address, value);
}

void Machine::copy(int first_start, int second_start, int address_number)
{
	if (first_start < 0 || second_start < 0 || address_number < 0) {
		std::cout << "Invalid input parameters!" << '\n';
		return;
	}
	for (size_t i = first_start; i < address_number; i++)
	{
		this->reg.move(i, i + second_start);
	}
}

void Machine::mem(size_t start_address, size_t end_address)
{
	if (this->reg.size() == 0) {
		return;
	}
	for (size_t i = start_address; i <= end_address; i++)
	{
		this->reg.print_cell(i);
	}
}

void Machine::qoute(std::string operat)
{
	if (operat[0] != '/') {
		this->loaded_program.push_back(std::pair<std::string, int>(operat, this->last_instruct_num++));
	}
	else {
		this->loaded_program.push_back(std::pair<std::string, int>(operat, -1));
	}
}

void Machine::load(std::istream& in)
{
	std::string buffer;
	this->loaded_program.clear();
	this->last_instruct_num = 0;
	while (!in.eof()) {
		std::getline(in, buffer);
		if (buffer[0] != '/') {
			this->loaded_program.push_back(std::pair<std::string, int>(buffer, this->last_instruct_num++));
		}
		else if (buffer[3] != 'm') {
			this->loaded_program.push_back(std::pair<std::string, int>(buffer, -1));
		}
	}
}

void Machine::add(std::istream& in)
{
	std::string buffer;
	size_t N = 0;
	size_t upper_bound = 0;
	if (!this->loaded_program.empty()) {
		std::vector<std::pair<std::string, int>>::reverse_iterator it = this->loaded_program.rbegin();
		while (it != this->loaded_program.rend()) {
			if (it->first[0] == 'Z' || it->first[1] == 'z') {
				if ((int)*it->first.rbegin() - '0' > upper_bound) {
					upper_bound = (int)*it->first.rbegin() - '0';
				}
				
			}
			if (it->first[1] == 's') {
				if ((int)*(it->first.rbegin() + 2) - '0' > upper_bound) {
					upper_bound = (int)*(it->first.rbegin() + 2) - '0';
				}
			}
			it++;
		}
	}
	N = last_instruct_num;
	while (!in.eof()) {
		std::getline(in, buffer);
		if (buffer[0] != '/') {
			if (buffer[0] == 'M') {
				std::string temp;
				size_t addr1 = 0;
				size_t addr2 = 0;
				int i = 0;
				bool addr1_found = false;
				for (i = buffer.size() - 1; i != -1; i--)
				{
					if (buffer[i] == ' ') {
						if (!addr1_found) {
							std::reverse(temp.begin(), temp.end());
							addr1 = atoi(temp.c_str());
							addr1_found = true;
							temp.clear();
						}
						else {
							std::reverse(temp.begin(), temp.end());
							addr2 = atoi(temp.c_str());
							break;
						}
					}
					temp += buffer[i];
				}
				buffer = buffer.substr(0, i);
				addr1 += upper_bound + 1;
				addr2 += upper_bound + 1;
				temp = ' ' + std::to_string(addr1) + ' ';
				buffer += temp;
				temp = std::to_string(addr2);
				buffer += temp;
			}
			else if (buffer[0] == 'J') {
				std::string temp;
				size_t addr1 = 0;
				size_t addr2 = 0;
				size_t place = 0;
				int i = 0;
				bool addr1_found = false;
				bool place_found = false;
				for (i = buffer.size() - 1; i != -1; i--)
				{
					if (buffer[i] == ' ') {
						if (!place_found) {
							std::reverse(temp.begin(), temp.end());
							place = atoi(temp.c_str());
							place_found = true;
							temp.clear();
							if (buffer[i - 1] == 'P') {
								break;
							}
						}
						else if (!addr1_found) {
							std::reverse(temp.begin(), temp.end());
							addr1 = atoi(temp.c_str());
							addr1_found = true;
							temp.clear();
						}
						else {
							std::reverse(temp.begin(), temp.end());
							addr2 = atoi(temp.c_str());
							break;
						}
					}
					temp += buffer[i];
				}
				buffer = buffer.substr(0, i);
				if (addr1_found) {
					addr1 += upper_bound + 1;
					addr2 += upper_bound + 1;
					temp = ' ' + std::to_string(addr1) + ' ';
					buffer += temp;
					temp = std::to_string(addr2);
					buffer += temp;
				}
				place += N;
				temp = ' ' + std::to_string(place);
				buffer += temp;
				temp.clear();
			}
			else {
				std::string temp;
				size_t addr = 0;
				int i = 0;
				for (i = buffer.size() - 1; i != -1; i--)
				{
					if (buffer[i] == ' ') {
						std::reverse(temp.begin(), temp.end());
						addr = atoi(temp.c_str());
						temp.clear();
						break;
					}
					temp += buffer[i];
				}
				buffer = buffer.substr(0, i);
				addr += upper_bound + 1;
				temp = ' ' + std::to_string(addr);
				buffer += temp;
			}
				
			this->loaded_program.push_back(std::pair<std::string, int>(buffer, this->last_instruct_num++));
		}
		else if (buffer[3] != 'm') {
			this->loaded_program.push_back(std::pair<std::string, int>(buffer, -1));
		}
	}
}

void Machine::run_instructions()
{
	std::vector<std::pair<std::string, int>>::iterator cursor = this->loaded_program.begin();
	std::vector<std::pair<std::string, int>>::iterator cursor_end = this->loaded_program.end();
	for (cursor; cursor != cursor_end; cursor++) {
		if (cursor->first[0] == 'Z') {
			std::string temp;
			size_t addr = 0;
			for (int i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					std::reverse(temp.begin(), temp.end());
					addr = atoi(temp.c_str());
					temp.clear();
					break;
				}
				temp += cursor->first[i];
			}
			this->reg.zero(addr);
		}
		else if (cursor->first[0] == 'I') {
			std::string temp;
			size_t addr = 0;
			for (int i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					std::reverse(temp.begin(), temp.end());
					addr = atoi(temp.c_str());
					temp.clear();
					break;
				}
				temp += cursor->first[i];
			}
			this->reg.inc(addr);
		}
		else if (cursor->first[0] == 'M') {
			std::string temp;
			size_t addr1 = 0;
			size_t addr2 = 0;
			bool addr1_found = false;
			for (int i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					if (!addr1_found) {
						std::reverse(temp.begin(), temp.end());
						addr1 = atoi(temp.c_str());
						addr1_found = true;
						temp.clear();
					}
					else {
						std::reverse(temp.begin(), temp.end());
						addr2 = atoi(temp.c_str());
						break;
					}
				}
				temp += cursor->first[i];
			}
			this->reg.move(addr2, addr1);
		}
		else if (cursor->first[0] == 'J') {
			std::string temp;
			size_t addr1 = 0;
			size_t addr2 = 0;
			size_t place = 0;
			int i = 0;
			bool addr1_found = false;
			bool place_found = false;
			for (i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					if (!place_found) {
						std::reverse(temp.begin(), temp.end());
						place = atoi(temp.c_str());
						place_found = true;
						temp.clear();
						if (cursor->first[i - 1] == 'P') {
							break;
						}
					}
					else if (!addr1_found) {
						std::reverse(temp.begin(), temp.end());
						addr1 = atoi(temp.c_str());
						addr1_found = true;
						temp.clear();
					}
					else {
						std::reverse(temp.begin(), temp.end());
						addr2 = atoi(temp.c_str());
						break;
					}
				}
				temp += cursor->first[i];
			}
			if (addr1_found && this->reg.return_value(addr1) != this->reg.return_value(addr2)) {
				continue;
			}
			else if (place > this->last_instruct_num - 1) {
				break;
			}
			else {
				if (cursor->second < place) {
					while (cursor->second != place - 1) {
						cursor++;
					}
				}
				else {
					while (cursor->second != place - 1) {
						cursor--;
					}
				}
			}
		}
		else if (cursor->first[1] == 'z') {
			std::string temp;
			size_t addr1 = 0;
			size_t addr2 = 0;
			bool addr1_found = false;
			for (int i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					if (!addr1_found) {
						std::reverse(temp.begin(), temp.end());
						addr1 = atoi(temp.c_str());
						addr1_found = true;
						temp.clear();
					}
					else {
						std::reverse(temp.begin(), temp.end());
						addr2 = atoi(temp.c_str());
						break;
					}
				}
				temp += cursor->first[i];
			}
			this->zero(addr1, addr2);
		}
		else if (cursor->first[1] == 's') {
			std::string temp;
			size_t val = 0;
			size_t addr = 0;
			bool addr1_found = false;
			for (int i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					if (!addr1_found) {
						std::reverse(temp.begin(), temp.end());
						val = atoi(temp.c_str());
						addr1_found = true;
						temp.clear();
					}
					else {
						std::reverse(temp.begin(), temp.end());
						addr = atoi(temp.c_str());
						break;
					}
				}
				temp += cursor->first[i];
			}
			this->set(addr, val);
		}
		else if (cursor->first[3] == 'p') {
			std::string temp;
			size_t start_addr1 = 0;
			size_t start_addr2 = 0;
			size_t num_addr = 0;
			bool addr1_found = false;
			bool num_found = false;
			for (int i = cursor->first.size() - 1; i != -1; i--)
			{
				if (cursor->first[i] == ' ') {
					if (!num_found) {
						std::reverse(temp.begin(), temp.end());
						num_addr = atoi(temp.c_str());
						num_found = true;
						temp.clear();
					}
					else if (!addr1_found) {
						std::reverse(temp.begin(), temp.end());
						start_addr1 = atoi(temp.c_str());
						addr1_found = true;
						temp.clear();
					}
					else {
						std::reverse(temp.begin(), temp.end());
						start_addr2 = atoi(temp.c_str());
						break;
					}
				}
				temp += cursor->first[i];
			}
			this->copy(start_addr2, start_addr1, num_addr);
		}
		else if (cursor->first[1] == 'a') {
			std::string temp;
			int i = 0;
			for (i; i < cursor->first.size(); i++)
			{
				if (cursor->first[i] == ' ') {
					break;
				}
			}
			temp = cursor->first.substr(i + 1, cursor->first.size() - 1);
			this->loaded_program.erase(cursor);
			std::ifstream file(temp);
			this->add(file);
			file.close();
			cursor = this->loaded_program.begin();
			cursor_end = this->loaded_program.end();
		}
		else if (cursor->first[1] == 'q') {
			std::string temp;
			int i = 0;
			for (i; i  < cursor->first.size(); i++)
			{
				if (cursor->first[i] == ' ') {
					break;
				}
			}
			temp = cursor->first.substr(i + 1, cursor->first.size() - 1);
			this->loaded_program.erase(cursor);
			if (temp[0] != '/') {
				this->loaded_program.push_back(std::pair<std::string, int>(temp, this->last_instruct_num++));
			}
			else {
				this->loaded_program.push_back(std::pair<std::string, int>(temp, -1));
			}
			cursor = this->loaded_program.begin();
			cursor_end = this->loaded_program.end();
		}
		else if (cursor->first[1] == 'r') {
			this->loaded_program.erase(cursor);
			cursor = this->loaded_program.begin();
			cursor_end = this->loaded_program.end();
		}
	}
}

void Machine::code() const
{
	for (auto reg : this->loaded_program)
	{
		if (reg.second == -1) {
			std::cout << reg.first << '\n';
			continue;
		}
		std::cout << reg.second << ": " << reg.first << '\n';
	}
}
