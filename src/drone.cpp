#include "drone.h"

Drone::Drone() : position{0,0,0}, velocity{0,0,0}, acceleration{0,0,0}, mass(1.0f) {}

void Drone::applyForce(const Vector3& force) {
    acceleration.x += force.x / mass;
    acceleration.y += force.y / mass;
    acceleration.z += force.z / mass;
}

void Drone::update(float dt) {
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    velocity.z += acceleration.z * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    acceleration = {0, 0, 0};  // Reset for next frame
}

Vector3 Drone::getPosition() const {
    return position;
}
