#include"APITools.hpp"
int main()
{
	Mat img = imread("cat2.jpg");
	imshow("", img);
	faceplusplusApi facepp;
	facepp.Objectrecognition(img);
	waitKey(0);
	while (true)
	{

	}
	return 0;
}