#include <iostream>
#include <chrono>
#include <thread>
#include "drone.h"

int main() {
    Drone drone;
    Vector3 gravity = {0.0f, -9.81f*drone.getMass(), 0.0f};


    // Thrust % range is 0 to 100, 50 makes it hover
    // Individual thrust calculations must be kept individual for steering control 
    // Rotors 0 and 1 are in the front, 2 and 3 are the back
    // Rotors 0 and 3 spin clockwise, 1 and 2 counterclockwise 
    drone.calculateThrust(100, 0);
    drone.calculateThrust(100, 1);
    drone.calculateThrust(100, 2);
    drone.calculateThrust(100, 3);

    // Apply tilt in degrees, X is left and right, Z is forwards and backwards
    drone.applyTilt(0, 0);

    // 2 second simulation
    for (int i = 0; i < 125; ++i) {
        // Gravity is applied each frame
        drone.applyForce(gravity);

        // Update drone, 60 fps
        drone.update(0.016f);  

        Vector3 pos = drone.getPosition();
        std::cout << "Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
