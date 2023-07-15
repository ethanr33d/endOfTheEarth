// abstract class for all simulated physics elements
#pragma once 

#include "SDL2/SDL.h"
#include "Vector2.h"
#include "PhysicsRect.h"

class PhysicsElement {
	protected:
	SDL_Renderer* m_renderer;

	// these should only be set using modifiers below
	Vector2 m_size;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	bool m_anchored; // whether object moves, default = false
	bool m_collidable; // whether collision checks are enabled, default = true
	double m_maxVelocity;

	public:
	PhysicsElement(SDL_Renderer* renderer) : m_renderer(renderer), 
		m_maxVelocity(INT_MAX), m_anchored(false), m_collidable(true) {};

	// safe modifiers that add to current vectors
	void applyVelocity(const Vector2& velocity);
	void applyAcceleration(const Vector2& acceleration);
	
	void setSize(const Vector2& m_size);
	void setPosition(const Vector2& position);
	void setVelocity(const Vector2& velocity); 
	void setAcceleration(const Vector2& acceleration);

	void setAnchored(const bool anchored);
	void setCollidable(const bool collidable);
	void setMaxVelocity(const double maxVelocity);

	Vector2 getSize() const;
	Vector2 getPosition() const;
	Vector2 getVelocity() const;
	Vector2 getAcceleration() const;
	
	double getMaxVelocity();
	bool isAnchored();
	bool isCollidable();

	SDL_Rect getIntCastedBounds() const;
	PhysicsRect getBounds() const;
	virtual void draw() = 0; // physics elements still need to be drawn
};