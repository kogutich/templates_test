#pragma once

#include <type_traits>
#include <string>

namespace mp
{
	template <typename T>
	struct remove_cv
	{
		typedef T type;
	};

	template <typename T>
	struct remove_cv<const T>
	{
		typedef T type;
	};

	template <typename T>
	struct remove_cv<volatile T>
	{
		typedef T type;
	};

	template <typename T>
	struct remove_cv<const volatile T>
	{
		typedef T type;
	};

	template <typename T>
	struct is_pointer_helper : std::false_type
	{
	};

	template<typename T>
	struct is_pointer_helper<T*> : std::true_type
	{
	};

	template<typename T>
	struct is_pointer : is_pointer_helper<typename remove_cv<T>::type>
	{
	};

	template<typename T>
	inline constexpr bool is_pointer_v = is_pointer<T>::value;
}

// usage
static_assert( !mp::is_pointer_v<std::string> );
static_assert( mp::is_pointer_v<std::string*> );
static_assert( !mp::is_pointer_v<std::string&> );
static_assert( !mp::is_pointer_v<int> );
static_assert( mp::is_pointer_v<int*> );
static_assert( mp::is_pointer_v<int**> );
static_assert( !mp::is_pointer_v<int[ 10 ]> );
static_assert( !mp::is_pointer_v<std::nullptr_t> );
static_assert( mp::is_pointer_v<const int*> );
static_assert( mp::is_pointer_v<int* const> );
static_assert( mp::is_pointer_v<volatile int*> );

int main()
{
}