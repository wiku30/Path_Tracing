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


#define DEBUG 0
//if 0, trigger multi-thread automatically

#define THREADS 8


Mat img(RES+1, RES+1, CV_8UC3);

int main(int argc, char** argv) // argv[1]: thread_id    argv[2]: total number
{
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
	ball b1(vec3(-15, -12, 50), 10, 0, 0.35, 0, 1, 1, 0.65);	

	vec3 A(-30, -30, 70);
	vec3 B(-30, 30, 70);
	vec3 C(30, -30, 70);
	vec3 D(30, 30, 70);
	vec3 E(-30, -30, -15);
	vec3 F(-30, 30, -15);
	vec3 G(30, -30, -15);
	vec3 H(30, 30, -15);

	vec3 sky1(-200, -100000, -100000);
	vec3 sky2(-200, -100000, 100000);
	vec3 sky3(-200, 200000, 0);

	vec3 P(23, -7, 50);
	vec3 Q(23, 10, 40);
	vec3 R(23, 27, 50);
	vec3 S(23, 10, 60);
	vec3 T(7, 10, 50);

	tex_face left;
	tex_face2 front;

	triangle s1(P, Q, R, 0, 0, 0);
	triangle s2(Q, R, S, 0, 0, 0);
	triangle s3(P, Q, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));
	triangle s4(Q, R, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));
	triangle s5(R, S, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));
	triangle s6(S, P, T, 0, 0.63, 0.27, color(0.7, 1, 0.7), color(0.7, 1, 0.7));

	//front
	triangle t1(A, B, C, 0, 0, 0.9, 1, color(0, 0, 1));
	triangle t2(B, C, D, 0, 0, 0.9, 1, color(0, 0, 1));

	triangle sky(sky1, sky2, sky3, color(1.5,1.5,1.5), 0, 0);
	
	//covered by texture
	triangle t5(A, C, E, 0, 0, 0.9, 1, color(0, 0, 1));
	triangle t6(C, E, G, 0, 0, 0.9, 1, color(0, 0, 1));

	//floor 
	triangle t7(C, D, G, 0, 0, 0.25, 1, color(1, 0.5, 0.7));
	triangle t8(D, G, H, 0, 0, 0.25, 1, color(1, 0.5, 0.7));
	
	//right mirror
	triangle t9(B, D, F, 0, 0.75, 0.15);
	triangle t10(D, F, H, 0, 0.75, 0.15);

	triangle t11(E, F, G, 0, 0, 0.9);
	triangle t12(F, G, H, 0, 0, 0.9);


	ray r;
	r.start = vec3(0, 0, 0);
	r.direc = vec3(0, 0, 1);


	scn.add_shape(&b1);
	//scn.add_shape(&b2);


	scn.add_shape(&s1);
	scn.add_shape(&s2);
	scn.add_shape(&s3);
	scn.add_shape(&s4);
	scn.add_shape(&s5);
	scn.add_shape(&s6);

	scn.add_shape(&left);
	scn.add_shape(&front);

	scn.add_shape(&t1);
	scn.add_shape(&t2);
	scn.add_shape(&sky);
	scn.add_shape(&t5);
	scn.add_shape(&t6);
	scn.add_shape(&t7);
	scn.add_shape(&t8);
	scn.add_shape(&t9);
	scn.add_shape(&t10);
	scn.add_shape(&t11);
	scn.add_shape(&t12);

	scn.shoot();
	cmr.pic;
	if (!multi_flag)
	{
		for (int i = 0; i <= RES; i++)
		{
			for (int j = 0; j <= RES; j++)
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
		for (int i = 0; i <= RES; i++)
		{
			for (int j = 0; j <= RES; j++)
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
		cout << "start merging..." << endl;
		ifstream sub[THREADS];
		for (int k = 0; k < threads; k++)
		{
			name[10] = k + '1';
			sub[k].open(name);
		}
		for (int i = 0; i <= RES; i++)
		{
			for (int j = 0; j <= RES; j++)
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
		cout << "Merging completed." << endl << fixed << setprecision(1)
			<< "Time elapsed: " << (clock() - tick)*(1.0 / 1000 / 60) << " minutes";
	}

	return 0;
}