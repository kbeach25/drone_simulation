#include <iostream>
#include <chrono>
#include <thread>
#include "drone.h"

int main() {
    Drone drone;
    Vector3 gravity = {0.0f, -9.8f, 0.0f};

    for (int i = 0; i < 100; ++i) {
        drone.applyForce(gravity);
        drone.update(0.016f);  // ~60 FPS

        Vector3 pos = drone.getPosition();
        std::cout << "Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
