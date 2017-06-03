#ifndef NBODY_H
#define NBODY_H
#include "particle.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
class NBody
{
    std::vector<double> forceX;
    std::vector<double> forceY;
    std::vector<std::thread> bodyThreads;
    public:
        int intervalMax;
        int intervalCurrent;
        std::vector<Particle> bodies;
        NBody(const std::string&, int);
        virtual ~NBody();
        void updateNbodies();
        void printNbodies();
        void updatePositions();

};

#endif // NBODY_H
