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