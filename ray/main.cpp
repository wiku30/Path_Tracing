#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <cmath>


#include <iostream>
#include <vector>

#include "types.h"
#include "bezier.h"
#include "ball.h"
#include "triangle.h"
#include "camera.h"
#include "scene.h"
using namespace std;

using namespace cv;

int main() {

	camera cmr;
	scene scn(cmr);
	ball b1(vec3(0, 0, 60), 7, 0);
	ball b2(vec3(20, 0, 50), 7, 0);
	ball b3(vec3(-20, 0, 50), 7, 0.5);
	ball b4(vec3(0, 20, 50), 7, 0);
	ball b5(vec3(0, -20, 50), 7, 0.5);

	vec3 A(-30, -30, 70);
	vec3 B(-30, 30, 70);
	vec3 C(30, -30, 70);
	vec3 D(30, 30, 70);
	vec3 E(-30, -30, 10);
	vec3 F(-30, 30, 10);
	vec3 G(30, -30, 10);
	vec3 H(30, 30, 10);

	triangle t1(A, B, C);
	triangle t2(B, C, D);
	triangle t3(A, B, E);
	triangle t4(B, E, F);
	triangle t5(A, C, E);
	triangle t6(C, E, G);
	triangle t7(C, D, G);
	triangle t8(D, G, H);
	triangle t9(B, D, F);
	triangle t10(D, F, H);

	ray r;

	scn.add_shape(&b1);
	scn.add_shape(&b2);
	scn.add_shape(&b3);
	scn.add_shape(&b4);
	scn.add_shape(&b5);
	scn.add_shape(&t1);
	scn.add_shape(&t2);
	scn.add_shape(&t3);
	scn.add_shape(&t4);
	scn.add_shape(&t5);
	scn.add_shape(&t6);
	scn.add_shape(&t7);
	scn.add_shape(&t8);
	scn.add_shape(&t9);
	scn.add_shape(&t10);
	scn.shoot();
	cmr.pic;
	Mat img(51,51,CV_8UC3);
	for (int i = 0; i <= 50; i++)
	{
		for (int j = 0; j <= 50; j++)
		{
			img.at<Vec3b>(i, j)[0] = min(sqrt(cmr.pic[i][j].x)*2560,255.0);
			img.at<Vec3b>(i, j)[1] = min(sqrt(cmr.pic[i][j].y)*2560,255.0);
			img.at<Vec3b>(i, j)[2] = min(sqrt(cmr.pic[i][j].z)*2560,255.0);
		}
	}
	imshow("游戏原画", img);
	imwrite("my.bmp", img);
	cvWaitKey(6000);
	return 0;
	/*
	// 读入一张图片（游戏原画）    
	Mat img = imread("pic.jpg");
	// 创建一个名为 "游戏原画"窗口    
	namedWindow("游戏原画");
	// 在窗口中显示游戏原画    
	imshow("游戏原画", img);
	// 等待6000 ms后窗口自动关闭    
	
	*/
}