#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include <set>
#include <math.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include "Node.h"
#include "Constants.h"
#include <list>

using namespace std;

class PathPlanner
{
public:
	double calculateDistance(Node* source, Node* target);
	void initializeHuristicValues(vector<vector<Node*> >  matrix, Node* goalNode);
	bool isNodeInList(set<Node>* list, int rowIndex, int colIndex);
	void handleNeighbors(vector<vector<Node*> >  map, Node* currNode, Node* goalNode,
			set<Node*>* openList, set<Node*>* closedList);
	std::list<Node* > markWaypoints(Node * startNode, Node * currNode);
	void findShortestPath(vector<vector<Node*> >  matrix, Node* startNode, Node* goalNode);
	vector<vector<Node*> > getNodeMap(cv::Mat *map);

private:
	Node* getMinimalFNode(set<Node*>* openList);
};

#endif  PATHPLANNER_H_
