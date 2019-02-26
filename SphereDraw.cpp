#include<iostream>
#include<stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <windows.h>
using namespace std;

#define PI 3.14159265358979323846
#define PI2 6.28318530717958647692
#define PTCOT 50
#define DIRCOEF 0.001
#define RESCOEF 0.00
#define VECCOEF 0.00
#define POWCOEF 2

GLsizei width = 600, height = 600;
int uStepsNum = 50, vStepNum = 50, init_number = 0;
double dir_coef = DIRCOEF, res_coef = RESCOEF, vec_coef = VECCOEF, pow_coef = POWCOEF;
double posi_table[PTCOT][4];

int frame_calculate(double posi_table[PTCOT][4]) {
	double new_table[PTCOT][4];
	for (int i = 0; i < init_number; i++) {
		new_table[i][0] = posi_table[i][0];
		new_table[i][1] = posi_table[i][1];
		new_table[i][2] = posi_table[i][2];
		new_table[i][3] = posi_table[i][3];
	}
	for (int i = 0; i < init_number; i++) {
		double force_x = 0, force_y = 0, a_force_x = 0, a_force_y = 0;
		for (int j = 0; j < init_number; j++) {
			if (i != j) {
				//fi=0 - 360 zita=1 - 180
				double lfB = posi_table[i][0] * PI / 180;
				double lzB = posi_table[i][1] * PI / 180;
				double lfA = posi_table[j][0] * PI / 180;
				double lzA = posi_table[j][1] * PI / 180;
				//角度转弧度
				double x_A = sin(lzA) * cos(lfA), y_A = sin(lfA) * sin(lzA), z_A = cos(lzA);
				double x_B = sin(lzB) * cos(lfB), y_B = sin(lfB) * sin(lzB), z_B = cos(lzB);
				//弧度转坐标
				double dis = acos(1 - (pow((x_A - x_B), 2) + pow((y_A - y_B), 2) + pow((z_A - z_B), 2)) / 2);
				double acc = dir_coef * (1 / pow(dis, pow_coef) - 1 / pow((PI2 - dis), pow_coef));
				//dis = distance between a and b on sphere,  acc = c acclaration of point c.
				double cA = y_A * z_B - z_A * y_B;
				double cB = z_A * x_B - x_A * z_B;
				double cC = x_A * y_B - y_A * x_B;
				//法向量的ABC 
				double m1 = 1 - cos(acc);
				double rpx = (2 * cB*cB*m1*x_B + 2 * cC*cC*m1*x_B - 2 * cA*cB*m1*y_B - 2 * cA*cC*m1*z_B - sqrt(pow((-2 * cB*cB*m1*x_B - 2 * cC*cC*m1*x_B + 2 * cA*cB*m1*y_B + 2 * cA*cC*m1*z_B), 2) - 4 * (cB*cB*m1*m1 + cC * cC*m1*m1 - cC * cC*y_B*y_B + 2 * cB*cC*y_B*z_B - cB * cB*z_B*z_B)*(cB*cB*x_B*x_B + cC * cC*x_B*x_B - 2 * cA*cB*x_B*y_B + cA * cA*y_B*y_B + cC * cC*y_B*y_B - 2 * cA*cC*x_B*z_B - 2 * cB*cC*y_B*z_B + cA * cA*z_B*z_B + cB * cB*z_B*z_B))) / (2 * (cB*cB*x_B*x_B + cC * cC*x_B*x_B - 2 * cA*cB*x_B*y_B + cA * cA*y_B*y_B + cC * cC*y_B*y_B - 2 * cA*cC*x_B*z_B - 2 * cB*cC*y_B*z_B + cA * cA*z_B*z_B + cB * cB*z_B*z_B));
				double rpy =, rpz = ;
				
				
				/*double s1 = z_B - cC * y_B / cB, s2 = x_B - cA * y_B / cB, s3 = z_B - cC * x_B / cA, s4 = y_B - cB * x_B / cA;
				double cA2 = pow(s1 / s2, 2) + pow(s3 / s4, 2) + 1;
				double cB2 = -2 * ((m1*s1 / s2) + (m1*s3 / s4));
				double cC2 = pow(m1 / s2, 2) + pow(m1 / s4, 2) - 1;

				double rpz = (-cB2 + sqrt(pow(cB2, 2) - 4 * cA2*cC2)) / (2 * cA2);
				double rpy = (m1 - rpz * s3 )/ s4, rpx = (m1 - rpz * s1) / s2;

				double rnz = (-cB2 - sqrt(pow(cB2, 2) - 4 * cA2*cC2)) / (2 * cA2);
				double rny = (m1 - rnz * s3) / s4, rnx = (m1 - rnz * s1) / s2;*/

				double rpt = acos(rpz), rpf = atan(rpy / rpx), rnt = acos(rnz), rnf = atan(rny / rnx);

				double disp = pow((rpx - x_A), 2) + pow((rpy - y_A), 2) + pow((rpz - z_A), 2);
				double disn = pow((rnx - x_A), 2) + pow((rny - y_A), 2) + pow((rnz - z_A), 2);

				/*double pca = y_A * rpz - z_A * rpy;
				double pcb = z_A * rpx - x_A * rpz;
				double pcc = x_A * rpy - y_A * rpx;
				double nca = y_A * rnz - z_A * rny;
				double ncb = z_A * rnx - x_A * rnz;
				double ncc = x_A * rny - y_A * rnx;*/

				if (disn > disp) {
					//p_point is selected;
					double rwt = rpt - lzB, rwf = rpf - lfB;
					a_force_y = rwt * 180 / PI;
					if (rwf > PI) {
						a_force_x = (rwf - PI2) * 180 / PI;
					}
					else if (rwf<-PI) {
						a_force_x = (PI2 + rwf) * 180 / PI;
					}
					else {
						a_force_x = rwf * 180 / PI;
					}
					//cout << rpx * cA + rpy * cB + rpz * cC << endl;
					//cout << pca << "/" << pcb << "/" << pcc << endl;
					
				}
				else {
					//n_point is selected;
					double rwt = rnt - lzB, rwf = rnf - lfB;
					a_force_y = rwt * 180 / PI;
					if (rwf > PI) {
						a_force_x = (rwf - PI2) * 180 / PI;
					}
					else if (rwf < -PI) {
						a_force_x = (PI2 + rwf) * 180 / PI;
					}
					else {
						a_force_x = rwf * 180 / PI;
					}
					//cout << rnx * cA + rny * cB + rnz * cC << endl;
					//cout << nca << "/" << ncb << "/" << ncc << endl;
				}


				force_x = force_x + a_force_x;
				force_y = force_y + a_force_y;
				//cout << "dis: " << dis << "/ acc: " << acc << endl;
				cout << sqrt(pow(cB2, 2) - 4 * cA2*cC2) << "/" << dis << endl;
				cout << "Vertical axias: "<< cA << ", " << cB << ", " << cC << endl;
			}
		}
		double bisr = sqrt(pow(force_x, 2) + pow(force_y, 2));
		double rx = res_coef * force_x / bisr;
		double ry = res_coef * force_y / bisr;


		if (force_x <= rx && force_x >= -rx) {
			force_x = 0;
		}
		else if (force_x > rx) {
			force_x -= rx;
		}
		else if (force_x < -rx) {
			force_x += rx;
		}

		if (force_y <= ry && force_y >= -ry) {
			force_y = 0;
		}
		else if (force_y > ry) {
			force_y -= ry;
		}
		else if (force_y < -ry) {
			force_y += ry;
		}

		new_table[i][2] = new_table[i][2] + force_x;
		new_table[i][3] = new_table[i][3] + force_y;
		new_table[i][0] += new_table[i][2];
		new_table[i][1] += new_table[i][3];

		if (new_table[i][2] <= vec_coef && new_table[i][2] >= -vec_coef) {
			new_table[i][2] = 0;
		}
		else if (new_table[i][2] > vec_coef) {
			new_table[i][2] -= vec_coef;
		}
		else if (new_table[i][2] < -res_coef) {
			new_table[i][2] += vec_coef;
		}
		if (new_table[i][3] <= vec_coef && new_table[i][3] >= -vec_coef) {
			new_table[i][3] = 0;
		}
		else if (new_table[i][3] > vec_coef) {
			new_table[i][3] -= vec_coef;
		}
		else if (new_table[i][3] < -res_coef) {
			new_table[i][3] += vec_coef;
		}
	}
	for (int i = 0; i < init_number; i++) {
		while (new_table[i][0] < 0) {
			new_table[i][0] = 360 + new_table[i][0];
		}
		while (new_table[i][0] >= 360) {
			new_table[i][0] = new_table[i][0] - 360;
		}
		if (new_table[i][1] < 0) {
			new_table[i][1] = -new_table[i][1];
			new_table[i][0] = -new_table[i][0];
		}
		while (new_table[i][1] > 360) {
			new_table[i][1] -= 360;
		}
		if (new_table[i][1] > 180) {
			new_table[i][1] = 360 - new_table[i][1];
			new_table[i][0] = -new_table[i][0];
		}
	}
	int flag = 1;
	for (int i = 0; i < init_number; i++) {
		for (int j = 2; j < 4; j++) {
			if (new_table[i][j] != 0) {
				flag = 0;
			}
		}
	}
	if (flag) {
		return 1;
	}
	for (int i = 0; i < init_number; i++) {
		for (int j = 0; j < 4; j++) {
			posi_table[i][j] = new_table[i][j];
		}
	}
	return 0;
}

