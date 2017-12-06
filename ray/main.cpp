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

#include "texture.h"

using namespace std;

using namespace cv;

Mat img(401, 401, CV_8UC3);

int main() {

	camera cmr;
	scene scn(cmr);
	//ball b1(vec3(0, 0, 40), 5, color(0,1,1));
	ball b2(vec3(17, 17, 50), 7);
	ball b3(vec3(-17, 17, 50), 7);
	ball b4(vec3(17, -17, 50), 7);
	ball b5(vec3(-17, -17, 50), 7);	

	vec3 A(-30, -30, 70);
	vec3 B(-30, 30, 70);
	vec3 C(30, -30, 70);
	vec3 D(30, 30, 70);
	vec3 E(-30, -30, 10);
	vec3 F(-30, 30, 10);
	vec3 G(30, -30, 10);
	vec3 H(30, 30, 10);

	tex_face t;
	triangle t3(A, B, E, 0, 0, 0.8);
	
	triangle t4(B, E, F, 0, 0, 0.8);
	
	triangle t5(A, C, E, 0,0.9);
	triangle t6(C, E, G, 0,0.9);

	triangle t7(C, D, G, 0, 0, 0.8);
	
	triangle t8(D, G, H, 0, 0, 0.8);
	
	triangle t9(B, D, F, 0,0.9);
	triangle t10(D, F, H, 0,0.9);

	t5.mir_color = color(1, 0.3, 0.3);
	t6.mir_color = color(1, 0.3, 0.3);
	t9.mir_color = color(0.3, 1, 0.3);
	t10.mir_color = color(0.3, 1, 0.3);

	ray r;
	r.start = vec3(0, 0, 0);
	r.direc = vec3(0, 0, 1);
	t.findcross(r);
	cout << t.findcross(r) << endl;


	//scn.add_shape(&b1);
	scn.add_shape(&b2);
	scn.add_shape(&b3);
	scn.add_shape(&b4);
	scn.add_shape(&b5);
	scn.add_shape(&t);
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

	for (int i = 0; i <= 400; i++)
	{
		for (int j = 0; j <= 400; j++)
		{
			img.at<Vec3b>(i, j)[0] = min(sqrt(cmr.pic[i][j].x)*256,255.0);
			img.at<Vec3b>(i, j)[1] = min(sqrt(cmr.pic[i][j].y)*256,255.0);
			img.at<Vec3b>(i, j)[2] = min(sqrt(cmr.pic[i][j].z)*256,255.0);
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