// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
  // Please implement this. 
	// glm::dot, glm::cross, glm::normalize, and glm::radians
	
	vec3 a = glm::normalize(axis);
	float sine = sin(glm::radians(degrees)), cosine = cos(glm::radians(degrees));
	float x = a.x, y = a.y, z = a.z;

	mat3 aat = mat3(x*x, y*x, z*x,
								  x*y, y*y, z*y,
								  x*z, y*z, z*z);

	mat3 aStar = mat3( 0, -z,  y,
									   z,  0, -x,
										-y,  x,  0);

	mat3 rotateM = glm::mat3(cosine) + (1-cosine) * aat + sine * aStar;

	return rotateM;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	mat3 rotationMatrix = Transform::rotate(degrees, up);
	eye = eye * rotationMatrix;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	mat3 rotationMatrix = Transform::rotate(degrees, glm::cross(eye,up));
	eye = eye * rotationMatrix;
	up = up * rotationMatrix;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up,w));
	vec3 v = glm::cross(w,u);
	mat4 transformM = mat4(u.x, u.y, u.z, -glm::dot(u,eye),
												 v.x, v.y, v.z, -glm::dot(v,eye),
												 w.x, w.y, w.z, -glm::dot(w,eye),
												 0  ,   0,   0,     1.0f);
	return transformM;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
