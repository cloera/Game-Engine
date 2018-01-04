//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

// SIMD includes
#include <xmmintrin.h>
#include <smmintrin.h> 
#include "Align16.h"

class Vect;

class Matrix final : public Align16
{
public:

	// Big Four Constructors
	Matrix();
	Matrix(const Matrix &in);
	const Matrix & operator=(const Matrix &in);
	~Matrix();

	// Specialized constructors
	Matrix(const  Vect v0, const Vect v1, const Vect v2, const Vect v3);
	Matrix(MatrixSpecialType type);
	Matrix(MatrixTransType, const float x, const float y, const float z);
	Matrix(MatrixTransType, const Vect& v);
	Matrix(MatrixScaleType, const float x, const float y, const float z);
	Matrix(MatrixScaleType, const Vect& v);
	Matrix(RotType type, const float angle);

	// Bracket Accessors
	float& operator[](const enum m0_enum);
	float& operator[](const enum m1_enum);
	float& operator[](const enum m2_enum);
	float& operator[](const enum m3_enum);
	float& operator[](const enum m4_enum);
	float& operator[](const enum m5_enum);
	float& operator[](const enum m6_enum);
	float& operator[](const enum m7_enum);
	float& operator[](const enum m8_enum);
	float& operator[](const enum m9_enum);
	float& operator[](const enum m10_enum);
	float& operator[](const enum m11_enum);
	float& operator[](const enum m12_enum);
	float& operator[](const enum m13_enum);
	float& operator[](const enum m14_enum);
	float& operator[](const enum m15_enum);
	const float& operator[](const enum m0_enum) const;
	const float& operator[](const enum m1_enum) const;
	const float& operator[](const enum m2_enum) const;
	const float& operator[](const enum m3_enum) const;
	const float& operator[](const enum m4_enum) const;
	const float& operator[](const enum m5_enum) const;
	const float& operator[](const enum m6_enum) const;
	const float& operator[](const enum m7_enum) const;
	const float& operator[](const enum m8_enum) const;
	const float& operator[](const enum m9_enum) const;
	const float& operator[](const enum m10_enum) const;
	const float& operator[](const enum m11_enum) const;
	const float& operator[](const enum m12_enum) const;
	const float& operator[](const enum m13_enum) const;
	const float& operator[](const enum m14_enum) const;
	const float& operator[](const enum m15_enum) const;

	// Accessors
	float& m0();
	float& m1();
	float& m2();
	float& m3();
	float& m4();
	float& m5();
	float& m6();
	float& m7();
	float& m8();
	float& m9();
	float& m10();
	float& m11();
	float& m12();
	float& m13();
	float& m14();
	float& m15();
	const float& m0() const;
	const float& m1() const;
	const float& m2() const;
	const float& m3() const;
	const float& m4() const;
	const float& m5() const;
	const float& m6() const;
	const float& m7() const;
	const float& m8() const;
	const float& m9() const;
	const float& m10() const;
	const float& m11() const;
	const float& m12() const;
	const float& m13() const;
	const float& m14() const;
	const float& m15() const;

	// Set
	void set(const Vect v0, const Vect v1, const Vect v2, const Vect v3);
	void set(MatrixSpecialType type);
	void set(MatrixTransType, const float x, const float y, const float z);
	void set(MatrixTransType, const Vect v);
	void set(MatrixScaleType, const float x, const float y, const float z);
	void set(MatrixScaleType, const Vect v);
	void set(RotType type, const float angle);
	void set(MatrixRowType type, const Vect v);
	void set(Vect &axis, float angle);

	// Get
	Vect get(MatrixRowType type) const;

	// Comparison
	bool isEqual(const Matrix& m, const float epsilon = MATH_TOLERANCE) const;
	bool isIdentity(const float epsilon = MATH_TOLERANCE) const;
	
	// Scale
	friend Matrix operator * (const float& scale, const Matrix& m);
	friend Matrix operator * (const Matrix& m, const float& scale);
	void operator *= (const float& scale);

	// Vector * Matrix (Row Major)
	friend Vect operator * (const Vect &v, const Matrix &m);
	friend void operator *= (Vect &v, const Matrix &m);

	// Matrix * Matrix 
	friend Matrix operator * (const Matrix& m1, const Matrix& m2);
	void operator *= (const Matrix& m1);

	// Matrix + Matrix
	friend Matrix operator + (const Matrix& m1, const Matrix& m2);
	void operator += (const Matrix& m);

	// Matrix - Matrix
	friend Matrix operator - (const Matrix& m1, const Matrix& m2);
	void operator -= (const Matrix& m);

	// Determinant
	const float det() const;

	// Transpose
	void T();
	const Matrix getT() const;

	// Inverse
	void inv();
	const Matrix getInv() const;
	const Matrix getAdj() const;

	// Unary operators
	Matrix operator + () const;
	Matrix operator - () const;
	

private:

	union
	{
		struct
		{
			Vect _v0;
			Vect _v1;
			Vect _v2;
			Vect _v3;
		};

		struct
		{
			float _m0;
			float _m1;
			float _m2;
			float _m3;
			float _m4;
			float _m5;
			float _m6;
			float _m7;
			float _m8;
			float _m9;
			float _m10;
			float _m11;
			float _m12;
			float _m13;
			float _m14;
			float _m15;
		};
	};
};

/////////////////////////
// Friend inline methods
////////////////////////

// Scale
inline Matrix operator*(const float & scale, const Matrix & m)
{
	return Matrix(Vect(m._m0*scale, m._m1*scale, m._m2*scale, m._m3*scale),
				  Vect(m._m4*scale, m._m5*scale, m._m6*scale, m._m7*scale),
				  Vect(m._m8*scale, m._m9*scale, m._m10*scale, m._m11*scale),
				  Vect(m._m12*scale, m._m13*scale, m._m14*scale, m._m15*scale));
}