double* coorexc(double p, double q) {
	double ret_value[3];
	double x = sin(PI*q / 180)*cos(PI*p / 180);
	double y = sin(PI*q / 180)*sin(PI*p / 180);
	double z = cos(PI*q / 180);
	ret_value[0] = x;
	ret_value[1] = y;
	ret_value[2] = z;
	return ret_value;
}

class Point
{
public:
	Point() {};
	Point(double a, double b, double c) :x(a), y(b), z(c) {};
public:
	double x;
	double y;
	double z;
};
Point getPoint(double u, double v)
{
	double x = sin(PI*v)*cos(PI2*u);
	double y = sin(PI*v)*sin(PI2*u);
	double z = cos(PI*v);
	return Point(x, y, z);
}
void drawWire()
{
	double ustep = 1 / (double)uStepsNum, vstep = 1 / (double)vStepNum;
	double u = 0, v = 0;
	for (int i = 0; i < uStepsNum; i++)
	{
		glBegin(GL_LINE_LOOP);
		Point a = getPoint(0, 0);
		glVertex3d(a.x, a.y, a.z);
		Point b = getPoint(u, vstep);
		glVertex3d(b.x, b.y, b.z);
		Point c = getPoint(u + ustep, vstep);
		glVertex3d(c.x, c.y, c.z);
		u += ustep;
		glEnd();
	}

	u = 0, v = vstep;
	for (int i = 1; i < vStepNum - 1; i++)
	{
		for (int j = 0; j < uStepsNum; j++)
		{
			glBegin(GL_LINE_LOOP);
			Point a = getPoint(u, v);
			Point b = getPoint(u + ustep, v);
			Point c = getPoint(u + ustep, v + vstep);
			Point d = getPoint(u, v + vstep);
			glVertex3d(a.x, a.y, a.z);
			glVertex3d(b.x, b.y, b.z);
			glVertex3d(c.x, c.y, c.z);
			glVertex3d(d.x, d.y, d.z);
			u += ustep;
			glEnd();
		}
		v += vstep;
	}

	u = 0;
	for (int i = 0; i < uStepsNum; i++)
	{
		glBegin(GL_LINE_LOOP);
		Point a = getPoint(0, 1);
		Point b = getPoint(u, 1 - vstep);
		Point c = getPoint(u + ustep, 1 - vstep);
		glVertex3d(a.x, a.y, a.z);
		glVertex3d(b.x, b.y, b.z);
		glVertex3d(c.x, c.y, c.z);
		glEnd();
	}
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat light_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.2f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 0.2f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}


