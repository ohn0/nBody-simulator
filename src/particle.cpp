#include "particle.h"

Particle::~Particle()
{
    //dtor
}

Particle::Particle()
{
    Rx = Ry = Vx = Vy = mass = 0;
}

double Particle::distToParticle(const Particle& nBody)
{
    double deltaX, deltaY;
    deltaX = nBody.Rx - Rx;
    deltaY = nBody.Ry - Ry;

    deltaX = pow(deltaX, 2);
    deltaY = pow(deltaY, 2);

    return sqrt(deltaX + deltaY);
}

double Particle::gravForce(const Particle& nBody)
{
    double dist = distToParticle(nBody);
    return ((GRAV_CONST * mass * nBody.mass)/(pow(dist, 2)));
}

double Particle::forceComponentX(const Particle& nBody, const double& gravForce)
{
    double dist = distToParticle(nBody);
    return (gravForce* ((nBody.Rx - Rx)/dist));
}

double Particle::forceComponentY(const Particle& nBody, const double& gravForce)
{
    double dist = distToParticle(nBody);
    return (gravForce * ((nBody.Ry - Ry)/dist));
}

double Particle::accelComponentX(const double& forceX)
{
    return forceX/mass;
}

double Particle::accelComponentY(const double& forceY)
{
    return forceY/mass;
}


void Particle::updateVx(double accelX)
{
    Vx = Vx + DELTA_TIME*accelX;
}

void Particle::updateVy(double accelY)
{
    Vy = Vy + DELTA_TIME*accelY;
}

void Particle::updateRx()
{
    Rx = Rx + DELTA_TIME*Vx;
}

void Particle::updateRy()
{
    Ry = Ry + DELTA_TIME*Vy;
}
