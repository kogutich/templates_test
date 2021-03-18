#pragma once

#include <type_traits>

namespace mp
{
	template <bool B, typename T = void>
	struct enable_if
	{
		using type = T;
	};

	template <typename T>
	struct enable_if<false, T>
	{
	};

	template <bool B, typename T = void>
	using enable_if_t = typename enable_if<B, T>::type;

	template <bool B, typename T = void>
	struct disable_if
	{
	};

	template <typename T>
	struct disable_if<false, T>
	{
		using type = T;
	};

	template <bool B, typename T = void>
	using disable_if_t = typename disable_if<B, T>::type;
}

// usage
template <typename T, mp::disable_if_t<std::is_same_v<T, int>, bool> = false>
constexpr bool disable_if_example()
{
	return false; // not int
}

template <typename T, mp::disable_if_t<!std::is_same_v<T, int>, bool> = false>
constexpr bool disable_if_example()
{
	return true; // int
}

static_assert( disable_if_example<int>() );
static_assert( !disable_if_example<void>() );
static_assert( !disable_if_example<bool>() );

int main()
{
}