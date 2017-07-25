
#include "Particle.h"

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>


using namespace std;

Particle::Particle(int i, int j, double x, double y, double yaw, double belief)
{
	this->row = i;
	this->col = j;
	this->x = x;
	this->y = y;
	this->yaw = yaw;
	this->belief = belief;
}

Particle::Particle()
{
	this->row = 0;
	this->col = 0;
	this->x = 0;
	this->y = 0;
	this->yaw = 0;
	this->belief = 0;
}

Particle::~Particle()
{


}
