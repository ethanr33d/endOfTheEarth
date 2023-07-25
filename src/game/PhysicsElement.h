// abstract class for all simulated physics elements
#pragma once 

#include "SDL2/SDL.h"
#include "Vector2.h"
#include "PhysicsRect.h"

class PhysicsElement {
	protected:
	SDL_Renderer* m_renderer;
	Vector2 m_drawablePosition; // computed by camera for final render position

	// final rendering size, separate from size used for physics calculations
	// by default is synced with physics size
	Vector2 m_drawableSize; 

	// these should only be set using modifying functions
	Vector2 m_size;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	bool m_anchored; // whether object moves, default = false
	bool m_collidable; // whether collision checks are enabled, default = true
	Vector2 m_maxVelocity; // max velocity (by magnitude) allowed along each axis
	double m_frictionConstant; // Affects the friction amount applied by elements grounded by this element

	// state information for element
	bool m_grounded; // whether element is grounded
	PhysicsElement* m_groundedBy; // element that this element is grounded against

	public:
	PhysicsElement(SDL_Renderer* renderer) : m_renderer(renderer), 
		m_maxVelocity(Vector2{INT_MAX, INT_MAX}), m_anchored(false),
		m_collidable(true), m_frictionConstant(0.5), m_grounded(false), m_groundedBy(nullptr) {};

	// safe modifiers that add to current vectors
	void applyVelocity(const Vector2& velocity);
	void applyAcceleration(const Vector2& acceleration);
	
	virtual void setSize(const Vector2& size); // allow overrides if additional processing neeeded
	void setPosition(const Vector2& position);
	void setVelocity(const Vector2& velocity); // prefer applyVelocity
	void setAcceleration(const Vector2& acceleration); // prefer applyAcceleration

	// should only be used by physics engine
	void _setGrounded(const bool grounded);
	void _setGroundingElement(PhysicsElement* element);

	void setAnchored(const bool anchored);
	void setCollidable(const bool collidable);
	void setMaxVelocity(const Vector2& maxVelocity);
	void setFrictionConstant(const double friction);
	void setDrawablePosition(const Vector2& position);

	Vector2 getSize() const;
	Vector2 getPosition() const;
	Vector2 getVelocity() const;
	Vector2 getAcceleration() const;
	
	bool isAnchored() const;
	bool isCollidable() const;
	Vector2 getMaxVelocity() const;
	double getFrictionConstant() const;

	bool isGrounded() const;
	PhysicsElement* getGroundingElement() const;

	SDL_Rect getRenderBounds() const;
	PhysicsRect getBounds() const;

	virtual void prePhysicsStep();
	virtual void postPhysicsStep();
	virtual void draw() = 0; // physics elements still need to be drawn
};