#include <iostream>
#include <chrono>
#include <thread>
#include "drone.h"

int main() {
    Drone drone;
    Vector3 gravity = {0.0f, -9.81f*drone.getMass(), 0.0f};

    // Set rotor thrust for each (N), will change when real-time control is integrated
   // drone.setRotorThrust(0, 2.4525f);
   /// drone.setRotorThrust(1, 2.4525f);
   // drone.setRotorThrust(2, 2.4525f);
   // drone.setRotorThrust(3, 2.4525f);

    drone.calculateThrust(0, 0);
    drone.calculateThrust(0, 1);
    drone.calculateThrust(0, 2);
    drone.calculateThrust(0, 3);


    for (int i = 0; i < 100; ++i) {
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
