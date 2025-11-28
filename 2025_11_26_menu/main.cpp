#include <iostream>

#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_func.hpp"

int main()
{
	
	// Способ 1: оператор sizeof
    std::cout << "Размер структуры MenuItem: " << sizeof(svr::MenuItem) << " байт" << std::endl;
    
    // Способ 2: можно посчитать размер конкретного объекта
    std::cout << "Размер объекта MAIN: " << sizeof(svr::MAIN) << " байт" << std::endl;
    
    // Способ 3: посмотреть размеры отдельных полей
    std::cout << "sizeof(const char*): " << sizeof(const char*) << " байт" << std::endl;
    std::cout << "sizeof(function pointer): " << sizeof(const svr::MenuItem* (*)(const svr::MenuItem*)) << " байт" << std::endl;
    std::cout << "sizeof(MenuItem*): " << sizeof(const svr::MenuItem*) << " байт" << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << " байт" << std::endl;

	const svr::MenuItem* current = &svr::MAIN;
	do
	{
		current = current->func(current);
	}
	while (true);
	
	return 0;
}