#pragma once

#include <iostream>

namespace mp
{
	namespace detail
	{
		template <size_t N, typename B>
		struct unroll
		{
			static constexpr void iteration( size_t i )
			{
				B::body( i );
				unroll<N - 1, B>::iteration( i + 1 );
			}
		};

		template <typename B>
		struct unroll<0, B>
		{
			static constexpr void iteration( size_t )
			{
			}
		};
	}

	template <size_t N, typename B>
	struct for_loop
	{
		static constexpr void exec( size_t m )
		{
			for ( size_t i = 0; i < m / N; i++ )
			{
				detail::unroll<N, B>::iteration( i * N );
			}

			for ( size_t i = 0; i < m % N; i++ )
			{
				B::body( m / N * N + i );
			}
		}
	};
}

// usage
struct Printer
{
	static void body( size_t index )
	{
		std::cout << "print: " << index << '\n';
	}
};

int main()
{
	mp::for_loop<10, Printer>::exec( 35 );
}