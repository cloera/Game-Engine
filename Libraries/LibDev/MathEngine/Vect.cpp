//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <math.h>

#include "MathEngine.h"

Vect::Vect()
	: _vx(0), _vy(0), _vz(0), _vw(1.0f)
{
}

Vect::Vect(const Vect & in) 
{
	this->_vx = in._vx;
	this->_vy = in._vy;
	this->_vz = in._vz;
	this->_vw = in._vw;
}

const Vect & Vect::operator=(const Vect & in)
{
	if (this != &in)
	{
		this->_vx = in._vx;
		this->_vy = in._vy;
		this->_vz = in._vz;
		this->_vw = in._vw;
	}
	return *this;
}

Vect::~Vect()
{
	// Do nothing
}

Vect::Vect(const float x, const float y, const float z, const float w)
	: _vx(x), _vy(y), _vz(z), _vw(w)
{
}

float & Vect::operator[](const enum x_enum)
{
	return this->_vx;
}

float & Vect::operator[](const enum y_enum)
{
	return this->_vy;
}

float & Vect::operator[](const enum z_enum)
{
	return this->_vz;
}

float & Vect::operator[](const enum w_enum)
{
	return this->_vw;
}

const float& Vect::operator[](const enum x_enum) const
{
	return this->_vx;
}

const float& Vect::operator[](const enum y_enum) const
{
	return this->_vy;
}

const float& Vect::operator[](const enum z_enum) const
{
	return this->_vz;
}

const float& Vect::operator[](const enum w_enum) const
{
	return this->_vw;
}


float & Vect::x()
{
	return this->_vx;
}

float & Vect::y()
{
	return this->_vy;
}

float & Vect::z()
{
	return this->_vz;
}

float & Vect::w()
{
	return this->_vw;
}

const float & Vect::x() const
{
	return this->_vx;
}

const float & Vect::y() const
{
	return this->_vy;
}

const float & Vect::z() const
{
	return this->_vz;
}

const float & Vect::w() const
{
	return this->_vw;
}

void Vect::set(const float x, const float y, const float z, const float w)
{
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
	this->_vw = w;
}

void Vect::set(const Vect vect)
{
	this->_vx = vect._vx;
	this->_vy = vect._vy;
	this->_vz = vect._vz;
	this->_vw = vect._vw;
}

Vect Vect::operator+() const
{
	return Vect(+this->_vx, +this->_vy, +this->_vz);
}

Vect Vect::operator-() const
{
	return Vect(-this->_vx, -this->_vy, -this->_vz);
}

Vect Vect::operator+(const Vect & v) const
{
	return Vect(this->_vx + v._vx, this->_vy + v._vy, this->_vz + v._vz);
}

void Vect::operator+=(const Vect & v)
{
	this->_vx += v._vx;
	this->_vy += v._vy;
	this->_vz += v._vz;
	this->_vw = 1.0f;
}

Vect Vect::operator-(const Vect & v) const
{
	return Vect(this->_vx - v._vx, this->_vy - v._vy, this->_vz - v._vz);
}

void Vect::operator-=(const Vect & v)
{
	this->_vx -= v._vx;
	this->_vy -= v._vy;
	this->_vz -= v._vz;
	this->_vw = 1.0f;
}

void Vect::operator*=(const float & scalar)
{
	this->_vx = this->_vx * scalar;
	this->_vy = this->_vy * scalar;
	this->_vz = this->_vz * scalar;
	this->_vw = MATH_ONE;
}

const float Vect::dot(const Vect v) const
{
	return (this->_vx * v._vx) + (this->_vy * v._vy) + (this->_vz * v._vz);
}

const Vect Vect::cross(const Vect v) const
{
	return Vect(this->_vy*v._vz - this->_vz*v._vy, -(this->_vx*v._vz - this->_vz*v._vx),
				this->_vx*v._vy - this->_vy*v._vx, 1);
}

void Vect::norm()
{
	float mag = this->mag();
	this->_vx = this->_vx / mag;
	this->_vy = this->_vy / mag;
	this->_vz = this->_vz / mag;
}

Vect Vect::getNorm() const
{
	float mag = this->mag();
	return Vect(this->_vx / mag, this->_vy / mag, this->_vz / mag);
}

const float Vect::mag() const
{
	return sqrtf(this->_vx*this->_vx + this->_vy*this->_vy + this->_vz*this->_vz);
}

const float Vect::magSqr() const
{
	return (this->_vx*this->_vx + this->_vy*this->_vy + this->_vz*this->_vz);
}

const float Vect::getAngle(const Vect v) const
{
	return acosf( (this->dot(v)) / (this->mag() * v.mag()) );
}

bool Vect::isZero(const float epsilon) const
{
	if(!Util::isZero(this->_vx, epsilon))
	{
		return false;
	}
	if (!Util::isZero(this->_vy, epsilon))
	{
		return false;
	}
	if (!Util::isZero(this->_vz, epsilon))
	{
		return false;
	}
	// Must subtract by 1.0f since w is always 1.0f
	if (!Util::isZero(this->_vw - 1.0f, epsilon))
	{
		return false;
	}
	return true;
}

bool Vect::isEqual(const Vect& v, const float epsilon) const
{
	if (!Util::isEqual(this->_vx, v._vx, epsilon))
	{
		return false;
	}
	if (!Util::isEqual(this->_vy, v._vy, epsilon))
	{
		return false;
	}
	if (!Util::isEqual(this->_vz, v._vz, epsilon))
	{
		return false;
	}
	if (!Util::isEqual(this->_vw, v._vw, epsilon))
	{
		return false;
	}
	return true;
}



// ---  End of File ---------------

