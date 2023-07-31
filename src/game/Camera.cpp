#include "Camera.h"

void Camera::offsetElements(const Vector2& offset) {
	for (PhysicsElement* element : *m_simulation.getElements()) {
		Vector2 newPos{ ceil(element->getPosition().x - offset.x), ceil(element->getPosition().y - offset.y)};
		element->setDrawablePosition(newPos);
	}
}

SDL_Rect Camera::getVisibleBounds() {
	return SDL_Rect{ static_cast<int>(m_cameraPosition.x),
		static_cast<int>(m_cameraPosition.y), 1000, 500 };
}

void Camera::setMode(CAMERA_MODE mode) {
	m_mode = mode;
}

void Camera::setSubject(PhysicsElement* element) {
	m_subject = element;
}

void Camera::step() {
	switch (m_mode) {
		case POSITION_FIXED:
			offsetElements(m_cameraPosition);
			break;
		case CENTER_SUBJECT:
			
			PhysicsRect subjectBounds = m_subject->getBounds();

			// center in the middle of screen
			m_cameraPosition = m_subject->getPosition() -
				Vector2{500 - subjectBounds.w / 2, 250 - subjectBounds.h / 2};
	
			offsetElements(m_cameraPosition);
			break;
	}
}