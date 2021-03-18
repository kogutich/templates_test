#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <array>

#include "args_printer.h"
#include "define_func_type.h"
#include "has_member.h"
#include "values_list.h"
#include "is_any_of.h"
#include "is_pointer.h"
#include "limit_types.h"
#include "other_copy_ctor.h"
#include "overload.h"
#include "partial_spec.h"
#include "enable_if.h"
#include "func_traits.h"
#include "apply.h"
#include "array_type.h"
#include "str.h"
#include "not.h"
#include "is_unique.h"
#include "unroll.h"

struct Printer
{
	static void body(size_t index)
	{
		std::cout << "print: " << index << '\n';
	}
};

int main()
{	
	std::cout << "\n\nstr\n";
	std::cout << T_STRING("hello")::value() << '\n';
	std::cout << T_STRING("hello world")::value() << '\n';

	std::cout << "\nunroll\n";
	mp::for_loop<10, Printer>::exec(35);
}
