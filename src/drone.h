#ifndef DRONE_H
#define DRONE_H

struct Vector3 {
    float x, y, z;
};

class Drone {
public:
    Drone();

    // Define drone functions
    void update(float dt);
    void applyForce(const Vector3& force);
    Vector3 getPosition() const;

    // 4 rotors, 2 blades per rotor
    
    // Thrust is calculated per rotor, 50% total thrust upwards makes the drone hover 
    void calculateThrust(int percent, int rotor);

    // xy plane movement functions
    void applyTilt(float degreesY, float degreesZ);

    // Need mass to be public
    float getMass() const { return mass; }

private:
    // Define drone variables
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    float mass;

    // Rotor variables
    float rotorThrust[4];

    // Drone angle variables
    // Real time tilt variables
    float tiltX; // Left and right tilt, - is left, + is right 
    float tiltZ; // Forwards and backwards tilt, + is forwards (front of drone tilting down), - is backwards

    // Target tilt variables
    float targetTiltX; 
    float targetTiltZ;
    float tiltSpeed;


};

#endif
