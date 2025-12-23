#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const svr::MenuItem svr::GO_BACK =
{
	"0 - Вернуться к выбору предметов...", svr::go_back, &svr::ALGEBRA
};
const svr::MenuItem svr::GO_BACK_TO_MENU =
{
	"0 - Вернуться в главное меню...", svr::go_back, &svr::STUDY
};

const svr::MenuItem svr::SUM =
{
	"1 - Хочу научиться складывать!", svr::sum, &svr::ALGEBRA
};
const svr::MenuItem svr::SUBSTRACT =
{
	"2 - Хочу научиться вычитать!", svr::substract, &svr::ALGEBRA
};
const svr::MenuItem svr::MULTIPLY =
{
	"3 - Хочу научиться умножать!", svr::multiply, &svr::ALGEBRA
};
const svr::MenuItem svr::DIVIDE =
{
	"4 - Хочу научиться делить!", svr::divide, &svr::ALGEBRA
};

namespace
{
	const svr::MenuItem* const algebra_children[] = 
	{
		&svr::GO_BACK,
		&svr::SUM,
		&svr::SUBSTRACT,
		&svr::MULTIPLY,
		&svr::DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
}

const svr::MenuItem svr::DIFF_EQ =
{
	"1 - Хочу изучить дифференциальное исчисление!", svr::diff_eq, &svr::MATH_ANALYSIS
};
const svr::MenuItem svr::INTEGRAL =
{
	"2 - Хочу изучить интегральное исчисление!", svr::integral, &svr::MATH_ANALYSIS
};

namespace
{
	const svr::MenuItem* const math_analysis_children[] = 
	{
		&svr::GO_BACK,
		&svr::DIFF_EQ,
		&svr::INTEGRAL
	};
	const int math_analysis_size = sizeof(math_analysis_children) / sizeof(math_analysis_children[0]);
}

const svr::MenuItem svr::ALGEBRA =
{
	"1 - Хочу изучать алгебру!", svr::show_menu, &svr::STUDY, algebra_children, algebra_size
};
const svr::MenuItem svr::MATH_ANALYSIS =
{
	"2 - Хочу изучать математический анализ!", svr::show_menu, &svr::STUDY, math_analysis_children, math_analysis_size
};

namespace
{
	const svr::MenuItem* const study_children[] =
	{
		&svr::GO_BACK_TO_MENU,
		&svr::ALGEBRA,
		&svr::MATH_ANALYSIS
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const svr::MenuItem svr::STUDY =
{
	"1 - Хочу учиться математике!", svr::show_menu, &svr::MAIN, study_children, study_size
};
const svr::MenuItem svr::EXIT =
{
	"0 - Я лучше пойду полежу...", svr::exit, &svr::MAIN
};

namespace
{
	const svr::MenuItem* const main_children[] =
	{
		&svr::EXIT,
		&svr::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const svr::MenuItem svr::MAIN =
{
	nullptr, svr::show_menu, nullptr, main_children, main_size
};