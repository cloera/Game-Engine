//---------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <math.h>

#include "MathEngine.h"

Matrix::Matrix()
	: _v0(Vect(0.0f, 0.0f, 0.0f, 0.0f)),
	  _v1(Vect(0.0f, 0.0f, 0.0f, 0.0f)),
	  _v2(Vect(0.0f, 0.0f, 0.0f, 0.0f)),
	  _v3(Vect(0.0f, 0.0f, 0.0f, 0.0f))
{
}

Matrix::Matrix(const Matrix & in)
{
	this->_v0 = in._v0;
	this->_v1 = in._v1;
	this->_v2 = in._v2;
	this->_v3 = in._v3;
}

const Matrix & Matrix::operator=(const Matrix & in)
{
	if (this != &in)
	{
		this->_v0 = in._v0;
		this->_v1 = in._v1;
		this->_v2 = in._v2;
		this->_v3 = in._v3;
	}
	return *this;
}

Matrix::~Matrix()
{
	// Do nothing
}

Matrix::Matrix(Vect v0, Vect v1, Vect v2, Vect v3)
	: _v0(v0), _v1(v1), _v2(v2), _v3(v3)
{
}

Matrix::Matrix(MatrixSpecialType type)
{
	this->set(type);
}

Matrix::Matrix(MatrixTransType type, float x, float y, float z)
{
	this->set(type, x, y, z);
}

Matrix::Matrix(MatrixTransType type, const Vect& v)
{
	this->set(type, v);
}

Matrix::Matrix(MatrixScaleType type, const float x, const float y, const float z)
{
	this->set(type, x, y, z);
}

Matrix::Matrix(MatrixScaleType type, const Vect& v)
{
	this->set(type, v);
}

Matrix::Matrix(RotType type, const float angle)
{
	this->set(type, angle);
}

float & Matrix::operator[](const enum m0_enum)
{
	return this->_m0;
}

float & Matrix::operator[](const enum m1_enum)
{
	return this->_m1;
}

float & Matrix::operator[](const enum m2_enum)
{
	return this->_m2;
}

float & Matrix::operator[](const enum m3_enum)
{
	return this->_m3;
}

float & Matrix::operator[](const enum m4_enum)
{
	return this->_m4;
}

float & Matrix::operator[](const enum m5_enum)
{
	return this->_m5;
}

float & Matrix::operator[](const enum m6_enum)
{
	return this->_m6;
}

float & Matrix::operator[](const enum m7_enum)
{
	return this->_m7;
}

float & Matrix::operator[](const enum m8_enum)
{
	return this->_m8;
}

float & Matrix::operator[](const enum m9_enum)
{
	return this->_m9;
}

float & Matrix::operator[](const enum m10_enum)
{
	return this->_m10;
}

float & Matrix::operator[](const enum m11_enum)
{
	return this->_m11;
}

float & Matrix::operator[](const enum m12_enum)
{
	return this->_m12;
}

float & Matrix::operator[](const enum m13_enum)
{
	return this->_m13;
}

float & Matrix::operator[](const enum m14_enum)
{
	return this->_m14;
}

float & Matrix::operator[](const enum m15_enum)
{
	return this->_m15;
}

const float& Matrix::operator[](const enum m0_enum) const
{
	return this->_m0;
}

const float& Matrix::operator[](const enum m1_enum) const
{
	return this->_m1;
}

const float& Matrix::operator[](const enum m2_enum) const
{
	return this->_m2;
}

const float& Matrix::operator[](const enum m3_enum) const
{
	return this->_m3;
}

const float& Matrix::operator[](const enum m4_enum) const
{
	return this->_m4;
}

const float& Matrix::operator[](const enum m5_enum) const
{
	return this->_m5;
}

const float& Matrix::operator[](const enum m6_enum) const
{
	return this->_m6;
}

const float& Matrix::operator[](const enum m7_enum) const
{
	return this->_m7;
}

