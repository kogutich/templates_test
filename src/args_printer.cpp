#pragma once

#include <iostream>
#include <typeinfo>
#include <type_traits>

namespace mp
{
	// 1 version
	template <size_t Index = 0>
	constexpr void print_args( std::ostream& )
	{
	}

	template <size_t Index = 1, typename T, typename ...Args>
	constexpr void print_args( std::ostream& out, T&& arg, Args&& ...args )
	{
		out << Index << ") " << typeid( std::decay_t<T> ).name() << ": " << std::boolalpha << arg << '\n';
		print_args<Index + 1, Args...>( out, std::forward<Args>( args )... );
	}

	// 2 version
	template <typename ...Args>
	constexpr void print_args2( std::ostream& out, Args&& ...args )
	{
		auto fn = [ &out, index = 1 ]( auto&& arg ) mutable
		{
			out << index++ << ") " << typeid( std::decay_t<decltype( arg )> ).name() << ": " << std::boolalpha << arg <<
				'\n';
		};

		( fn( std::forward<Args>( args ) ), ... );
	}
}

// usage
int main()
{
	const int x = 10;
	mp::print_args( std::cout, 1, true, "3", &x );

	std::cout << '\n';
	mp::print_args2( std::cout, 1, true, "3", &x );
}
