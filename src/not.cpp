#pragma once

#include <type_traits>

namespace mp
{
	template <template <typename...> class F>
	struct not_f
	{
		template <typename ...Ts>
		using func = std::bool_constant<!F<Ts...>::value>;
	};
}

// usage
template <typename ...Ts>
using not_same = mp::not_f<std::is_same>::func<Ts...>;

static_assert( !not_same<int, int>::value );
static_assert( !mp::not_f<std::is_same>::func<int, int>::value );
static_assert( mp::not_f<std::is_same>::func<int, void>::value );

int main()
{
}