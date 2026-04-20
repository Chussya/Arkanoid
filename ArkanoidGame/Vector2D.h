#pragma once

namespace ArkanoidGame
{
	template<class T>
	struct Vector2D
	{
		T x = { 0 };
		T y = { 0 };
	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;

	template<class T>
	Vector2D<T> operator+(const Vector2D<T> &v1, const Vector2D<T> &v2)
	{
		return { v1.x + v2.x, v1.y + v2.y };
	}

	template<class T>
	Vector2D<T> operator-(const Vector2D<T> &v1, const Vector2D<T> &v2)
	{
		return { v1.x - v2.x, v1.y - v2.y };
	}

	template<class T>
	Vector2D<T> operator*(const Vector2D<T> &v1, const Vector2D<T> &v2)
	{
		return { v1.x * v2.x, v1.y * v2.y };
	}

	template<class T>
	Vector2D<T> operator/(const Vector2D<T> &v1, const Vector2D<T> &v2)
	{
		return { v1.x / v2.x, v1.y / v2.y };
	}

	template<class T>
	bool operator==(const Vector2D<T> &v1, const Vector2D<T> &v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}

	template<class To, class From>
	To convert(const From& from)
	{
		return { static_cast<decltype(To::x)>(from.x), static_cast<decltype(To::y)>(from.y) };
	}
}