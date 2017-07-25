
#ifndef PARTICLE_H_
#define PARTICLE_H_

////this class represent a particale in the map window
//class Particle {
//public:
//	int row, col; //the row/col index in the map
//	double x, y; //the exact place of the robot; x- place in column, y- place in row
//	double yaw; //the heading angle of the robot
//	double belief;
//
//
//};

class Particle {
public:
	int row, col;
	double x, y;
	double yaw;
	double belief;
	bool operator< (const Particle& p2) const
	{
		return (this->belief < p2.belief);
	}

	//a deafult constructor
		Particle();
		//constructor
		Particle(int i, int j, double x, double y, double yaw, double belief);
		//disconstructor
		~Particle();
};

#endif /* PARTICLE_H_ */


