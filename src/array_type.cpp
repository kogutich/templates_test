#pragma once

#include <cstddef>
#include <type_traits>

namespace mp
{
	template <size_t ...N>
	struct reverse
	{
	private:
		template <typename C, size_t ...Vs>
		struct impl
		{
			using type = C;
		};

		template <size_t ...W, size_t V, size_t ...Vs>
		struct impl<reverse<W...>, V, Vs...>
		{
			using type = typename impl<reverse<V, W...>, Vs...>::type;
		};

	public:
		using type = typename impl<reverse<>, N...>::type;
	};

	template <typename T, size_t ...N>
	struct array_type
	{
		static_assert( sizeof...( N ) > 0, "empty array" );

	private:
		template <typename Result, typename ...>
		struct impl
		{
			using type = Result;
		};

		template <typename Result, size_t M, size_t ...Ms>
		struct impl<Result, reverse<M, Ms...>>
		{
			using type = typename impl<Result[ M ], reverse<Ms...>>::type;
		};

	public:
		using type = typename impl<T, typename reverse<N...>::type>::type;
	};

	template <typename T, size_t ...N>
	using array_type_t = typename array_type<T, N...>::type;
}

// usage
static_assert( std::is_same_v<mp::reverse<>::type, mp::reverse<>> );
static_assert( std::is_same_v<mp::reverse<1>::type, mp::reverse<1>> );
static_assert( std::is_same_v<mp::reverse<1, 2>::type, mp::reverse<2, 1>> );
static_assert( std::is_same_v<mp::reverse<1, 2, 3>::type, mp::reverse<3, 2, 1>> );

static_assert( std::is_same_v<mp::array_type_t<int, 2>, int[ 2 ]> );
static_assert( std::is_same_v<mp::array_type_t<int, 2, 3>, int[ 2 ][ 3 ]> );
static_assert( std::is_same_v<mp::array_type_t<int, 2, 3, 4>, int[ 2 ][ 3 ][ 4 ]> );

int main()
{
}