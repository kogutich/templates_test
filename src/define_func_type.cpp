#pragma once

namespace mp
{
	typedef double ( *func_t )( double );

	// 1 ---------------------------------------------------
	double f( double x )
	{
		return x + 1;
	}

	template <typename T>
	T g( T x )
	{
		return x + 1;
	}

	func_t f1 = f;
	func_t f2 = g<double>; // same like ordinary func

	// 2 ---------------------------------------------------
	template <typename X>
	struct outer
	{
		template <typename T>
		static T g( T x )
		{
			return x + 1;
		}
	};

	template <typename X>
	double h()
	{
		//func_t f = outer<X>::g<double>;        // error
		func_t f = outer<X>::template g<double>; // correct
		return f( 1 );
	}
}

int main()
{
}
