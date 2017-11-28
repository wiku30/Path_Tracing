#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  


#include <iostream>
#include <vector>

#include "types.h"
#include "bezier.h"
#include "ball.h"
#include "triangle.h"

using namespace std;

using namespace cv;

int main() {

	vec3 A(0,0,0), B(1,0,0), C(0,1,0), D(0,0,1);
	triangle T(A, B, C);
	ray i,r;
	i.setstart(0, 0, 1);
	i.setdirec(1, 1, -2);
	r=T.reflect(i);
	cout << r.start << endl << r.direc << endl;
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