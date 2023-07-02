#pragma once
template <typename T>
class vec2
{
public:
	T x, y;
	vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}
};

template <typename T>
class vec3
{
public:
	T x, y, z;
	vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vec3(vec2 v2, T z) {
		this->x = v2->x;
		this->y = v2->y;
		this->z = z;
	}
};

template <typename T>
class vec4 {
public:
	T x, y, z, w;
	vec4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	vec4(vec3 v3, T w) {
		this->x = v3->x;
		this->y = v3->y;
		this->z = v3->z;
		this->w = w;
	}
};
