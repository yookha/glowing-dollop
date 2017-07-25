#ifndef ROBOT_H_
#define ROBOT_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include "Constants.h"
#include <math.h>
#include "Node.h";
#include "Map.h"
#include <set>
#include "RobotStructs.h"

using namespace HamsterAPI;
using namespace std;

class Robot {
private:
	Hamster *hamster;
	double prev_x, prev_y, prev_yaw;
	double current_x, current_y, current_yaw;

	void printWaypoints(std::list<Node*> waypoints);

	bool checkWallAhead();
	void getScansBetween(double min, double max,std::vector<double> & distances);
	void moveForward();
	void moveBackwards();
	bool isFrontFree();
	bool willCollide(std::vector<double> distances,int afc);
		bool isLeftFree();
		bool isRightFree();
		bool isBackFree();
		void turnLeft() ;
		void turnRight();
		void turnAround();
		void stopMoving() ;

public:

	//constructor
	Robot(Hamster *hamster);

	// TODO: check
	void updateRobotPosition();

	//calculate delta between positions
	double DeltaX() const;
	double DeltaYaw() const;
	double DeltaY() const;


	void move(robotState startPosition, std::list<Node* > waypoints, Node* goalPosition, Map map);
	double calculateAngleDegrees(double deltaX, double deltaY);

	struct robotState getRobotState(OccupancyGrid ogrid, robotState startPosition);

	//distructor
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
