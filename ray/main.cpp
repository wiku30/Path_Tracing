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
	// ����һ��ͼƬ����Ϸԭ����    
	Mat img = imread("pic.jpg");
	// ����һ����Ϊ "��Ϸԭ��"����    
	namedWindow("��Ϸԭ��");
	// �ڴ�������ʾ��Ϸԭ��    
	imshow("��Ϸԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	*/
}