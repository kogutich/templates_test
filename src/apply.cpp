#include <cstddef>
#include <type_traits>

namespace mp
{
	template <template <typename> class F, std::size_t N, typename X>
	struct apply_helper
	{
		using type = typename apply_helper<F, N - 1, typename F<X>::type>::type;
	};

	template <template <typename> class F, typename X>
	struct apply_helper<F, 0, X>
	{
		using type = X;
	};

	template <template <typename> class F, std::size_t N>
	struct apply
	{
		template <typename X>
		using to = typename apply_helper<F, N, X>::type;
	};
}

// usage
static_assert( std::is_same_v<mp::apply<std::add_pointer, 0>::to<int>, int> );
static_assert( std::is_same_v<mp::apply<std::add_pointer, 1>::to<int>, int*> );
static_assert( std::is_same_v<mp::apply<std::add_pointer, 2>::to<int>, int**> );
static_assert( std::is_same_v<mp::apply<std::add_pointer, 3>::to<int>, int***> );

int main()
{
}