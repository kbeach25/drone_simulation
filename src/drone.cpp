#include "drone.h"
#include <cmath>
#include <iostream>

// Initialize drone and rotors
// Drone mass: 0.116kg
Drone::Drone() : position{0,0,0}, velocity{0,0,0}, acceleration{0,0,0}, mass(0.116f) {
    for (int i =0; i < 4; i++) rotorThrust[i] = 0.0f;
}

// Inputs: percentage of total rpm, rotor index
void Drone::calculateThrust(int percent, int rotor){
    // The drone hovers at about 30% total thrust
    // Thus, max thrust per rotor = 9.81 * mass / 4 / 0.3

    if (rotor >= 0 && rotor < 4) {
        rotorThrust[rotor] = ((percent * 9.81 * mass) / 400) / 0.3;
        std::cout << rotorThrust[rotor] << std::endl;
    }
}

void Drone::applyForce(const Vector3& force) {
    acceleration.x += force.x / mass;
    acceleration.y += force.y / mass;
    acceleration.z += force.z / mass;
}

void Drone::update(float dt) {

    // Combine thrust from each of the rotors for total force
    float totalThrust = 0.0f;
    for (int i = 0; i < 4; i++) {
        totalThrust += rotorThrust[i];
    }

    // Apply force from 4 rotors to drone
    applyForce({0.0f, totalThrust, 0.0f});

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
