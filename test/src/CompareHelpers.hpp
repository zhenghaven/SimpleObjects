// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

template<typename _T>
struct CompareTestHelpers
{

	static bool Eq(const _T& a, const _T& b)
	{
		return a == b;
	};
	static bool Neq(const _T& a, const _T& b)
	{
		return a != b;
	};
	static bool Lt(const _T& a, const _T& b)
	{
		return a < b;
	};
	static bool Gt(const _T& a, const _T& b)
	{
		return a > b;
	};
	static bool Ge(const _T& a, const _T& b)
	{
		return a >= b;
	};
	static bool Le(const _T& a, const _T& b)
	{
		return a <= b;
	};

}; // struct CompareHelpers

