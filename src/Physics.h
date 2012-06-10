/*
 * Physics.h
 *
 *  Created on: 09/06/2012
 *      Author: Rafael Fonte
 */

#define WORLD_DIMENSIONS 3

#ifndef PHYSICS_H_
#define PHYSICS_H_

class Physics {
public:
	Physics(unsigned double mass,
			double position[], double speed[], double acceleration[],
			double thetaPosition[], double thetaSpeed[], double thetaAcceleration[],
			double phiPosition[], double phiSpeed[], double phiAcceleration[]
	);
	virtual ~Physics();

private:
	unsigned double mass = 1.0;

	double position[3] = {0.0,0.0,0.0};
	double speed[3] = {0.0,0.0,0.0};
	double acceleration[3] = {0.0,0.0,0.0};

	double thetaPosition[3] = {0.0,0.0,0.0};
	double thetaSpeed[3] = {0.0,0.0,0.0};
	double thetaAcceleration[3] = {0.0,0.0,0.0};

	double phiPosition[3] = {0.0,0.0,0.0};
	double phiSpeed[3] = {0.0,0.0,0.0};
	double phiAcceleration[3] = {0.0,0.0,0.0};
};

#endif /* PHYSICS_H_ */
