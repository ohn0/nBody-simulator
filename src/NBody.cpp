#include "NBody.h"

NBody::NBody(const std::string& filename)
{
    std::ifstream NBodyFile(filename);
    double value = 0;

    while(NBodyFile >> value){
        bodies.push_back(Particle());
        bodies.back().Rx = value;
        NBodyFile >> value; bodies.back().Ry = value;
        NBodyFile >> value; bodies.back().Vx = value;
        NBodyFile >> value; bodies.back().Vy = value;
        NBodyFile >> value; bodies.back().mass = value;
    }
    NBodyFile.close();
    int i = 0;
    while(i < bodies.size()){
        forceX.push_back(0);
        forceY.push_back(0);
        i++;
    }
    for(i = 0; i < 2;i++){
        bodyThreads.push_back(std::thread());
    }
}

void NBodyThreadUpdate(const std::vector<Particle>::iterator& currentBody, std::vector<Particle>::iterator nBodyIterator,
                       const std::vector<Particle>::iterator& nBodyEnd, double* forceX, double* forceY, int bodySize)
{
    *forceX = 0;
    *forceY = 0;
    double gForce = 0;
    int workValues = bodySize/2;
    int j = 0;
    std::vector<Particle>::iterator nBodyBegin = nBodyIterator;
    while(j < workValues && currentBody+j != nBodyEnd){
        *forceX = 0;
        *forceY = 0;
        nBodyIterator = nBodyBegin;
        while(nBodyIterator != nBodyEnd){
            if(nBodyIterator != currentBody+j){
                gForce = (currentBody+j)->gravForce(*nBodyIterator);
                *forceX = (currentBody+j)->forceComponentX(*nBodyIterator, gForce);
                *forceY = (currentBody+j)->forceComponentY(*nBodyIterator, gForce);
            }
            nBodyIterator++;
        }
        forceX++;
        forceY++;
        j++;
    }
//    while(nBodyIterator != nBodyEnd && workValues+i < bodySize){
//        if(nBodyIterator != currentBody){
//            gForce = currentBody->gravForce(*nBodyIterator);
//            *forceX += currentBody->forceComponentX(*nBodyIterator, gForce);
//            *forceY += currentBody->forceComponentY(*nBodyIterator, gForce);
//        }
//        nBodyIterator++;
//        i++;
//    }
}

void NBody::updateNbodies()
{
    double gForce = 0;
    double accelX, accelY;
    accelX = accelY = 0;
    std::vector<Particle>::iterator bodyIterator = bodies.begin();
    std::vector<Particle>::iterator currentBody = bodies.begin();
    int i = 0;
    while(currentBody != bodies.end()){
        bodyIterator = bodies.begin();
        forceX[i] = 0;
        forceY[i] = 0;
        while(bodyIterator != bodies.end()){
            if(bodyIterator != currentBody){
                gForce = currentBody->gravForce(*bodyIterator);
                forceX[i] += currentBody->forceComponentX(*bodyIterator, gForce);
                forceY[i] += currentBody->forceComponentY(*bodyIterator, gForce);
            }
            bodyIterator++;
        }
        currentBody++; i++;
    }
    i = 0;
    bodyIterator = bodies.begin(); i = 0;
    while(bodyIterator != bodies.end()){
        accelX = bodyIterator->accelComponentX(forceX[i]);
        accelY = bodyIterator->accelComponentY(forceY[i]);
        bodyIterator->updateVx(accelX);
        bodyIterator->updateVy(accelY);
        bodyIterator->updateRx();
        bodyIterator->updateRy();
        bodyIterator++;i++;
    }

}

void NBody::printNbodies()
{
    std::vector<Particle>::iterator bodyIterator = bodies.begin();
    while(bodyIterator != bodies.end()){
        std::cout << bodyIterator->Rx << "\t" << bodyIterator->Ry << std::endl;
        bodyIterator++;
    }
}

NBody::~NBody()
{
    //dtor
}
