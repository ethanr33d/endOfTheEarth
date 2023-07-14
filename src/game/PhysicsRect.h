#pragma once

// position + size rectangle, essentially a floating point SDL_Rect
struct PhysicsRect {
	double x;
	double y;
	double w;
	double h;
	PhysicsRect() : x(0.0), y(0.0), w (0.0), h(0.0) {};
	PhysicsRect(double initX, double initY, double initW, double initH) : 
		x(initX), y(initY), w(initW), h(initH) {};
};