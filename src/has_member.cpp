#pragma once

#include <utility>
#include <vector>
#include <type_traits>

namespace mp
{
	template <typename, typename = void>
	struct has_type_member : std::false_type
	{
	};

	template <typename T>
	struct has_type_member<T, std::void_t<typename T::type>> : std::true_type
	{
	};

	template <typename T, typename = void>
	struct is_iterable : std::false_type
	{
	};

	template <typename T>
	struct is_iterable<T, std::void_t<decltype( std::declval<T>().begin() ), decltype( std::declval<T>().end() )>> : std::true_type
	{
	};

	template <typename, typename = void>
	struct is_pre_incrementable : std::false_type
	{
	};

	template <typename T>
	struct is_pre_incrementable<T, std::void_t<decltype( ++std::declval<T&>() )>> : std::true_type
	{
	};
}

// usage
static_assert( !mp::has_type_member<int>::value );
static_assert( mp::has_type_member<std::decay<int>>::value );

static_assert( mp::is_iterable<std::vector<int>>::value );
static_assert( !mp::is_iterable<char>::value );

static_assert( mp::is_pre_incrementable<int>::value );
static_assert( !mp::is_pre_incrementable<void>::value );

int main()
{
}