
#ifndef MAP_H_
#define MAP_H_

#include <opencv2/core/core.hpp>
#include <vector>

#include "/opt/hamster/HamsterRosInstall/include/HamsterAPICommon/Messages/OccupancyGrid.h"

#include "Particle.h"
#include "PointType.cpp"
#include "Node.h"

#define TOP_PARTICLES 5
#define MIN_BLUE_BELIFE 0.6

using namespace HamsterAPI;


class Map {
private:
	OccupancyGrid ogrid;

public:
	cv::Mat * mat;
	cv::Mat * inflatedMap;
	//constructor
	Map(OccupancyGrid ogrid);

	// inflates the map
	void inflateMap(int robotSize);

	// Set map borders
	void setMapBorders(cv::Mat *mat);

	//print the view window map
	void paintMap(std::vector<Particle*> particles);

	//print red particales
	void paintRedPluse(int i , int j);

	//print blue particales
	void paintBluePluse(int i , int j);

	//print green particales
	void paintGreenPluse(int i , int j);

	//print red pixel
	void paintRedDot(int i , int j);

	//print blue pixel
	void paintBlueDot(int i , int j);

	//print green pixel
	void paintGreenDot(int i , int j);


	void setPointColor(cv::Mat * matrix, int x, int y, int red, int green, int blue);

	void setPointType(int x ,int y, PointType type);

	void drawPath(Node* goal);

	void showMap();

	//distructor
	virtual ~Map();


	/*getters and setters*/
	const OccupancyGrid& getOgrid() const {
		return ogrid;
	}

	const cv::Mat* getMat() const {
		return mat;
	}
};

#endif /* MAP_H_ */
