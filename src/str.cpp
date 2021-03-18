#pragma once

#include <string>
#include <utility>
#include <type_traits>
#include <iostream>

namespace mp
{
	namespace detail
	{
		template <size_t Len, typename T>
		constexpr T string_at( const T( &s )[ Len ], int n )
		{
			static_assert( Len <= 50 + 2, "String literal is too long." );
			return n >= Len - 1 ? T() : s[ n ];
		}

		template <typename Seq, char ...C>
		struct filter_zeros
		{
			using type = Seq;
		};

		template <template <char ...> class SeqT, char ...Old, char New, char ...News>
		struct filter_zeros<SeqT<Old...>, New, News...>
		{
			using type = std::conditional_t<
				New == '\0',
				SeqT<Old...>,
				typename filter_zeros<SeqT<Old..., New>, News...>::type
			>;
		};
	}

	template <char ...C>
	struct string_wrapper
	{
		static std::string value()
		{
			static const std::string v{ C... };
			return v;
		}
	};
}

#define T_STRING(s) mp::detail::filter_zeros<mp::string_wrapper<>, T_STRING_ARG(s)>::type

#define T_STRING_ARG(s)    \
    mp::detail::string_at(s, 0),  \
    mp::detail::string_at(s, 1),  \
    mp::detail::string_at(s, 2),  \
    mp::detail::string_at(s, 3),  \
    mp::detail::string_at(s, 4),  \
    mp::detail::string_at(s, 5),  \
    mp::detail::string_at(s, 6),  \
    mp::detail::string_at(s, 7),  \
    mp::detail::string_at(s, 8),  \
    mp::detail::string_at(s, 9),  \
    mp::detail::string_at(s, 10), \
    mp::detail::string_at(s, 11), \
    mp::detail::string_at(s, 12), \
    mp::detail::string_at(s, 13), \
    mp::detail::string_at(s, 14), \
    mp::detail::string_at(s, 15), \
    mp::detail::string_at(s, 16), \
    mp::detail::string_at(s, 17), \
    mp::detail::string_at(s, 18), \
    mp::detail::string_at(s, 19), \
    mp::detail::string_at(s, 20), \
    mp::detail::string_at(s, 21), \
    mp::detail::string_at(s, 22), \
    mp::detail::string_at(s, 23), \
    mp::detail::string_at(s, 24), \
    mp::detail::string_at(s, 25), \
    mp::detail::string_at(s, 26), \
    mp::detail::string_at(s, 27), \
    mp::detail::string_at(s, 28), \
    mp::detail::string_at(s, 29), \
    mp::detail::string_at(s, 30), \
    mp::detail::string_at(s, 31), \
    mp::detail::string_at(s, 32), \
    mp::detail::string_at(s, 33), \
    mp::detail::string_at(s, 34), \
    mp::detail::string_at(s, 35), \
    mp::detail::string_at(s, 36), \
    mp::detail::string_at(s, 37), \
    mp::detail::string_at(s, 38), \
    mp::detail::string_at(s, 39), \
    mp::detail::string_at(s, 40), \
    mp::detail::string_at(s, 41), \
    mp::detail::string_at(s, 42), \
    mp::detail::string_at(s, 43), \
    mp::detail::string_at(s, 44), \
    mp::detail::string_at(s, 45), \
    mp::detail::string_at(s, 46), \
    mp::detail::string_at(s, 47), \
    mp::detail::string_at(s, 48), \
    mp::detail::string_at(s, 49), \
    mp::detail::string_at(s, 50)

// usage
static_assert( std::is_same_v<T_STRING( "" ), mp::string_wrapper<>> );
static_assert( std::is_same_v<T_STRING( "a" ), mp::string_wrapper<'a'>> );
static_assert( std::is_same_v<T_STRING( "ab" ), mp::string_wrapper<'a', 'b'>> );
static_assert( std::is_same_v<T_STRING( "abc" ), mp::string_wrapper<'a', 'b', 'c'>> );
static_assert( std::is_same_v<T_STRING( "abcd" ), mp::string_wrapper<'a', 'b', 'c', 'd'>> );
static_assert( std::is_same_v<T_STRING( "abcde" ), mp::string_wrapper<'a', 'b', 'c', 'd', 'e'>> );
static_assert( std::is_same_v<T_STRING( "hello world" ), mp::string_wrapper<'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'>> );

int main()
{
	std::cout << T_STRING( "hello" )::value() << '\n';
	std::cout << T_STRING( "hello world" )::value() << '\n';
}