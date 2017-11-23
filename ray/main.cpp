#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

#include "types.h"
#include "bezier.h"
#include <iostream>
#include <vector>

using namespace std;

using namespace cv;

int main() {
	vec3 a(0, 0, 0);
	vec3 b(0, 1, 0);
	vec3 c(1, 1, 0);
	vector<vec3> bez;
	bez.push_back(a);
	bez.push_back(b);
	bez.push_back(c);
	cout << findPoint(bez,0) << endl;
	cout << findPoint(bez, 0.5) << endl;
	cout << findPoint(bez, 1) << endl;
	/*
	// 读入一张图片（游戏原画）    
	Mat img = imread("pic.jpg");
	// 创建一个名为 "游戏原画"窗口    
	namedWindow("游戏原画");
	// 在窗口中显示游戏原画    
	imshow("游戏原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	*/
}