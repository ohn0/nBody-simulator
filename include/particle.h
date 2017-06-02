#ifndef PARTICLE_H
#define PARTICLE_H
#include <cmath>
const double GRAV_CONST = 6.6740E-11;
const double DELTA_TIME = 6;
class Particle
{
    //A class for each body in the system.
    public:
        double Rx, Ry, Vx, Vy;
        double mass;
        Particle();
        Particle(double Rx, double Ry, double Vx, double Vy, double mass) : Rx(Rx), Ry(Ry), Vx(Vx), Vy(Vy), mass(mass) { };
        virtual ~Particle();
        double distToParticle(const Particle&);
        double gravForce(const Particle&);
        double forceComponentX(const Particle&, const double&);
        double forceComponentY(const Particle&, const double&);
        double accelComponentX(const double&);
        double accelComponentY(const double&);
        void updateVx(double);
        void updateVy(double);
        void updateRx();
        void updateRy();
};

#endif // PARTICLE_H
