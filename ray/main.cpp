
#define DEBUG 0
//if 0, trigger multi-thread automatically

//#define BEZIER_TEST

#define THREADS 8

#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <cmath>
#include <fstream>
#include <windows.h>
#include <vector>
#include <ctime>
#include <iomanip>

#include "types.h"

#include "bezier.h"
#include "ball.h"
#include "triangle.h"
#include "camera.h"
#include "scene.h"
#include "texture.h"

using namespace std;
using namespace cv;





Mat img(RES, RES, CV_8UC3);

int main(int argc, char** argv) // argv[1]: thread_id    argv[2]: total number
{

#ifdef BEZIER_TEST

	bezier bez;
	bez.genMesh();
#else
	int tick = clock();
	
	bool multi_flag = 0;
	int threads = 1;
	int threadID;
	
	char name[] = "result/sub0.txt";
	char flag[] = "result/0.flag";	//created when finished

	if (argc >= 3)
	{
		multi_flag = 1;
		threads = atoi(argv[2]);
		threadID = atoi(argv[1]);
		srand(threadID * 777);

		name[10] = argv[1][0];
		flag[7] = argv[1][0];
		remove(name);
		remove(flag);
	}
	else if (!DEBUG)
	{
		char name[200];
		for (int i = 1; i <= THREADS; i++)
		{
			char cmd[] = " 0 0";
			cmd[1] += i;
			cmd[3] += THREADS;
			strncpy(name, argv[0], 190);
			strncat(name, cmd, 190);
			WinExec(name, SW_HIDE);
		}
		return 0;
	}

	camera cmr;
	scene scn(cmr);
	ball b1(vec3(-16, -11, 53), 8, 0, 0.08, 0.00, 1, 1, 0.92);

	ball b2(vec3(24, -15, 44), 6, 0, 0.1, 0.9, 1, color(0, 0, 1));

	ball light(vec3(-70, 0, 40), 41, 30, 0, 0);
	/*
	vec3 A(-30, -30, 70);
	vec3 B(-30, 30, 70);
	vec3 C(30, -30, 70);
	vec3 D(30, 30, 70);
	vec3 E(-30, -30, -15);
	vec3 F(-30, 30, -15);
	vec3 G(30, -30, -15);
	vec3 H(30, 30, -15);
	*/

	vec3 bot1(30, -100000, -100000);
	vec3 bot2(30, -100000, 100000);
	vec3 bot3(30, 200000, 0);

	vec3 left1(-100000, -30, -100000);
	vec3 left2(-100000, -30, 100000);
	vec3 left3(200000, -30, 0);

	vec3 top1(-30, -100000, -100000);
	vec3 top2(-30, -100000, 100000);
	vec3 top3(-30, 200000, 0);

	vec3 back1(-100000, -100000, -15);
	vec3 back2(100000, -100000, -15);
	vec3 back3(0, 200000, -15);

	vec3 P(23, -2, 50);
	vec3 Q(23, 10, 40);
	vec3 R(23, 22, 50);
	vec3 S(23, 10, 60);
	vec3 T(10, 10, 50);

	tex_face right;
	tex_face2 front;

	triangle s1(P, Q, R, 0, 0, 0);
	triangle s2(Q, R, S, 0, 0, 0);
	triangle s3(P, Q, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));
	triangle s4(Q, R, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));
	triangle s5(R, S, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));
	triangle s6(S, P, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));



	triangle top(top1, top2, top3, 0, 0, 0.9, 1, 1);
	
	//floor 
	triangle bot(bot1, bot2, bot3, 0, 0, 0.25, 1, color(1, 0.5, 0.7));
	
	//left mirror
	triangle left(left1, left2, left3, 0, 0.8, 0.16);

	triangle back(back1, back2, back3, 0, 0, 0.9);

	


	ray r;
	r.start = vec3(0, 0, 0);
	r.direc = vec3(0, 0, 1);
	/*
	for(int i=1; i<10; i++)
		cout << front.diffuse(r).start << "   " << front.diffuse(r).direc << endl;

	int xx;
	cin >> xx;
	*/

	scn.add_shape(&b1);
	scn.add_shape(&b2);
	scn.add_shape(&light);


	scn.add_shape(&s1);
	scn.add_shape(&s2);
	scn.add_shape(&s3);
	scn.add_shape(&s4);
	scn.add_shape(&s5);
	scn.add_shape(&s6);

	scn.add_shape(&right);
	scn.add_shape(&front);
	scn.add_shape(&top);

	scn.add_shape(&bot);

	scn.add_shape(&left);

	scn.add_shape(&back);

	scn.shoot();
	cmr.pic;
	if (!multi_flag)
	{
		for (int i = 0; i < RES; i++)
		{
			for (int j = 0; j < RES; j++)
			{
				img.at<Vec3b>(i, j)[0] = min(sqrt(cmr.pic[i][j].x) * 256, 255.0);
				img.at<Vec3b>(i, j)[1] = min(sqrt(cmr.pic[i][j].y) * 256, 255.0);
				img.at<Vec3b>(i, j)[2] = min(sqrt(cmr.pic[i][j].z) * 256, 255.0);
			}
		}
		imshow("”Œœ∑‘≠ª≠", img);
		imwrite("my.bmp", img);
	}
	else
	{
		ofstream ouf(name);
		//ouf << RES << " " << RES << endl;
		for (int i = 0; i < RES; i++)
		{
			for (int j = 0; j < RES; j++)
			{
				ouf << cmr.pic[i][j].x << " "
					<< cmr.pic[i][j].y << " "
					<< cmr.pic[i][j].z << " "
					<< endl;
			}
		}
		ouf.close();
		ofstream flg(flag);
		flg.close();
		for (int i = 1; i <= threads; i++)
		{
			flag[7] = '0' + i;
			ifstream test(flag);
			if (!test)	//not the last
			{
				cout << "part " << threadID << "completed." << endl;
				return 0;
			}
		}

		//merging
		int tock = clock();
		cout << fixed << setprecision(1);
		cout << "Rendering completed. Rendering time: " 
			<< (tock - tick)*(1.0 / 1000 / 60) << "minutes" << endl;
		cout << "start merging..." << endl;
		ifstream sub[THREADS];
		for (int k = 0; k < threads; k++)
		{
			name[10] = k + '1';
			sub[k].open(name);
		}
		for (int i = 0; i < RES; i++)
		{
			for (int j = 0; j < RES; j++)
			{
				color pix(0);
				color tmp(0);
				for (int k = 0; k < threads; k++)
				{
					sub[k] >> tmp.x >> tmp.y >> tmp.z;
					pix += tmp;
				}
				pix /= threads;
				img.at<Vec3b>(i, j)[0] = min(sqrt(pix.x) * 256, 255.0);
				img.at<Vec3b>(i, j)[1] = min(sqrt(pix.y) * 256, 255.0);
				img.at<Vec3b>(i, j)[2] = min(sqrt(pix.z) * 256, 255.0);
			}
		}
		for (int k = 0; k < threads; k++)
		{
			name[10] = k + '1';
			sub[k].close();
		}
		imwrite("result/res.bmp", img);
		int tt = clock();
		cout << "Merging completed." << endl << setprecision(0)
			<< "Merging time: " << (tt - tock)*(1.0 / 1000) << " seconds"<<endl;
#if !HI_RES
		double pred = (tock - tick) * 20 + (tt - tock) * 6.25;
		cout << "Predicted running time for full resolution: " <<
			pred * (1.0 / 60 / 1000) << " minutes" << endl;
#endif
	}
#endif
	return 0;
}