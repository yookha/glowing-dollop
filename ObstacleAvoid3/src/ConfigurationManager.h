/*
 * ConfigurationManager.h
 *
 *  Created on: Jul 12, 2017
 *      Author: user
 */

#ifndef SRC_CONFIGURATIONMANAGER_H_
#define SRC_CONFIGURATIONMANAGER_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "RobotStructs.h"

using namespace std;

class ConfigurationManager {
public:
	ConfigurationManager();

	Location getStartPoint();
	Location getEndPoint();
	RobotSize getRobotSize();
	double getResulution();

private:
	vector<string> getValueAsString(string key);
	vector<string> splitStringByWhitespace(string value);
};

#endif /* SRC_CONFIGURATIONMANAGER_H_ */