int ang = 60, con = 0;

void displayFunc()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glRotated(30, 1, 0, 0);
	glRotated(ang, 0, 1, 0);
	glRotated(270, 0, 0, 1);
	drawWire();
	int con = frame_calculate(posi_table);
	cout << "(" << posi_table[0][0] << "," << posi_table[0][1] << ") (" << posi_table[1][0] << "," << posi_table[1][1] << ")" << endl;
	for (int i = 0; i < init_number; i++) {
		glPushMatrix();
		double* coor = coorexc(posi_table[i][0], posi_table[i][1]);
		glTranslatef(coor[0], coor[1], coor[2]);
		glColor3f(0.0, 1.0, 0.0);
		glutSolidSphere(0.02, 30, 30);
		glPopMatrix();
	}
	glutSwapBuffers();
	ang += 1;
	//Sleep(500);
}

int main(int argc, char* argv[]) {
	cout << "Enter the number of points: " << endl;
	cin >> init_number;
	int counter = 0, out = 1;
	srand(time(NULL));
	while (out) {
		out = 0;
		for (int i = 0; i < init_number; i++) {
			posi_table[i][0] = rand() % 359;
			posi_table[i][1] = rand() % 179;
			posi_table[i][2] = 0;
			posi_table[i][3] = 0;
		}
		for (int i = 0; i < init_number; i++) {
			for (int j = 0; j < init_number; j++) {
				if (i != j) {
					if (posi_table[i][0] == posi_table[j][0] || posi_table[i][1] == posi_table[j][1]) {
						out = 1;
					}
				}
			}
		}
	}
	for (int i = 0; i < init_number; i++) {
		cout << "(" << posi_table[i][0] << "," << posi_table[i][1] << ") ";
	}
	cout << "\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Sphere");
	init();
	glutDisplayFunc(displayFunc);
	glutIdleFunc(displayFunc);
	glutMainLoop();

	return 0;
}
