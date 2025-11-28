#include <cstdlib>
#include <iostream>

#include "menu_func.hpp"
namespace
{
	const svr::MenuItem* menu(const svr::MenuItem* current)
	{
		for (int i = 1; i < current->children_amount; i++)
		{	
			std::cout << current->children[i]->name << std::endl;
		}
		
		std::cout << current->children[0]->name << std::endl;
		std::cout << "Читаем >> ";
		
		int user_input;
		std::cin >> user_input;
		std::cout << std::endl;
		
		return current->children[user_input];
	}
}
const svr::MenuItem* svr::exit(const MenuItem* current)
{
	std::exit(0);
}

const svr::MenuItem* svr::go_back(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent->parent;
}
const svr::MenuItem* svr::pushkin(const MenuItem* current)
{
	std::cout << "Что читаем?" << std::endl;
	return menu(current);
}
const svr::MenuItem* svr::show_menu(const MenuItem* current)
{
	std::cout << "Кого читаем? " << std::endl;
	return menu(current);
}

const svr::MenuItem* svr::dubrovsky(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::onegin(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::winter_evening(const MenuItem* current)
{
	std::cout << current->name << std::endl << std::endl;
	return current->parent;
}