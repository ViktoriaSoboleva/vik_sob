#include <cstdlib>
#include <iostream>

#include "menu_functions.hpp"

const svr::MenuItem* svr::show_menu(const MenuItem* current)
{
	std::cout << "Обучайка привествует тебя!" << std::endl;
	for (int i = 1; i < current->children_count; i++)
	{	
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка >> ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const svr::MenuItem* svr::exit(const MenuItem* current)
{
	std::exit(0);
}


const svr::MenuItem* svr::sum(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::substract(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::multiply(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::divide(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::diff_eq(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const svr::MenuItem* svr::integral(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const svr::MenuItem* svr::go_back(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;
}
