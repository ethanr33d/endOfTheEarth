// class responsible for keeping the player in view

#pragma once
#include <SDL2/SDL.h>
#include "PhysicsElement.h"
#include "PhysicsRect.h"
#include "PhysicalWorld.h"
#include "Vector2.h"

// POSITION_FIXED: camera is fixed at a certain position
// CENTER_SUBJECT: camera is centered at subject
enum CAMERA_MODE{POSITION_FIXED, CENTER_SUBJECT};

class Camera {
	private:
		PhysicalWorld& m_simulation;
		CAMERA_MODE m_mode;
		PhysicsElement* m_subject;
		Vector2 m_cameraPosition;

		// offset all elements by offset value
		void offsetElements(const Vector2& offset);
	public:
		Camera(PhysicalWorld& simulation) : m_mode(POSITION_FIXED), m_subject(nullptr),
			m_simulation(simulation) {};

		// get the bounds of the screen visible portion of the simulation
		SDL_Rect getVisibleBounds();
	
		// change the camera mode
		void setMode(CAMERA_MODE mode);

		// set the subject of the camera for certain camera modes
		void setSubject(PhysicsElement* subject);

		// update drawing positions for all elements based on camera mode
		void step();
};