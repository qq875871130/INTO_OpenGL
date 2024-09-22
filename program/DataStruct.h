#pragma once
template <typename T>
class Vec2
{
public:
	T X, Y;

	Vec2(T x, T y) : X(x), Y(y)
	{
	}
};

template <typename T>
class Vec3
{
public:
	T X, Y, Z;

	Vec3(T x, T y, T z) : X(x), Y(y), Z(z)
	{
	}

	Vec3(Vec2<T> v2, T z) : X(v2.X), Y(v2.Y), Z(z)
	{
	}
};

template <typename T>
class Vec4 {
public:
	T X, Y, Z, W;

	Vec4(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w)
	{
	}

	Vec4(Vec3<T> v3, T w) : X(v3.X), Y(v3.Y), Z(v3.Z), W(w)
	{
	}
};
