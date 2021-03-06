// si4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Image.h"
#include <iostream>

int main()
{
	Image im1 = Image("res\\img1.png.haraff.sift");
	Image im2 = Image("res\\img2.png.haraff.sift");
	
	std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> coords = im1.coords(im2);

	/*
	for (int i = 0; i < keyPointsPairs.size(); i++)
	{
		std::pair<int, int> p = keyPointsPairs.at(i);
		std::cout << p.first << "    " << p.second << std::endl;
	}
	*/

	cv::Mat3b img1 = cv::imread("res\\img1.png");
	cv::Mat3b img2 = cv::imread("res\\img2.png");

	int rows = cv::max(img1.rows, img2.rows);
	int cols = img1.cols + img2.cols;

	cv::Mat3b res(rows, cols, cv::Vec3b(0, 0, 0));

	img1.copyTo(res(cv::Rect(0, 0, img1.cols, img1.rows)));
	img2.copyTo(res(cv::Rect(img1.cols, 0, img2.cols, img2.rows)));

	for (int i = 0; i < coords.size(); i++)
	{
		cv::line(res, cv::Point(coords.at(i).first.first, coords.at(i).first.second), 
			cv::Point(coords.at(i).second.first + (cols / 2), coords.at(i).second.second), cv::Scalar(255), 1, 4, 0);
	}


	//cv::line(res, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255), 1, 4, 0);

	imshow("Img 1", img1);
	imshow("Img 2", img2);
	imshow("Result", res);
	cv::waitKey();
    return 0;
}