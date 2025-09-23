#include "drone.h"
#include <cmath>
#include <iostream>

// Initialize drone and rotors
// Drone mass: 0.116kg
Drone::Drone() : 
                position{0,0,0}, velocity{0,0,0}, acceleration{0,0,0}, mass(0.116f),
                tiltX(0.0f), tiltZ(0.0f), targetTiltX(0.0f), targetTiltZ(0.0f), tiltSpeed(1.0f) 
                
                
                {
    for (int i =0; i < 4; i++) rotorThrust[i] = 0.0f;
}

// Inputs: percentage of rotor thrust, rotor index
void Drone::calculateThrust(int percent, int rotor){
    // The drone hovers at about 50% total thrust
    // Thus, max thrust per rotor = 9.81 * mass / 4 / 0.5

    if (rotor >= 0 && rotor < 4) {
        rotorThrust[rotor] = ((percent * 9.81 * mass) / 400) / 0.5;
        std::cout << rotorThrust[rotor] << std::endl;
    }
}

void Drone::applyForce(const Vector3& force) {
    acceleration.x += force.x / mass;
    acceleration.y += force.y / mass;
    acceleration.z += force.z / mass;
}

// Convert tilt to radians
void Drone::applyTilt(float degreesX, float degreesZ){
    targetTiltX= degreesX * M_PI / 180.0;
    targetTiltZ= degreesZ * M_PI / 180.0;
}

void Drone::update(float dt) {

    // Combine thrust from each of the rotors for total force
    float totalThrust = 0.0f;

    // Find total thrust for drone
    for (int i = 0; i < 4; i++) {
        totalThrust += rotorThrust[i];
    }


    // Split thrust into x, y, and z
    float thrustX = totalThrust * std::sin(tiltX); // Left and right 
    float thrustY = totalThrust * std::cos(tiltX) * std::cos(tiltZ); // Up and down
    float thrustZ = totalThrust * std::sin(tiltZ); // Forwards and backwards


    // Apply force from 4 rotors to drone
    applyForce({thrustX, thrustY, thrustZ});

    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    velocity.z += acceleration.z * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    acceleration = {0, 0, 0};  // Reset for next frame

    // Control the rate of change of the drone's tilt
    auto smoothTilt = [](float currentTilt, float targetTilt, float speed, float dt) {
        float deltaTilt = targetTilt - currentTilt;
        std::cout << currentTilt << std::endl;

        if (std::abs(deltaTilt) < 0.001f) return targetTilt;
        return currentTilt + std::clamp(deltaTilt, -speed * dt, speed*dt);
        
    
    };

    tiltX = smoothTilt(tiltX, targetTiltX, tiltSpeed, dt);
    tiltZ = smoothTilt(tiltZ, targetTiltZ, tiltSpeed, dt);

    // Set floor for environment (very subject to change)
    if (position.y < 0.0f) {
        position.y = 0.0f;
        velocity.y = 0.0f;
    }
}

Vector3 Drone::getPosition() const {
    return position;
}
