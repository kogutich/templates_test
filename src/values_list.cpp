#pragma once

#include <cstddef>
#include <type_traits>
#include <array>
#include <utility>

namespace mp
{
	template <typename T, typename U>
	constexpr bool is_current_type( const U& )
	{
		return std::is_same_v<T, std::remove_cv_t<std::remove_reference_t<U>>>;
	}

	template <typename T, auto ...Ts>
	constexpr size_t count_of_type()
	{
		size_t count = 0;

		auto fn = [&count] ( auto&& i ) {
			if ( is_current_type<T>( i ) )
			{
				count++;
			}
		};

		( fn( Ts ), ... );

		return count;
	}

	template <auto ...Ts>
	struct values_list
	{
	public:
		template <typename T>
		constexpr static auto get()
		{
			constexpr size_t N = count_of_type<T, Ts...>();
			std::array<T, N> arr{};

			auto fn = [ i = 0, &arr ]( auto&& elem ) constexpr mutable {
				if ( is_current_type<T>( std::forward<decltype( elem )>( elem ) ) )
				{
					arr[ i++ ] = elem;
				}
			};

			( fn( Ts ), ... );

			return arr;
		}
	};
}

// usage
using vl = mp::values_list<1, 7, true, 'b', false, 8>;

constexpr std::array<int, 3> int_values = vl::get<int>();
static_assert( int_values[ 0 ] == 1 );
static_assert( int_values[ 1 ] == 7 );
static_assert( int_values[ 2 ] == 8 );

constexpr std::array<bool, 2> bool_values = vl::get<bool>();
static_assert( bool_values[ 0 ] == true );
static_assert( bool_values[ 1 ] == false );

constexpr std::array<char, 1> char_values = vl::get<char>();
static_assert( char_values[ 0 ] == 'b' );

int main()
{
}