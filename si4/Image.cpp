#include "stdafx.h"
#include "Image.h"


Image::Image()
{
}

Image::Image(std::string filePath)
{
	init(filePath);
}


Image::~Image()
{
}

std::vector<std::vector<int>> Image::getTraits()
{
	return _traits;
}

std::vector<std::pair<float, float>> Image::getCoords()
{
	return _coords;
}

void Image::init(std::string filePath)
{
	std::ifstream inFile(filePath);
	std::string fileStr((std::istreambuf_iterator<char>(inFile)),
		std::istreambuf_iterator<char>());

	std::vector<std::string> separated;
	boost::split(separated, fileStr, [](char c) {return c == '\n'; });
	inFile.close();

	int traitCount = boost::lexical_cast<int>(separated.at(0));
	int keyPointsCount = boost::lexical_cast<int>(separated.at(1));

	for (int i = 2; i < /*keyPointsCount + 2*/100; i++)
	{
		std::vector<std::string> pointStr;
		boost::split(pointStr, separated.at(i), [](char c) {return c == ' '; });
		
		std::pair<float, float> coords;
		coords.first = boost::lexical_cast<float>(pointStr.at(0));
		coords.second = boost::lexical_cast<float>(pointStr.at(1));
		_coords.push_back(coords);

		std::vector<int> traits;
		for (int j = 5; j < traitCount + 5; j++)
		{
			traits.push_back(boost::lexical_cast<int>(pointStr.at(j)));
		}
		_traits.push_back(traits);
	}
}

std::vector<std::pair<int, int>> Image::nearestNeighbours(Image other)
{
	std::vector<std::pair<int, int>> out;
	std::vector<std::vector<int>> otherTraits = other.getTraits();
	int i = 0;
	BOOST_FOREACH(std::vector<int> v, _traits)
	{
		int bestValue = 10000;
		int bestId = 0;
		int k = 0;
		BOOST_FOREACH(std::vector<int> otherV, otherTraits)
		{
			int currValue = 0;
			for (int j = 0; j < otherV.size(); j++)
			{
				currValue += std::abs(v.at(j) - otherV.at(j));
			}
			if (currValue < bestValue)
			{
				bestValue = currValue;
				bestId = k;
			}
			k++;
		}

		out.push_back(std::pair<int, int>(i, bestId));
		i++;
	}

	return out;
}

std::vector<std::pair<int, int>> Image::keyPointsPairs(Image other)
{
	std::vector<std::pair<int, int>> temp1 = (*this).nearestNeighbours(other);
	std::vector<std::pair<int, int>> temp2 = other.nearestNeighbours(*this);

	std::vector<std::pair<int, int>> out;

	for (int i = 0; i < temp1.size(); i++)
	{
		for (int j = i + 1; j < temp2.size(); j++)
		{
			if (temp1.at(i).first == temp2.at(j).second && temp1.at(i).second == temp2.at(j).first)
			{
				out.push_back(std::pair<int, int>(temp1.at(i)));
			}
		}
	}

	return out;
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Image::coords(Image other)
{
	std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> out;

	std::vector<std::pair<int, int>> keyPointsPairs = (*this).keyPointsPairs(other);

	for (int i = 0; i < keyPointsPairs.size(); i++)
	{
		std::pair<int, int> ids = keyPointsPairs.at(i);

		std::pair<float, float> coords1;
		coords1.first = _coords.at(ids.first).first;
		coords1.second = _coords.at(ids.first).second;

		std::pair<float, float> coords2;
		coords2.first = other.getCoords().at(ids.second).first;
		coords2.second = other.getCoords().at(ids.second).second;

		std::pair<std::pair<float, float>, std::pair<float, float>> elem;
		elem.first = coords1;
		elem.second = coords2;

		out.push_back(elem);
	}
	return out;
}

std::vector<std::pair<int, int>> Image::cohesionAnalysis(std::vector<std::pair<int, int>> keyPointsPairs, int threshold, int neighbourNumber)
{
	std::vector<std::pair<int, int>> out;

	BOOST_FOREACH(auto p, keyPointsPairs)
	{
		std::vector<int> neighbourhood1 = keyPointNeighbourhood(p.first, neighbourNumber);
		std::vector<int> neighbourhood2 = keyPointNeighbourhood(p.second, neighbourNumber);

		int counter = 0;
		BOOST_FOREACH(int i, neighbourhood1)
		{
			neighbourhood2.


			BOOST_FOREACH(int j, neighbourhood2)
			{

			}
		}
	}

	return out;
}

int Image::findPair(int point, std::vector<std::pair<int, int>> keyPointsPairs)
{
	int out = -1;
	BOOST_FOREACH(auto pair, keyPointsPairs)
	{
		if (pair.first == point)
		{
			out = pair.second;
			break;
		}
	}
	return out;
}