inline Matrix operator*(const Matrix & m, const float & scale)
{
	return Matrix(Vect(m._m0*scale, m._m1*scale, m._m2*scale, m._m3*scale),
				  Vect(m._m4*scale, m._m5*scale, m._m6*scale, m._m7*scale),
				  Vect(m._m8*scale, m._m9*scale, m._m10*scale, m._m11*scale),
				  Vect(m._m12*scale, m._m13*scale, m._m14*scale, m._m15*scale));
}

// Vect * Matrix (Row Major)
inline Vect operator *(const Vect &v, const Matrix &m)
{
	return Vect(m._m0 * v.x() + m._m4 * v.y() + m._m8 * v.z() + m._m12 * v.w(),
				m._m1 * v.x() + m._m5 * v.y() + m._m9 * v.z() + m._m13 * v.w(),
				m._m2 * v.x() + m._m6 * v.y() + m._m10 * v.z() + m._m14 * v.w(),
				m._m3 * v.x() + m._m7 * v.y() + m._m11 * v.z() + m._m15 * v.w());
}

inline void operator *= (Vect &v, const Matrix &m)
{
	v.set(m._m0 * v.x() + m._m4 * v.y() + m._m8 * v.z() + m._m12 * v.w(),
		  m._m1 * v.x() + m._m5 * v.y() + m._m9 * v.z() + m._m13 * v.w(),
		  m._m2 * v.x() + m._m6 * v.y() + m._m10 * v.z() + m._m14 * v.w(),
		  m._m3 * v.x() + m._m7 * v.y() + m._m11 * v.z() + m._m15 * v.w());
}

// Matrix * Matrix
inline Matrix operator*(const Matrix & m1, const Matrix & m2)
{
	Matrix result;

	result._m0  = m1._m0*m2._m0 + m1._m1*m2._m4 + m1._m2*m2._m8 + m1._m3*m2._m12;
	result._m1  = m1._m0*m2._m1 + m1._m1*m2._m5 + m1._m2*m2._m9 + m1._m3*m2._m13;
	result._m2  = m1._m0*m2._m2 + m1._m1*m2._m6 + m1._m2*m2._m10 + m1._m3*m2._m14;
	result._m3  = m1._m0*m2._m3 + m1._m1*m2._m7 + m1._m2*m2._m11 + m1._m3*m2._m15;

	result._m4  = m1._m4*m2._m0 + m1._m5*m2._m4 + m1._m6*m2._m8 + m1._m7*m2._m12;
	result._m5  = m1._m4*m2._m1 + m1._m5*m2._m5 + m1._m6*m2._m9 + m1._m7*m2._m13;
	result._m6  = m1._m4*m2._m2 + m1._m5*m2._m6 + m1._m6*m2._m10 + m1._m7*m2._m14;
	result._m7  = m1._m4*m2._m3 + m1._m5*m2._m7 + m1._m6*m2._m11 + m1._m7*m2._m15;

	result._m8  = m1._m8*m2._m0 + m1._m9*m2._m4 + m1._m10*m2._m8 + m1._m11*m2._m12;
	result._m9  = m1._m8*m2._m1 + m1._m9*m2._m5 + m1._m10*m2._m9 + m1._m11*m2._m13;
	result._m10 = m1._m8*m2._m2 + m1._m9*m2._m6 + m1._m10*m2._m10 + m1._m11*m2._m14;
	result._m11 = m1._m8*m2._m3 + m1._m9*m2._m7 + m1._m10*m2._m11 + m1._m11*m2._m15;

	result._m12 = m1._m12*m2._m0 + m1._m13*m2._m4 + m1._m14*m2._m8 + m1._m15*m2._m12;
	result._m13 = m1._m12*m2._m1 + m1._m13*m2._m5 + m1._m14*m2._m9 + m1._m15*m2._m13;
	result._m14 = m1._m12*m2._m2 + m1._m13*m2._m6 + m1._m14*m2._m10 + m1._m15*m2._m14;
	result._m15 = m1._m12*m2._m3 + m1._m13*m2._m7 + m1._m14*m2._m11 + m1._m15*m2._m15;

	return result;
}

// Matrix + Matrix
inline Matrix operator+(const Matrix & m1, const Matrix & m2)
{
	return Matrix(Vect(m1._m0  + m2._m0,  m1._m1  + m2._m1,  m1._m2  + m2._m2,  m1._m3  + m2._m3),
				  Vect(m1._m4  + m2._m4,  m1._m5  + m2._m5,  m1._m6  + m2._m6,  m1._m7  + m2._m7),
				  Vect(m1._m8  + m2._m8,  m1._m9  + m2._m9,  m1._m10 + m2._m10, m1._m11 + m2._m11),
				  Vect(m1._m12 + m2._m12, m1._m13 + m2._m13, m1._m14 + m2._m14, m1._m15 + m2._m15));
}

// Matrix - Matrix
inline Matrix operator-(const Matrix & m1, const Matrix & m2)
{
	return Matrix(Vect(m1._m0  - m2._m0,  m1._m1  - m2._m1,  m1._m2  - m2._m2,  m1._m3  - m2._m3),
				  Vect(m1._m4  - m2._m4,  m1._m5  - m2._m5,  m1._m6  - m2._m6,  m1._m7  - m2._m7),
				  Vect(m1._m8  - m2._m8,  m1._m9  - m2._m9,  m1._m10 - m2._m10, m1._m11 - m2._m11),
				  Vect(m1._m12 - m2._m12, m1._m13 - m2._m13, m1._m14 - m2._m14, m1._m15 - m2._m15));
}

#endif

// ---  End of File ---------------
