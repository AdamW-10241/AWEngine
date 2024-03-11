#pragma once

struct Vector2 {
	// Simple Constructor
	Vector2() : x(0.0f), y(0.0f) {}
	// Assigned Constructor
	Vector2(float x, float y) : x(x), y(y) {}
	// Uniform Constructor
	Vector2(float uniform) : x(uniform), y(uniform) {}

	~Vector2() = default;

	// OPERATORS
	// Vector 2 Assignment Operator
	Vector2& operator=(const Vector2& Other) {
		x = Other.x;
		y = Other.y;

		return *this;
	}

	// Boolean Operators
	// If two Vector2's are equal
	bool operator==(const Vector2& Other) {
		return x == Other.x && y == Other.y;
	}
	// If two Vector2's are not equal
	bool operator!=(const Vector2& Other) {
		return x != Other.x || y != Other.y;
	}

	// Arithmetic Operators
	// Addition
	Vector2 operator+(const Vector2& Other) {
		return Vector2(Other.x + x, Other.y + y);
	}
	// Addition Equals
	Vector2& operator+=(const Vector2& Other) {
		return *this = *this + Other;
	}
	// Subtraction
	Vector2 operator-(const Vector2& Other) {
		return Vector2(x - Other.x, y - Other.y);
	}
	// Subtraction Equals
	Vector2& operator-=(const Vector2& Other) {
		return *this = *this - Other;
	}
	// Multiply Vector2 by Vector2
	Vector2 operator*(const Vector2& Other) {
		return Vector2(x * Other.x, y * Other.y);
	}
	// Multiply Equals Vector2 by Vector2
	Vector2& operator*=(const Vector2& Other) {
		return *this = *this * Other;
	}
	// Multiply Vector2 by Float
	Vector2 operator*(const float Scalar) {
		return Vector2(x * Scalar, y * Scalar);
	}
	// Multiply Equals Vector2 by Float
	Vector2& operator*=(const float Scalar) {
		return *this = *this * Scalar;
	}
	// Division Vector2 by Vector2
	Vector2 operator/(const Vector2& Other);
	// Division Equals Vector2 by Vector2
	Vector2& operator/=(const Vector2& Other);
	// Division Vector2 by Float
	Vector2 operator/(const float& Scalar);
	// Division Equals Vector2 by Float
	Vector2 operator/=(const float& Scalar);

	// Return an infinite negative vector (invalid vector)
	static Vector2 NaN();

	// Get the squared length / magnitude / size of the Vector2
	// This is inaccurate by double the size but cheaper
	float LengthSqd() const {
		return x * x + y * y;
	}
	// Get the length / magnitude / size of the Vector2
	float Length() const;

	// Get the distance between two Vector2's
	// This is inaccurate by double the size but cheaper
	static float DistSqd(Vector2& V1, Vector2& V2) {
		Vector2 DistanceVector(V1 - V2);
		// x^2 + y^2
		return DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y;
	}
	// Get the distance between two Vector2's
	static float Distance(Vector2& V1, Vector2& V2);

	// Change the Vector2 to a normalised value
	Vector2& Normalise();

	// Return a normalised Vector2 based on another Vector2
	static Vector2 Normalised(const Vector2& Other);
	
	// Log the Vector2 to the console
	void Log();

	// Log the Length of Vector2 to the console
	void LogLength();

	float x, y;
};