#include "Math/Vector2.h"
#include <iostream>
#include "Debug.h"

#define MINNORMAL 0.00001f

Vector2 Vector2::operator/(const Vector2& Other) const
{
	Vector2 NewVector(NaN());
	
	if (Other.x == 0.0f) {
		AW_LOG("Vector2", "Cannot divide by zero, returning with NaN x.");
	}
	else {
		NewVector.x = x / Other.x;
	}

	if (Other.y == 0.0f) {
		AW_LOG("Vector2", "Cannot divide by zero, returning with NaN y.");
	}
	else {
		NewVector.y = y / Other.y;
	}

	return NewVector;
}

Vector2& Vector2::operator/=(const Vector2& Other)
{
	return *this = *this / Other;
}

Vector2 Vector2::operator/(const float& Scalar) const
{
	if (Scalar == 0.0f)
	{
		AW_LOG("Vector2", "Cannot divide by zero, returning with NaN Vector2.");

		return Vector2::NaN();
	}
	
	return Vector2(x / Scalar, y / Scalar);
}

Vector2& Vector2::operator/=(const float& Scalar)
{
	return *this = *this / Scalar;
}

Vector2 Vector2::NaN()
{
	return Vector2(std::numeric_limits<float>::quiet_NaN());
}

float Vector2::Length() const
{
	// sqrtf(x^2 * y^2)
	return std::sqrtf(LengthSqd());
}

float Vector2::Distance(Vector2& V1, Vector2& V2)
{
	// sqrtf(x^2 + y^2)
	return std::sqrtf(DistSqd(V1, V2));
}

Vector2& Vector2::Normalise()
{
	if (Length() > MINNORMAL) {
		*this /= Length();
	}
	else {
		*this = Vector2();
	}

	return *this;
}

Vector2 Vector2::Normalised(const Vector2& Other)
{
	if (Other.Length() > MINNORMAL) {
		return Vector2(Other.x / Other.Length(), Other.y / Other.Length());
	}

	return Vector2();
}

void Vector2::Log()
{
	AW_LOG("Vector2", x << ", " << y);
}

void Vector2::LogLength()
{
	AW_LOG("Vector2", Length());
}