const float& Matrix::operator[](const enum m8_enum) const
{
	return this->_m8;
}

const float& Matrix::operator[](const enum m9_enum) const
{
	return this->_m9;
}

const float& Matrix::operator[](const enum m10_enum) const
{
	return this->_m10;
}

const float& Matrix::operator[](const enum m11_enum) const
{
	return this->_m11;
}

const float& Matrix::operator[](const enum m12_enum) const
{
	return this->_m12;
}

const float& Matrix::operator[](const enum m13_enum) const
{
	return this->_m13;
}

const float& Matrix::operator[](const enum m14_enum) const
{
	return this->_m14;
}

const float& Matrix::operator[](const enum m15_enum) const
{
	return this->_m15;
}

float & Matrix::m0()
{
	return this->_m0;
}

float & Matrix::m1()
{
	return this->_m1;
}

float & Matrix::m2()
{
	return this->_m2;
}

float & Matrix::m3()
{
	return this->_m3;
}

float & Matrix::m4()
{
	return this->_m4;
}

float & Matrix::m5()
{
	return this->_m5;
}

float & Matrix::m6()
{
	return this->_m6;
}

float & Matrix::m7()
{
	return this->_m7;
}

float & Matrix::m8()
{
	return this->_m8;
}

float & Matrix::m9()
{
	return this->_m9;
}

float & Matrix::m10()
{
	return this->_m10;
}

float & Matrix::m11()
{
	return this->_m11;
}

float & Matrix::m12()
{
	return this->_m12;
}

float & Matrix::m13()
{
	return this->_m13;
}

float & Matrix::m14()
{
	return this->_m14;
}

float & Matrix::m15()
{
	return this->_m15;
}


const float & Matrix::m0() const
{
	return this->_m0;
}

const float & Matrix::m1() const
{
	return this->_m1;
}

const float & Matrix::m2() const
{
	return this->_m2;
}

const float & Matrix::m3() const
{
	return this->_m3;
}

const float & Matrix::m4() const
{
	return this->_m4;
}

const float & Matrix::m5() const
{
	return this->_m5;
}

const float & Matrix::m6() const
{
	return this->_m6;
}

const float & Matrix::m7() const
{
	return this->_m7;
}

const float & Matrix::m8() const
{
	return this->_m8;
}

const float & Matrix::m9() const
{
	return this->_m9;
}

const float & Matrix::m10() const
{
	return this->_m10;
}

const float & Matrix::m11() const
{
	return this->_m11;
}

const float & Matrix::m12() const
{
	return this->_m12;
}

const float & Matrix::m13() const
{
	return this->_m13;
}

const float & Matrix::m14() const
{
	return this->_m14;
}

const float & Matrix::m15() const
{
	return this->_m15;
}

// Set
void Matrix::set(const Vect v0, const Vect v1, const Vect v2, const Vect v3)
{
	this->_v0 = v0;
	this->_v1 = v1;
	this->_v2 = v2;
	this->_v3 = v3;
}

