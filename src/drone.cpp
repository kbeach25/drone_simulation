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
    // Formula: thrust = ct * p * n^2 * D^4
    // ct = 0.10 (standard), p=1.225 (sea level), n = rpm / 60, D = diameter (5.25in for this drone, 0.133m)
    // 7310 rpm max for drone
    if (rotor >= 0 && rotor < 4) {
        rotorThrust[rotor] = 0.20 * 1.225 * std::pow((percent* 12000)/ (100* 60.0f), 2) * std::pow(0.133f, 4);
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
