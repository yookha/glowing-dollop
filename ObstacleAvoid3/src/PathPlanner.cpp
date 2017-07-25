#include "PathPlanner.h"

void PathPlanner::findShortestPath(vector<vector<Node*> >  matrix, Node* startNode, Node* goalNode)
{
	set<Node*> openList;
	set<Node*> closedList;
	Node* currNode;

	initializeHuristicValues(matrix, goalNode);

	closedList.insert(startNode);

	startNode->setIsInClosedList(true);

	handleNeighbors(matrix, startNode, goalNode, &openList, &closedList);

	while(!openList.empty())
	{
		currNode = getMinimalFNode(&openList);

		openList.erase(currNode);
		currNode->setIsInOpenList(false);
		closedList.insert(currNode);
		currNode->setIsInClosedList(true);

		handleNeighbors(matrix, currNode, goalNode, &openList, &closedList);
	}
}

vector<vector<Node*> > PathPlanner::getNodeMap(cv::Mat *map)
{
	vector<vector<Node*> > matrix(map->cols, vector<Node*>(map->rows));

	for(int col = 0; col < map->cols; col++)
	{
		for(int row = 0; row < map->rows; row++)
		{
			bool isObstacle = map->at<cv::Vec3b>(col, row)[0] == 0;
			Node * node = new Node(col, row, isObstacle);

			matrix.at(row).at(col) = node;
		}
	}

	return matrix;
}

void PathPlanner::initializeHuristicValues(vector<vector<Node*> >  matrix, Node* goalNode)
{
	for (int colIndex = 0; colIndex < matrix[0].size(); colIndex++)
	{
		for (int rowIndex = 0; rowIndex < matrix.size(); rowIndex++)
		{
			Node* currNode = matrix.at(rowIndex).at(colIndex);

			if (!currNode->getIsObstacle())
			{
				currNode->setH(calculateDistance(currNode, goalNode));
			}
		}
	}
}

double PathPlanner::calculateDistance(Node* source, Node* target)
{
	return sqrt(pow(source->getX() - target->getX(), 2) + pow(source->getY() - target->getY(), 2));
}

void PathPlanner::handleNeighbors(vector<vector<Node*> >  map, Node* currNode, Node* goalNode,
		set<Node*>* openList, set<Node*>* closedList)
{
	for (int colIndex = currNode->getX() - 1; colIndex <= currNode->getX() + 1; colIndex++)
	{
		for (int rowIndex = currNode->getY() - 1; rowIndex <= currNode->getY() + 1; rowIndex++)
		{
			Node* currNeighbor = map.at(rowIndex).at(colIndex);

			// Checks if we're out of bounds and if the current neighbor is not an obstacle
			if (colIndex >= 0 && rowIndex >= 0 &&
				colIndex < map.size() && rowIndex < map.at(0).size() &&
				!currNeighbor->getIsObstacle())
			{
				// Makes sure the current node is not scanned
				if (colIndex != currNode->getX() || rowIndex != currNode->getY())
				{
					// Checks if the current neighbor is in the closed list
					if (!currNeighbor->getIsInClosedList())
					{
						double tempGCost =
							calculateDistance(currNode, currNeighbor) + currNode->getG();

						// Checks if the current neighbor is already in the open list
						if (!currNeighbor->getIsInOpenList())
						{
							currNeighbor->setG(tempGCost);
							currNeighbor->setF(currNeighbor->getH() + tempGCost);
							currNeighbor->setParent(currNode);

							// Checking if we have reached the goal
							if (goalNode->getX() == colIndex && goalNode->getY() == rowIndex)
							{
								openList->clear();
								return;
							}

							// Adding the node to the open list for the first time
							openList->insert(currNeighbor);
							currNeighbor->setIsInOpenList(true);
						}
						// The node was already in the open list, check if we found a shorter path
						else
						{
							if (tempGCost < currNeighbor->getG())
							{
								currNeighbor->setG(tempGCost);
								currNeighbor->setF(currNeighbor->getH() + tempGCost);
								currNeighbor->setParent(currNode);
							}
						}
					}
				}
			}
		}
	}
}

Node* PathPlanner::getMinimalFNode(set<Node*>* openList)
{
	Node* minNode = *(openList->begin());
	Node* currNode;

	for (set<Node*>::iterator iter = openList->begin(); iter != openList->end(); iter++)
	{
		currNode = *iter;

		if (currNode->getF() < minNode->getF())
		{
			minNode = currNode;
		}
	}

	return minNode;
}

std::list<Node *> PathPlanner::markWaypoints(Node * startNode, Node * currNode)
{
	std::list<Node* > waypoints;

	while(currNode->getX() != startNode->getX() || currNode->getY() != startNode->getY())
		{
			currNode->setIsWaypoint(true);
			waypoints.push_back(currNode);

			currNode = currNode->getParent();

			for (int skipIndex = 0; skipIndex < WAYPOINTS_SKIP_NUM; skipIndex++)
			{
				if (currNode->getParent() != NULL)
				{
					currNode = currNode->getParent();
				}
			}
		}

		return waypoints;
}
