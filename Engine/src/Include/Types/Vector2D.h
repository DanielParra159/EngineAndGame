#ifndef _ENGINE_VECTOR2D_H_
#define _ENGINE_VECTOR2D_H_

#include<math.h>
template <typename T = int32>
class Vector2D
{
private:
	T mX, mY;

public:
	Vector2D() { mX = 0; mY = 0; };
	Vector2D(T aX, T aY) : mX(aX), mY(aY) {}
	Vector2D(const Vector2D<T>& aV2) : mX(aV2.mX), mY(aV2.mY) {};
	T GetX() const { return mX; }
	T GetY() const { return mY; }
	void SetX(T aX) { mX = aX; }
	void SetY(T aY) { mY = aY; }

	T Length() const
	{
		return sqrt(mX * mX + mY * mY);
	}
	T LengthSqrt(void) const
	{
		return (mX*mX + mY*mY);
	}

	void NormalizeThis()
	{
		T l = Length();
		if (l > 0)
		{
			(*this) *= 1 / l;
		}
	}
	Vector2D<T>& Normalize()
	{
		T l = (T)Length();
		if (l == 0)	return *this;
		l = (T)1.0 / l;
		mX *= l;
		mY *= l;
		return *this;
	}

	const T DotProduct(const Vector2D<T>& aV2) const
	{
		return ((mX*aV2.mX) + (mY*aV2.mY));
	}
	const Vector2D<T> CrossProduct(const Vector2D<T>& aV2) const
	{
		return Vector2D<T>(mY*aV2.mX - mX*aV2.mY, mX*aV2.mY - mY*aV2.mX);
	}
	T GetDistance(const Vector2D<T>& aV2) const
	{
		return T(Vector2D<T>(mX - aV2.mX, mY - aV2.mY).Length());
	}
	T GetDistanceSqrt(const Vector2D<T>& aV2) const
	{
		return T(Vector2D<T>(mX - aV2.mX, mY - aV2.mY).LengthSq());
	}

	bool operator==(const Vector2D<T>& aV2) const
	{
		return (mX == aV2.mX) && (mY == aV2.mY);
	}
	bool operator!=(const Vector2D<T>& aV2) const
	{
		return (mX != aV2.mX) || (mY != aV2.mY);
	}

	Vector2D operator+(const Vector2D& aV2) const
	{
		return Vector2D(mX + aV2.mX, mY + aV2.mY);
	}
	Vector2D<T>& operator+=(const Vector2D<T>& aV2)
	{
		mX += aV2.mX;
		mY += aV2.mY;
		return *this;
	}
	Vector2D<T>  operator+(const T aScalar) const
	{
		return Vector2D<T>(mX + aScalar, mY + aScalar);
	}
	Vector2D<T>& operator+=(const T aScalar)
	{
		mX += aScalar;
		mY += aScalar;
		return *this;
	}

	Vector2D operator-(const Vector2D& aV2) const
	{
		return Vector2D(mX - aV2.mX, mY - aV2.mY);
	}
	Vector2D<T>& operator-=(const Vector2D<T>& aV2)
	{
		mX -= aV2.mX;
		mY -= aV2.mY;
		return *this;
	}
	Vector2D<T>  operator-(const T aScalar) const
	{
		return Vector2D<T>(mX - aScalar, mY - aScalar);
	}
	Vector2D<T>& operator-=(const T aScalar)
	{
		mX -= aScalar;
		mY -= aScalar;
		return *this;
	}

	Vector2D operator*(T aScalar)
	{
		return Vector2D(mX * aScalar, mY * aScalar);
	}
	Vector2D& operator*=(T aScalar)
	{
		mX *= aScalar;
		mY *= aScalar;
		return *this;
	}

	Vector2D operator/(T aScalar)
	{
		return Vector2D(mX / aScalar, mY / aScalar);
	}
	Vector2D& operator/=(T aScalar)
	{
		mX /= aScalar;
		mY /= aScalar;
		return *this;
	}
};
#endif // _ENGINE_VECTOR2D_H_