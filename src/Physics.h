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
	Physics(double mass,
			double position[], double speed[], double acceleration[],
			double thetaPosition[], double thetaSpeed[], double thetaAcceleration[],
			double phiPosition[], double phiSpeed[], double phiAcceleration[]
	);
	virtual ~Physics();

private:
	double mass;

	double linearPosition[3];
	double linearSpeed[3];
	double linearAcceleration[3];

	double thetaPosition[3];
	double thetaSpeed[3];
	double thetaAcceleration[3];

	double phiPosition[3];
	double phiSpeed[3];
	double phiAcceleration[3];
};

#endif /* PHYSICS_H_ */
