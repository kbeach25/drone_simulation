#ifndef DRONE_H
#define DRONE_H

struct Vector3 {
    float x, y, z;
};

class Drone {
public:
    Drone();
    void update(float dt);
    void applyForce(const Vector3& force);
    Vector3 getPosition() const;

private:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    float mass;
};

#endif
