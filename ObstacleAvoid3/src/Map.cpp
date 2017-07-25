#include "Map.h"

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>

using namespace std;
Map::Map(OccupancyGrid ogrid) {
	this->ogrid = ogrid;

	this->mat = new cv::Mat(ogrid.getWidth(), ogrid.getHeight(), CV_8UC3, cv::Scalar(255, 255, 255));

	this->inflatedMap = new cv::Mat(ogrid.getWidth(), ogrid.getHeight(), CV_8UC3, cv::Scalar(255, 255, 255));

	cv::namedWindow("LocalizationView");
	cv::namedWindow("View");
}

void Map::inflateMap(int robotSize) {
	double resolutionInCms = ogrid.getResolution() * 100;

	double robotSizeInCms = robotSize / resolutionInCms;

	int inflationRadius = robotSizeInCms / 2;

	int width = ogrid.getWidth();
	int height = ogrid.getHeight();

	setMapBorders(inflatedMap);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (ogrid.getCell(i, j) == CELL_OCCUPIED) {

				for (int ii = -inflationRadius; ii < inflationRadius; ii++)
				{
					for (int jj = -inflationRadius; jj < inflationRadius; jj++)
					{
						if (ii + i >= 0 && ii + i < height && jj + j >= 0 && jj + j < width)
						{
							setPointColor(inflatedMap, i + ii, j + jj, 0, 0, 0);
						}
					}
				}
			}
		}
	}
}

void Map::paintMap(std::vector<Particle*> particles) {
	try
	{
		setMapBorders(mat);

		//paint particles
		for (unsigned int i = 0; i < particles.size(); i++)
		{
			if (particles[i]->belief > MIN_BLUE_BELIFE)
			{
				paintBluePluse(particles[i]->row, particles[i]->col);
			}
			else if (i >= (particles.size() - TOP_PARTICLES))
			{
				paintGreenPluse(particles[i]->row, particles[i]->col);
			}
			else
			{
				paintRedPluse(particles[i]->row, particles[i]->col);
			}
		}

		cv::imshow("LocalizationView", *mat);
		cv::waitKey(1);

	} catch (const HamsterAPI::HamsterError & message_error) {
		HamsterAPI::Log::i("Client", message_error.what());
	}
}

void Map::drawPath(Node* goal) {
	Node* currentNode = goal;

	// Mark goal point as green
	setPointColor(inflatedMap, currentNode->getX(), currentNode->getY(), 0, 255, 0);

	currentNode = currentNode->getParent();

	while (currentNode != NULL)
	{
		if (currentNode->getIsWaypoint())
		{
			setPointType(currentNode->getX(), currentNode->getY(), Waypoint);
		}
		else
		{
			setPointType(currentNode->getX(), currentNode->getY(), Path);
		}

		currentNode = currentNode->getParent();
	}
}

void Map::setPointType(int x, int y, PointType type) {
	switch (type) {
	case (Unknown): {
		setPointColor(inflatedMap, x, y, 128, 128, 128);
		break;
	}
	case (Free): {
		setPointColor(inflatedMap, x, y, 255, 255, 255);
		break;
	}
	case (Obstacle): {
		setPointColor(inflatedMap, x, y, 0, 0, 0);
		break;
	}
	case (Path): {
		setPointColor(inflatedMap, x, y, 255, 0, 0);
		break;
	}
	case (Waypoint): {
		setPointColor(inflatedMap, x, y, 255, 255, 0);
		break;
	}
	case (ParticleType): {
		setPointColor(inflatedMap, x, y, 0, 0, 255);
		break;
	}
	case (LidarScanObstacle): {
		setPointColor(inflatedMap, x, y, 255, 0, 255);
		break;
	}

	}
}

void Map::setMapBorders(cv::Mat *mat) {
	int width = ogrid.getWidth();
	int height = ogrid.getHeight();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			//print basic map
			if (ogrid.getCell(i, j) == CELL_FREE)
			{
				//paint in white
				setPointColor(mat, i, j, 255, 255, 255);
			}
			else if (ogrid.getCell(i, j) == CELL_OCCUPIED)
			{
				//paint in black
				setPointColor(mat, i, j, 0, 0, 0);
			}
			else
			{
				//paint in gray
				setPointColor(mat, i, j, 175, 175, 175);
			}
		}
	}

}

void Map::showMap() {
	cv::imshow("View", *inflatedMap);
	cv::waitKey(1);
}

void Map::setPointColor(cv::Mat * matrix, int x, int y, int red, int green, int blue) {
	matrix->at<cv::Vec3b>(x, y)[0] = blue;
	matrix->at<cv::Vec3b>(x, y)[1] = green;
	matrix->at<cv::Vec3b>(x, y)[2] = red;
}

void Map::paintRedPluse(int i, int j) {
	paintRedDot(i, j);
	paintRedDot(i + 1, j);
	paintRedDot(i - 1, j);
	paintRedDot(i, j + 1);
	paintRedDot(i, j - 1);
}

void Map::paintBluePluse(int i, int j) {
	paintBlueDot(i, j);
	paintBlueDot(i + 1, j);
	paintBlueDot(i - 1, j);
	paintBlueDot(i, j + 1);
	paintBlueDot(i, j - 1);
}

void Map::paintGreenPluse(int i, int j) {
	paintGreenDot(i, j);
	paintGreenDot(i + 1, j);
	paintGreenDot(i - 1, j);
	paintGreenDot(i, j + 1);
	paintGreenDot(i, j - 1);
}

void Map::paintRedDot(int i, int j) {
	setPointColor(mat, i, j, 255, 0, 0);
}

void Map::paintBlueDot(int i, int j) {
	setPointColor(mat, i, j, 0, 0, 255);
}
void Map::paintGreenDot(int i, int j) {
	setPointColor(mat, i, j, 0, 255, 0);
}

Map::~Map() {
}
