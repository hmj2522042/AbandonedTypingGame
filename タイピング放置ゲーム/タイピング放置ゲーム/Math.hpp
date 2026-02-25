#pragma once
#include <cmath>
#include <algorithm>
#include <limits>
#include "DxLib.h"

namespace Math
{
	// 円周率
	static constexpr double Pi = 3.141592653589793;

	// デグリ（度数法）からラジアン（弧度法）に変換
	template <typename T>
	constexpr T Deg2Rad(const T& deg)
	{
		return static_cast<T>(deg * Pi / 180.0);
	}

	// ラジアン（弧度法）からデグリ（度数法）に変換
	template <typename T>
	constexpr T Rad2Deg(const T& rad)
	{
		return static_cast<T>(rad / Pi * 180.0);
	}

	// 値の丸め込み
	template <typename T>
	constexpr T Clamp(const T& value, const T& low, const T& high)
	{
		return (std::min)((std::max)(value, low), high);
	}

	// 値を0.0～1.0に丸め込む
	template <typename T>
	constexpr T Clamp01(const T& value)
	{
		return Clamp(value, static_cast<T>(0), static_cast<T>(1));
	}

	// 絶対値
	template <typename T>
	constexpr T Abs(const T& value)
	{
		return value < 0 ? -value : value;
	}

	// 2つの値が同じか
	template <typename T>
	constexpr bool Equal(const T& a, const T& b)
	{
		return Abs(a - b) <= std::numeric_limits<T>::epsilon();
	}

	// 値が0か
	template <typename T>
	constexpr bool Equal0(const T& value)
	{
		return Equal(value, static_cast<T>(0));
	}

	// 符号を返す
	template <typename T>
	constexpr int Sign(const T& value)
	{
		return (value > 0) - (value < 0);
	}
}
