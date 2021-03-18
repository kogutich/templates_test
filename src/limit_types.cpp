#pragma once

namespace mp
{
	template <typename T>
	struct only_for_int; // note: no body

	template<>
	struct only_for_int<int>
	{
		int value;
	};
}

int main()
{
}