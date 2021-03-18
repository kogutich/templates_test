#pragma once

#include <cstddef>
#include <tuple>

namespace mp
{
	template <typename F>
	struct func_traits;

	template <typename R, typename ...Args>
	struct func_traits<R( * )( Args... )>
	{
		using function_type = R( * )( Args... );
		using result_type = R;

		template <std::size_t Index>
		using argument_type = typename std::tuple_element<Index, std::tuple<Args...>>::type;
	};
}

// usage
void unary_f( int )
{
}

int binary_f( double, char )
{
	return 0;
}

using unary_f_t = decltype( &unary_f );
static_assert( std::is_same_v<mp::func_traits<unary_f_t>::result_type, void> );
static_assert( std::is_same_v<mp::func_traits<unary_f_t>::argument_type<0>, int> );
static_assert( std::is_same_v<mp::func_traits<unary_f_t>::function_type, void( * )( int )> );

using binary_f_t = decltype( &binary_f );
static_assert( std::is_same_v<mp::func_traits<binary_f_t>::result_type, int> );
static_assert( std::is_same_v<mp::func_traits<binary_f_t>::argument_type<0>, double> );
static_assert( std::is_same_v<mp::func_traits<binary_f_t>::argument_type<1>, char> );
static_assert( std::is_same_v<mp::func_traits<binary_f_t>::function_type, int( * )( double, char )> );

int main()
{
}