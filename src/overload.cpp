#pragma once

#include <variant>
#include <string>
#include <iostream>

namespace mp
{
	template <typename ...Ts>
	struct overload : Ts...
	{
		using Ts::operator()...;
	};

	template <typename... Ts>
	overload( Ts ... )->overload<Ts...>;
}

int main()
{
	std::variant<int, bool, std::string> v{ 10 };

	std::visit(
		mp::overload{
			[]( int i ) { std::cout << "int: " << i; },
			[] ( bool i ) { std::cout << "bool: " << i; },
			[] ( const std::string& i ) { std::cout << "string: " << i; }
		},
		v
	);
}
