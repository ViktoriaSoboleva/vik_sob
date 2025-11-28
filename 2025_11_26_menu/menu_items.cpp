#include "menu_items.hpp"
#include "menu_func.hpp"

#include <cstddef>

const svr::MenuItem svr::GO_BACK =
{
	"0 - Выйти в предыдущее меню", svr::go_back, &svr::PUSHKIN
};
const svr::MenuItem svr::DUBROVSKY =
{
	"1 - Дубровский", svr::dubrovsky, &svr::PUSHKIN
};
const svr::MenuItem svr::ONEGIN =
{
	"2 - Евгений Онегин", svr::onegin, &svr::PUSHKIN
};
const svr::MenuItem svr::WINTER_EVENING =
{
	"3 - Зимний вечер", svr::winter_evening, &svr::PUSHKIN
};

namespace
{
	const svr::MenuItem* const pushkin_children[] =
	{
		&svr::GO_BACK,
		&svr::DUBROVSKY,
		&svr::ONEGIN,
		&svr::WINTER_EVENING
	};
	const int pushkin_children_amount = sizeof(pushkin_children) / sizeof(pushkin_children[0]);
}

const svr::MenuItem svr::GO_BACK_TO_MENU =
{
	"0 - Выйти в главное меню", svr::go_back, &svr::READ
};
const svr::MenuItem svr::PUSHKIN =
{
	"1 - Читать Пушкина", svr::pushkin, &svr::READ, pushkin_children, pushkin_children_amount
};
const svr::MenuItem svr::LERMONTOV =
{
	"2 - Читать Лермонтова", svr::go_back, &svr::READ
};
const svr::MenuItem svr::KRYLOV =
{
	"3 - Читать Крылова", svr::go_back, &svr::READ
};

namespace
{
	const svr::MenuItem* const read_children[] =
	{
		&svr::GO_BACK_TO_MENU,
		&svr::PUSHKIN,
		&svr::LERMONTOV,
		&svr::KRYLOV
	};
	const int read_children_amount = sizeof(read_children) / sizeof(read_children[0]);
}

const svr::MenuItem svr::READ =
{
	"1 - Русские писатели", svr::show_menu, &svr::MAIN, read_children, read_children_amount
};
const svr::MenuItem svr::EXIT =
{
	"0 - Завершить чтение", svr::exit, &svr::MAIN
};

namespace
{
	const svr::MenuItem* const main_children[] =
	{
		&svr::EXIT,
		&svr::READ
	};
	const int main_children_amount = sizeof(main_children) / sizeof(main_children[0]);
}
const svr::MenuItem svr::MAIN =
{
	nullptr, svr::show_menu, nullptr, main_children, main_children_amount
};
