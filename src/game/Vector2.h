#pragma once

// generic vector
struct Vector2 {
	double x;
	double y;
	Vector2() : x(0.0), y(0.0) {};
	Vector2(double initX, double initY) : x(initX), y(initY) {};

	/* vector math functions */
	Vector2 operator+ (const Vector2& vector) {
		return Vector2{ this->x + vector.x, this->y + vector.y };
	};

	Vector2 operator* (const double scalar) {
		return Vector2{ this->x * scalar, this->y * scalar };
	};

	Vector2 operator* (const int scalar) {
		return Vector2{ this->x * static_cast<double>(scalar), this->y * static_cast<double>(scalar) };
	};
};