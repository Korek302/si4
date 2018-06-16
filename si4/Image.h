#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <cmath>

class Image
{
public:
	Image();
	Image(std::string filePath);
	~Image();

	std::vector<std::vector<int>> getTraits();
	std::vector<std::pair<float, float>> getCoords();

	std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> coords(Image other);
private:
	//std::vector<std::vector<std::string>> _keyPoints;
	std::vector<std::pair<float, float>> _coords;
	std::vector<std::vector<int>> _traits;
	std::vector<std::pair<int, int>> nearestNeighbours(Image other);
	std::vector<std::pair<int, int>> keyPointsPairs(Image other);

	std::vector<int> keyPointNeighbourhood(int pointId, int n);
	std::vector<std::pair<int, int>> cohesionAnalysis(std::vector<std::pair<int, int>> keyPointsPairs, int threshold, int neighbourNumber);

	void init(std::string filePath);
};

