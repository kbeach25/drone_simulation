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
    
    // Find thrust as a function of % of RPM (7310 rpm per rotor hovers for 0.116kg drone, 30% of total rpm range)
    void calculateThrust(int percent, int rotor);

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


};

#endif
