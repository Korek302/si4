#pragma once
#include <string>
#include <vector>

class Image
{
public:
	Image();
	Image(std::string filePath);
	~Image();

private:
	std::vector<std::string[]> _keyPoints;
	std::string **as;

	void init(std::string filePath);
	std::vector<std::pair<int, int>> nearestNeighbours(Image other);
	std::vector<std::pair<int, int>> keyPointsPairs(Image other);
};

