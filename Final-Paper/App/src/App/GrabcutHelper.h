#pragma once
#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>


using namespace std;
using namespace cv;

class GrabcutHelper
{
public:
	void reset();
	void setImage(const Mat& _image, const string& _winName);
	void setTransformedImage();
	void setRect();
	int doGrabcut();
	int getIterCount() const {
		return iterCount;
	}
	Mat getConvertedImage();

private:
	void setRectInMask();

	const string* winName;
	const Mat* image;
	Mat mask;
	Mat bgdModel, fgdModel;
	Mat convertedImage;

	bool isInitialized;
	bool rectState;

	Rect rect;
	int iterCount;
};

bool R1(int R, int G, int B);
bool R2(float Y, float Cr, float Cb);
bool R3(float H, float S, float V);
Mat GetSkin(Mat const &src);