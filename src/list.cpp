#pragma once

namespace mp
{

	template <auto V, typename T>
	struct list
	{
		inline static constexpr decltype( V ) value = V;
		using next = T;
	};

	struct nil
	{
	};
}

// usage
static_assert( mp::list<1, mp::list<2, mp::list<3, mp::nil>>>::value == 1 );
static_assert( mp::list<1, mp::list<2, mp::list<3, mp::nil>>>::next::value == 2 );
static_assert( mp::list<1, mp::list<2, mp::list<3, mp::nil>>>::next::next::value == 3 );

int main()
{
}