//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 
#include "Constants.h"
#include "Align16.h"


class Vect final : public Align16
{
public:

	friend class Matrix;

	// Big Four constructors
	Vect();
	Vect(const Vect &in);
	const Vect & operator=(const Vect &in);
	~Vect();

	// Specialized constructors
	Vect(const float _vx, const float _vy, const float _vz, const float _vw = 1.0f);

	// Bracket Accessors
	float& operator[](const enum x_enum);
	float& operator[](const enum y_enum);
	float& operator[](const enum z_enum);
	float& operator[](const enum w_enum);
	const float& operator[](const enum x_enum) const;
	const float& operator[](const enum y_enum) const;
	const float& operator[](const enum z_enum) const;
	const float& operator[](const enum w_enum) const;

	// Accessors
	float& x();
	float& y();
	float& z();
	float& w();
	const float& x() const;
	const float& y() const;
	const float& z() const;
	const float& w() const;

	// Set
	void set(const float _vx, const float _vy, const float _vz, const float _vw = 1.0f);
	void set(const Vect vect);

	// Unary operators
	Vect operator + () const;
	Vect operator - () const;

	// Add
	Vect operator + (const Vect& v) const;
	void operator +=(const Vect& v);

	// Subtract
	Vect operator - (const Vect& v) const;
	void operator -=(const Vect& v);

	// Scale
	friend Vect operator * (const float &scalar, const Vect &vect);
	friend Vect operator * (const Vect &vect, const float &scalar);
	void operator *= (const float &scalar);

	// Dot Product
	const float dot(const Vect v) const;

	// Cross Product
	const Vect cross(const Vect v) const;

	// Normalize Vector
	void norm();
	Vect getNorm() const;

	// Magnitude
	const float mag() const;
	const float magSqr() const;

	// Angle between two vectors
	const float getAngle(const Vect v) const;

	// Comparison
	bool isZero(const float epsilon = MATH_TOLERANCE) const;
	bool isEqual(const Vect& v, const float epsilon = MATH_TOLERANCE) const;


private:

	union
	{
		__m128	_m;

		// anonymous struct
		struct
		{
			float _vx;
			float _vy;
			float _vz;
			float _vw;
		};
	};

};

// Scale
inline Vect operator * (const float &scalar, const Vect &vect)
{
	Vect result;
	result._vx = vect._vx * scalar;
	result._vy = vect._vy * scalar;
	result._vz = vect._vz * scalar;
	result._vw = MATH_ONE;
	return result;
}

inline Vect operator * (const Vect &vect, const float &scalar)
{
	Vect result;
	result._vx = vect._vx * scalar;
	result._vy = vect._vy * scalar;
	result._vz = vect._vz * scalar;
	result._vw = MATH_ONE;
	return result;
}

#endif

// ---  End of File ---------------
