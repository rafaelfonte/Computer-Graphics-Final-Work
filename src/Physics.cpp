/*
 * Physics.cpp
 *
 *  Created on: 09/06/2012
 *      Author: Rafael Fonte
 */

#include "Physics.h"

Physics::Physics(unsigned double mass,
				 double position[], double speed[], double acceleration[],
				 double thetaPosition[], double thetaSpeed[], double thetaAcceleration[],
				 double phiPosition[], double phiSpeed[], double phiAcceleration[])
{
	this->mass = mass;

	for(int i = 0; i < WORLD_DIMENSIONS; i++)
	{
		this->position[i] = position[i];
		this->speed[i] = speed[i];
		this->acceleration[i] = acceleration[i];
		this->thetaPosition[i] = thetaPosition[i];
		this->thetaSpeed[i] = thetaSpeed[i];
		this->thetaAcceleration[i] = thetaAcceleration[i];
		this->phiPosition[i] = thetaPosition[i];
		this->phiSpeed[i] = thetaSpeed[i];
		this->phiAcceleration[i] = thetaAcceleration[i];
	}

}

Physics::~Physics() {
	// TODO Auto-generated destructor stub
}
