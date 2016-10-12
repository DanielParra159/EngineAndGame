#ifndef _ENGINE_VECTOR3D_H_
#define _ENGINE_VECTOR3D_H_

#include <math.h>

template <typename T = float32>
class Vector3D
{
public:
	T mX, mY, mZ;
	static const Vector3D<T> zero;
	static const Vector3D<T> one;
	static const Vector3D<T> right;
	static const Vector3D<T> up;
	static const Vector3D<T> forward;
public:
	Vector3D() { mX = 0; mY = 0; mZ = 0; };
	Vector3D(T aX, T aY, T aZ) : mX(aX), mY(aY), mZ(aZ) {}
	Vector3D(const Vector3D<T>& aV3) : mX(aV3.mX), mY(aV3.mY), mZ(aV3.mZ) {};

	T Length() const
	{
		return sqrt(mX*mX + mY*mY + mYZ*mYZ);
	}
	T LengthSqrt(void) const
	{
		return (mX*mX + mY*mY + mZ*mZ);
	}

	Vector3D<T>& Normalize()
	{
		T l = (T)Length();
		if (l == 0)	return *this;
		l = (T)1.0 / l;
		mX *= l;
		mY *= l;
		mZ *= l;
		return *this;
	}

	const T DotProduct(const Vector3D<T>& aV3) const
	{
		return ((mX*aV3.mX) + (mY*aV3.mY) + (mZ*aV3.mZ));
	}
	const Vector3D<T> CrossProduct(const Vector3D<T>& aV3) const
	{
		return Vector3D<T>((mY*aV3.mZ) - (mZ*aV3.mY), (mZ*aV3.mX) - (mX*aV3.mZ), (mX*aV3.mY) - (mY*aV3.mX));
	}
	T GetDistance(const Vector3D<T>& aV3) const
	{
		return T(Vector3D<T>(mX - aV3.mX, mY - aV3.mY, mZ - aV3.mZ).Length());
	}
	T GetDistanceSqrt(const Vector3D<T>& aV3) const
	{
		return T(Vector3D<T>(mX - aV3.mX, mY - aV3.mY, mZ - aV3.mZ).LengthSq());
	}

	bool operator==(const Vector3D<T>& aV3) const
	{
		return (mX == aV3.mX) && (mY == aV3.mY) && (mZ == aV3.mZ);
	}
	bool operator!=(const Vector3D<T>& aV3) const
	{
		return (mX != aV3.mX) || (mY != aV3.mY) || (mZ != aV3.mZ)
	}

	Vector3D operator+(const Vector3D& aV3) const
	{
		return Vector3D(mX + aV3.mX, mY + aV3.mY, mZ + aV3.mZ);
	}
	Vector3D<T>& operator+=(const Vector3D<T>& aV3)
	{
		mX += aV3.mX;
		mY += aV3.mY;
		mZ += aV3.mZ;
		return *this;
	}
	Vector3D<T>  operator+(const T aScalar) const
	{
		return Vector3D<T>(mX + aScalar, mY + aScalar, mZ + aScalar);
	}
	Vector3D<T>& operator+=(const T aScalar)
	{
		mX += aScalar;
		mY += aScalar;
		mZ += aScalar;
		return *this;
	}

	Vector3D operator-(const Vector3D& aV3) const
	{
		return Vector3D(mX - aV3.mX, mY - aV3.mY, mZ - aV3.mZ);
	}
	Vector3D<T>& operator-=(const Vector3D<T>& aV3)
	{
		mX -= aV3.mX;
		mY -= aV3.mY;
		mZ -= aV3.mZ;
		return *this;
	}
	Vector3D<T>  operator-(const T aScalar) const
	{
		return Vector3D<T>(mX - aScalar, mY - aScalar, mZ - aScalar);
	}
	Vector3D<T>& operator-=(const T aScalar)
	{
		mX -= aScalar;
		mY -= aScalar;
		mZ -= aScalar;
		return *this;
	}

	Vector3D operator*(T aScalar) const
	{
		return Vector3D(mX * aScalar, mY * aScalar, mZ * aScalar);
	}
	Vector3D& operator*=(T aScalar)
	{
		mX *= aScalar;
		mY *= aScalar;
		mZ *= aScalar;
		return *this;
	}
	Vector3D& operator*=(const Vector3D<T>& aScalar)
	{
		mX *= aScalar.mX;
		mY *= aScalar.mY;
		mZ *= aScalar.mZ;
		return *this;
	}

	Vector3D operator/(T aScalar) const
	{
		return Vector3D(mX / aScalar, mY / aScalar, mZ / aScalar);
	}
	Vector3D& operator/=(T aScalar)
	{
		mX /= aScalar;
		mY /= aScalar;
		mZ /= aScalar;
		return *this;
	}
};

//Vector3D<float32> Vector3D<float32>::zero = Vector3D();
#endif // _ENGINE_VECTOR3D_H_