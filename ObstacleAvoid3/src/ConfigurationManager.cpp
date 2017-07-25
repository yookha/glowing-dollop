/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: user
 */

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager() {

}

Location ConfigurationManager::getStartPoint() {
	vector<string> values = getValueAsString("start");

	Location startPoint;

	startPoint.x = atoi(values.at(1).c_str());
	startPoint.y = atoi(values.at(2).c_str());

	return startPoint;
}

Location ConfigurationManager::getEndPoint() {
	vector<string> values = getValueAsString("end");

	Location startPoint;

	startPoint.x = atoi(values.at(1).c_str());
	startPoint.y = atoi(values.at(2).c_str());

	return startPoint;
}

RobotSize ConfigurationManager::getRobotSize() {
	vector<string> values = getValueAsString("size");
	RobotSize size;

	size.height = atoi(values.at(1).c_str());
	size.width = atoi(values.at(2).c_str());

	return size;
}

double ConfigurationManager::getResulution() {
	vector<string> values = getValueAsString("resulation");

	return atof(values.at(1).c_str());
}

vector<string> ConfigurationManager::getValueAsString(string key) {
	std::ifstream file("robotSettings.txt");
	std::string str;
	while (std::getline(file, str)) {
		vector<string> result = splitStringByWhitespace(str);

		if (key.compare(result.at(0)) == 0) {
			return result;
		}
	}

	vector<string> result;
	return result;
}

vector<string> ConfigurationManager::splitStringByWhitespace(string value) {
	vector<string> result;
	istringstream iss(value);
	for (string s; iss >> s;)
		result.push_back(s);

	return result;
}