void Matrix::set(MatrixSpecialType type)
{
	switch (type)
	{
	case MatrixSpecialType::ZERO:
		this->_v0 = Vect(0.0f, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, 0.0f, 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, 0.0f, 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case MatrixSpecialType::IDENTITY:
		this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
}

void Matrix::set(MatrixTransType, const float x, const float y, const float z)
{
	this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
	this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
	this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
	this->_v3 = Vect(x, y, z);
}

void Matrix::set(MatrixTransType, const Vect v)
{
	this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
	this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
	this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
	this->_v3 = v;
}

void Matrix::set(MatrixScaleType, const float x, const float y, const float z)
{
	this->_v0 = Vect(x, 0.0f, 0.0f, 0.0f);
	this->_v1 = Vect(0.0f, y, 0.0f, 0.0f);
	this->_v2 = Vect(0.0f, 0.0f, z, 0.0f);
	this->_v3 = Vect(0.0f, 0.0f, 0.0f);
}

void Matrix::set(MatrixScaleType, const Vect v)
{
	this->_v0 = Vect(v.x(), 0.0f, 0.0f, 0.0f);
	this->_v1 = Vect(0.0f, v.y(), 0.0f, 0.0f);
	this->_v2 = Vect(0.0f, 0.0f, v.z(), 0.0f);
	this->_v3 = Vect(0.0f, 0.0f, 0.0f);
}

void Matrix::set(RotType type, const float angle)
{
	switch (type)
	{
	case RotType::ROT_X:
		this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, cosf(angle), sinf(angle), 0.0f);
		this->_v2 = Vect(0.0f, -sinf(angle), cosf(angle), 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case RotType::ROT_Y:
		this->_v0 = Vect(cosf(angle), 0.0f, -sinf(angle), 0.0f);
		this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
		this->_v2 = Vect(sinf(angle), 0.0f, cosf(angle), 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case RotType::ROT_Z:
		this->_v0 = Vect(cosf(angle), sinf(angle), 0.0f, 0.0f);
		this->_v1 = Vect(-sinf(angle), cosf(angle), 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
}

void Matrix::set(MatrixRowType type, const Vect v)
{
	switch (type)
	{
	case MatrixRowType::ROW_0:
		this->_v0 = v;
		break;
	case MatrixRowType::ROW_1:
		this->_v1 = v;
		break;
	case MatrixRowType::ROW_2:
		this->_v2 = v;
		break;
	case MatrixRowType::ROW_3:
		this->_v3 = v;
		break;
	}
}

void Matrix::set(Vect & axis, float angle)
{
	// angle
	// axis;
	const float angle_a = 0.5f * angle;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_a);
	sin_a = sinf(angle_a);

	Vect qV = axis.getNorm();

	qV *= sin_a;

	Vect Q;
	Q[x] = qV[x];
	Q[y] = qV[y];
	Q[z] = qV[z];
	Q[w] = cos_a;

	// TODO: Perhaps use transpose function
	// this function has been transposed
	float x2, y2, z2;
	float xx, xy, xz;
	float yy, yz, zz;
	float wx, wy, wz;

	// TODO: ADD test to make sure that quat is normalized

	x2 = Q[x] + Q[x];
	y2 = Q[y] + Q[y];
	z2 = Q[z] + Q[z];

	xx = Q[x] * x2;
	xy = Q[x] * y2;
	xz = Q[x] * z2;

	yy = Q[y] * y2;
	yz = Q[y] * z2;
	zz = Q[z] * z2;

	wx = Q[w] * x2;
	wy = Q[w] * y2;
	wz = Q[w] * z2;

	this->_m0 = 1.0f - (yy + zz);
	this->_m1 = xy + wz;
	this->_m2 = xz - wy;
	this->_m3 = 0.0f;

	this->_m4 = xy - wz;
	this->_m5 = 1.0f - (xx + zz);
	this->_m6 = yz + wx;
	this->_m7 = 0.0f;

	this->_m8 = xz + wy;
	this->_m9 = yz - wx;
	this->_m10 = 1.0f - (xx + yy);
	this->_m11 = 0.0f;

	this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
}

// Get
Vect Matrix::get(MatrixRowType type) const
{
	switch (type)
	{
	case MatrixRowType::ROW_0:
		return this->_v0;
	case MatrixRowType::ROW_1:
		return this->_v1;
	case MatrixRowType::ROW_2:
		return this->_v2;
	case MatrixRowType::ROW_3:
		return this->_v3;		
	}
	return Vect();
}

// Comparison
bool Matrix::isEqual(const Matrix& m, const float epsilon) const
{
	if (!this->_v0.isEqual(m._v0, epsilon))
	{
		return false;
	}
	if (!this->_v1.isEqual(m._v1, epsilon))
	{
		return false;
	}
	if (!this->_v2.isEqual(m._v2, epsilon))
	{
		return false;
	}
	if (!this->_v3.isEqual(m._v3, epsilon))
	{
		return false;
	}
	return true;
}

bool Matrix::isIdentity(const float epsilon) const
{
	Matrix identity(MatrixSpecialType::IDENTITY);

	return this->isEqual(identity, epsilon);
}

// Scale
void Matrix::operator*=(const float & scale)
{
	this->_m0 *= scale;   this->_m1 *= scale;   this->_m2 *= scale;   this->_m3 *= scale;
	this->_m4 *= scale;   this->_m5 *= scale;   this->_m6 *= scale;   this->_m7 *= scale;
	this->_m8 *= scale;   this->_m9 *= scale;   this->_m10 *= scale;  this->_m11 *= scale;
	this->_m12 *= scale;  this->_m13 *= scale;  this->_m14 *= scale;  this->_m15 *= scale;
}

// Matrix * Matrix
void Matrix::operator*=(const Matrix & m2)
{
	Matrix tmp(*this);

	this->_m0  = tmp._m0*m2._m0 + tmp._m1*m2._m4 + tmp._m2*m2._m8 + tmp._m3*m2._m12;
	this->_m1  = tmp._m0*m2._m1 + tmp._m1*m2._m5 + tmp._m2*m2._m9 + tmp._m3*m2._m13;
	this->_m2  = tmp._m0*m2._m2 + tmp._m1*m2._m6 + tmp._m2*m2._m10 + tmp._m3*m2._m14;
	this->_m3  = tmp._m0*m2._m3 + tmp._m1*m2._m7 + tmp._m2*m2._m11 + tmp._m3*m2._m15;
			   
	this->_m4  = tmp._m4*m2._m0 + tmp._m5*m2._m4 + tmp._m6*m2._m8 + tmp._m7*m2._m12;
	this->_m5  = tmp._m4*m2._m1 + tmp._m5*m2._m5 + tmp._m6*m2._m9 + tmp._m7*m2._m13;
	this->_m6  = tmp._m4*m2._m2 + tmp._m5*m2._m6 + tmp._m6*m2._m10 + tmp._m7*m2._m14;
	this->_m7  = tmp._m4*m2._m3 + tmp._m5*m2._m7 + tmp._m6*m2._m11 + tmp._m7*m2._m15;
			   
	this->_m8  = tmp._m8*m2._m0 + tmp._m9*m2._m4 + tmp._m10*m2._m8 + tmp._m11*m2._m12;
	this->_m9  = tmp._m8*m2._m1 + tmp._m9*m2._m5 + tmp._m10*m2._m9 + tmp._m11*m2._m13;
	this->_m10 = tmp._m8*m2._m2 + tmp._m9*m2._m6 + tmp._m10*m2._m10 + tmp._m11*m2._m14;
	this->_m11 = tmp._m8*m2._m3 + tmp._m9*m2._m7 + tmp._m10*m2._m11 + tmp._m11*m2._m15;

	this->_m12 = tmp._m12*m2._m0 + tmp._m13*m2._m4 + tmp._m14*m2._m8 + tmp._m15*m2._m12;
	this->_m13 = tmp._m12*m2._m1 + tmp._m13*m2._m5 + tmp._m14*m2._m9 + tmp._m15*m2._m13;
	this->_m14 = tmp._m12*m2._m2 + tmp._m13*m2._m6 + tmp._m14*m2._m10 + tmp._m15*m2._m14;
	this->_m15 = tmp._m12*m2._m3 + tmp._m13*m2._m7 + tmp._m14*m2._m11 + tmp._m15*m2._m15;
}

// Matrix += Matrix
void Matrix::operator+=(const Matrix & m)
{
	*this = Matrix(Vect(this->_m0  + m._m0,  this->_m1  + m._m1,  this->_m2  + m._m2,  this->_m3  + m._m3),
				   Vect(this->_m4  + m._m4,  this->_m5  + m._m5,  this->_m6  + m._m6,  this->_m7  + m._m7),
				   Vect(this->_m8  + m._m8,  this->_m9  + m._m9,  this->_m10 + m._m10, this->_m11 + m._m11),
				   Vect(this->_m12 + m._m12, this->_m13 + m._m13, this->_m14 + m._m14, this->_m15 + m._m15));
}

// Matrix -= Matrix
void Matrix::operator-=(const Matrix & m)
{
	*this = Matrix(Vect(this->_m0  - m._m0,  this->_m1  - m._m1,  this->_m2  - m._m2,  this->_m3  - m._m3),
				   Vect(this->_m4  - m._m4,  this->_m5  - m._m5,  this->_m6  - m._m6,  this->_m7  - m._m7),
				   Vect(this->_m8  - m._m8,  this->_m9  - m._m9,  this->_m10 - m._m10, this->_m11 - m._m11),
				   Vect(this->_m12 - m._m12, this->_m13 - m._m13, this->_m14 - m._m14, this->_m15 - m._m15));
}

// Determinant
const float Matrix::det() const
{
	return _m0 * ( _m5 * (_m10*_m15 - _m11*_m14) - _m6 * (_m9*_m15 - _m11*_m13) + _m7 * (_m9*_m14 - _m10*_m13) ) -
		   _m1 * ( _m4 * (_m10*_m15 - _m11*_m14) - _m6 * (_m8*_m15 - _m11*_m12) + _m7 * (_m8*_m14 - _m10*_m12) ) +
		   _m2 * ( _m4 * (_m9*_m15  - _m11*_m13) - _m5 * (_m8*_m15 - _m11*_m12) + _m7 * (_m8*_m13 - _m9 *_m12) ) -
		   _m3 * ( _m4 * (_m9*_m14  - _m10*_m13) - _m5 * (_m8*_m14 - _m10*_m12) + _m6 * (_m8*_m13 - _m9 *_m12) );

}

// Transpose
void Matrix::T()
{
	Matrix tmp(*this);

	this->_m1  = tmp._m4;  this->_m2 = tmp._m8;   this->_m3 = tmp._m12;
	this->_m4  = tmp._m1;  this->_m6 = tmp._m9;   this->_m7 = tmp._m13;
	this->_m8  = tmp._m2;  this->_m9 = tmp._m6;   this->_m11 = tmp._m14;
	this->_m12 = tmp._m3;  this->_m13 = tmp._m7;  this->_m14 = tmp._m11;
}

const Matrix Matrix::getT() const
{
	return Matrix(Vect(this->_m0, this->_m4, this->_m8, this->_m12),
				  Vect(this->_m1, this->_m5, this->_m9, this->_m13),
				  Vect(this->_m2, this->_m6, this->_m10, this->_m14),
				  Vect(this->_m3, this->_m7, this->_m11, this->_m15));
}

// Inverse
void Matrix::inv()
{
	// A^-1 = 1 / det(A) * Adj(A)
	*this = (1.0f / this->det()) * this->getAdj();
}

const Matrix Matrix::getInv() const
{
	// A^-1 = 1 / det(A) * Adj(A)
	Matrix result = (1.0f / this->det()) * this->getAdj();

	return result;
}

// Adjugate
const Matrix Matrix::getAdj() const
{
	Matrix result;

	// A whole chunk o' math
	result._m0 = _m6*_m11*_m13  - _m7*_m10*_m13 + _m7*_m9*_m14 - _m5*_m11*_m14 - _m6*_m9*_m15 + _m5*_m10*_m15;
	result._m1 = _m3*_m10*_m13  - _m2*_m11*_m13 - _m3*_m9*_m14 + _m1*_m11*_m14 + _m2*_m9*_m15 - _m1*_m10*_m15;
	result._m2 = _m2*_m7*_m13   - _m3*_m6*_m13  + _m3*_m5*_m14 - _m1*_m7*_m14  - _m2*_m5*_m15 + _m1*_m6*_m15;
	result._m3 = _m3*_m6*_m9    - _m2*_m7*_m9   - _m3*_m5*_m10 + _m1*_m7*_m10  + _m2*_m5*_m11 - _m1*_m6*_m11;
	result._m4 = _m7*_m10*_m12  - _m6*_m11*_m12 - _m7*_m8*_m14 + _m4*_m11*_m14 + _m6*_m8*_m15 - _m4*_m10*_m15;
	result._m5 = _m2*_m11*_m12  - _m3*_m10*_m12 + _m3*_m8*_m14 - _m0*_m11*_m14 - _m2*_m8*_m15 + _m0*_m10*_m15;
	result._m6 = _m3*_m6*_m12   - _m2*_m7*_m12  - _m3*_m4*_m14 + _m0*_m7*_m14  + _m2*_m4*_m15 - _m0*_m6*_m15;
	result._m7 = _m2*_m7*_m8    - _m3*_m6*_m8   + _m3*_m4*_m10 - _m0*_m7*_m10  - _m2*_m4*_m11 + _m0*_m6*_m11;
	result._m8 = _m5*_m11*_m12  - _m7*_m9*_m12  + _m7*_m8*_m13 - _m4*_m11*_m13 - _m5*_m8*_m15 + _m4*_m9*_m15;
	result._m9 = _m3*_m9*_m12   - _m1*_m11*_m12 - _m3*_m8*_m13 + _m0*_m11*_m13 + _m1*_m8*_m15 - _m0*_m9*_m15;
	result._m10 = _m1*_m7*_m12  - _m3*_m5*_m12  + _m3*_m4*_m13 - _m0*_m7*_m13  - _m1*_m4*_m15 + _m0*_m5*_m15;
	result._m11 = _m3*_m5*_m8   - _m1*_m7*_m8   - _m3*_m4*_m9  + _m0*_m7*_m9   + _m1*_m4*_m11 - _m0*_m5*_m11;
	result._m12 = _m6*_m9*_m12  - _m5*_m10*_m12 - _m6*_m8*_m13 + _m4*_m10*_m13 + _m5*_m8*_m14 - _m4*_m9*_m14;
	result._m13 = _m1*_m10*_m12 - _m2*_m9*_m12  + _m2*_m8*_m13 - _m0*_m10*_m13 - _m1*_m8*_m14 + _m0*_m9*_m14;
	result._m14 = _m2*_m5*_m12  - _m1*_m6*_m12  - _m2*_m4*_m13 + _m0*_m6*_m13  + _m1*_m4*_m14 - _m0*_m5*_m14;
	result._m15 = _m1*_m6*_m8   - _m2*_m5*_m8   + _m2*_m4*_m9  - _m0*_m6*_m9   - _m1*_m4*_m10 + _m0*_m5*_m10;

	return result;
}

Matrix Matrix::operator+() const
{
	return Matrix(Vect(+this->_m0,  +this->_m1,  +this->_m2,  +this->_m3),
				  Vect(+this->_m4,  +this->_m5,  +this->_m6,  +this->_m7),
				  Vect(+this->_m8,  +this->_m9,  +this->_m10, +this->_m11),
				  Vect(+this->_m12, +this->_m13, +this->_m14, +this->_m15));
}

Matrix Matrix::operator-() const
{
	return Matrix(Vect(-this->_m0,  -this->_m1,  -this->_m2,  -this->_m3),
				  Vect(-this->_m4,  -this->_m5,  -this->_m6,  -this->_m7),
				  Vect(-this->_m8,  -this->_m9,  -this->_m10, -this->_m11),
				  Vect(-this->_m12, -this->_m13, -this->_m14, -this->_m15));
}



// ---  End of File ---------------
