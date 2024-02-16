#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
	class CameraTema2
	{
	public:
		class CameraTema2()
		{
			position = glm::vec3(0, 2, 3);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			distanceToTarget = 3.25f;
		}

		class CameraTema2(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			Set(position, center, up);
		}

		~CameraTema2()
		{ }

		// Update camera
		void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			this->position = position;
			SetOrientation(glm::normalize(center - position), up);
		}

		// Function to set orientation based on forward and up vectors
		void SetOrientation(const glm::vec3& forward, const glm::vec3& up)
		{
			this->forward = glm::normalize(forward);
			this->right = glm::normalize(glm::cross(forward, up));
			this->up = glm::cross(right, forward);
		}

		// Function to update the camera based on object position
		void UpdateWithObject(const glm::vec3& objectPosition)
		{
			// Calculate new camera position based on the object's position
			glm::vec3 newCameraPosition = objectPosition - (distanceToTarget * forward);

			// Update the camera position
			position = newCameraPosition;

			// Update the forward vector to look at the object
			forward = glm::normalize(objectPosition - position);

			// Recalculate the right and up vectors based on the new forward vector
			right = glm::normalize(glm::cross(forward, up));
			up = glm::cross(right, forward);
		}

		void MoveForward(float distance)
		{
			// movement will keep the camera at the same height always
			// Example: If you rotate up/down your head and walk forward you will still keep the same relative distance (height) to the ground!
			// Translate the camera using the DIR vector computed from forward
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			position += dir * distance;
		}

		void TranslateForward(float distance)
		{
			// TODO : Translate the camera using the "forward" vector
			position += forward * distance;
		}

		void TranslateUpward(float distance)
		{
			// TODO : Translate the camera using the up vector
			position += up * distance;
		}

		void TranslateRight(float distance)
		{
			// TODO
			// Translate the camera using the "right" vector
			// Usually translation using camera "right' is not very useful because if the camera is rotated around the "forward" vector 
			// translation over the right direction will have an undesired effect; the camera will get closer or farther from the ground
			// Using the projected right vector (onto the ground plane) makes more sense because we will keep the same distance from the ground plane
			position += right * distance;
		}

		void RotateFirstPerson_OX(float angle)
		{
			// TODO
			// Compute the new "forward" and "up" vectors
			// Attention! Don't forget to normalize the vectors
			// Use glm::rotate()

			glm::vec4 new_forward = glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1);
			forward = glm::normalize(glm::vec3(new_forward));

			up = glm::cross(right, forward);

		}

		void RotateFirstPerson_OY(float angle)
		{
			// TODO
			// Compute the new "forward", "up" and "right" vectors
			// Don't forget to normalize the vectors
			// Use glm::rotate()

			glm::vec4 new_forward = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
			forward = glm::normalize(glm::vec3(new_forward));

			glm::vec4 new_right = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1);
			right = glm::normalize(glm::vec3(new_right));

			up = glm::cross(right, forward);
		}

		void RotateFirstPerson_OZ(float angle)
		{
			// TODO
			// Compute the new Right and Up, Forward stays the same
			// Don't forget to normalize the vectors

			glm::vec4 new_right = glm::rotate(glm::mat4(1.0f), angle, forward) * glm::vec4(right, 1);
			right = glm::normalize(glm::vec3(new_right));

			up = glm::cross(right, forward);
		}

		void RotateThirdPerson_OX(float angle)
		{
			// TODO
			// Rotate the camera in Third Person mode - OX axis
			// Use distanceToTarget as translation distance
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OY(float angle)
		{
			// TODO
			// Rotate the camera in Third Person mode - OY axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OY(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OZ(float angle)
		{
			// TODO
			// Rotate the camera in Third Person mode - OZ axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OZ(angle);
			TranslateForward(-distanceToTarget);
		}

		glm::mat4 GetViewMatrix()
		{
			// Returns the View Matrix
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 GetTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

	public:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;

	};
}