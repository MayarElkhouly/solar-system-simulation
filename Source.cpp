#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>   
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "GL/glut.h"


int Height;
int Width;
bool one = false;
float tx = 0.0;
float x_rotation = 0.0;
float worldX = 15.0;
float worldY = 0.0;
float scaleFactor = 0.6;
bool animate = false;
float first = 1;
float second = 1;
float angle_x = -90.0f;   //to turn on x put it =0  //-90
float angleY = 0.0f;
float angleZ = 0.0f;
float offset = -10;
float x_value = 0;
//float venus_rotation = 360.0 / (225.0 * 24.0 * 60.0 * 60.0 * frame_rate);
//float mercury_rotation = 360.0 / (88.0 * 24.0 * 60.0 * 60.0 * frame_rate);
GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = 10.0f;
GLfloat PX = 0.0f;
GLfloat PY = 0.0f;
GLfloat PZ = 0.0f;

float wS = Width*0.75;
float hS = Height*.75;
static unsigned int spacecraft; // Display lists base index.





//Function to draw the orbits around the sun
void drawOrbit(float radius) {
	glBegin(GL_LINE_STRIP);
	for (float i = 0; i < 360.0; i += 0.1) {
		float x = radius * cos(i * 3.1415926535 / 180);
		float y = radius * sin(i * 3.1415926535 / 180);
		//float z = radius * tan(i * 3.1415926535 / 180);
		glVertex3f(x, y,1);
	}
	glEnd();
}


void Setup() 
{
	
	srand(time(0));
	//Parameter handling
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//to draw spacecraft
    spacecraft = glGenLists(1);
	glNewList(spacecraft, GL_COMPILE);
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0); 
	glColor3f(1.0f, 0.41f, 0.71f);
	glutWireCone(2.0, 3.0, 10, 10);
	glPopMatrix();
	glEndList();
}




void drawScene() {

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////  view port 1  ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, Width, Height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);


	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, PX, PY, 0.0, 0.0, 1.0, 0.0);



	if (!animate) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glColor3f(1, 1, 1);
		glTranslatef(-8, 50, 0.0);
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLUquadricObj* planet;
	planet = gluNewQuadric();
	gluQuadricDrawStyle(planet, GLU_FILL);
	gluDeleteQuadric(planet);

	glDisable(GL_LIGHTING);


	


	//to edit all solar System
	glPushMatrix();
	glTranslatef(x_value, 0.0, -400);
	glTranslatef(0.0, 0.0, offset);
	glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
	glCallList(spacecraft);


	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glLineWidth(0.1);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	drawOrbit(20);
	drawOrbit(40);
	drawOrbit(60);
	drawOrbit(80);
	drawOrbit(100);
	drawOrbit(125);
	drawOrbit(165);
	drawOrbit(200);
	drawOrbit(225);
	glPopMatrix();

	//drawing sun
	glPushMatrix();
	glColor3f(0.8, 0.498039, 0.196078);
	gluSphere(planet, 20, 36, 18);
	glColor3f(1, 1, 0);
	glEnable(GL_BLEND);
	glBlendFunc(first, second);
	gluSphere(planet, 30, 36, 18);
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0, 0.0, 0.0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);


	//mercury
	glPushMatrix();
	glRotatef(x_rotation * 1.6, 0, 1, 0);
	glTranslatef(40, 0, -10.0);
	glColor3ub(204, 126, 56);
	gluSphere(planet, 4, 36, 18);
	glPopMatrix();

	//venus
	glPushMatrix();
	glRotatef(x_rotation * 1.17, 0, 1, 0);
	glTranslatef(60, 0, -10.0);
	glColor3ub(215, 122, 98);
	gluSphere(planet, 5.5, 36, 18);
	glPopMatrix();

	//Earth
	glPushMatrix();
	glRotatef(x_rotation, 0, 1, 0);
	glTranslatef(80, 0, -10.0);
	glColor3f(0.275f, 0.51f, 0.71f);
	gluSphere(planet, 6 , 36, 18);

	//moon
	glRotatef(x_rotation * 70, 0.0, 1.0, 0.0);
	glTranslatef(2, 0, -10.0);
	glColor3f(0.75f, 0.75f, 0.75f);
	gluSphere(planet, 3, 36, 18);

	glPopMatrix();


	//mars
	glPushMatrix();
	glRotatef(x_rotation * 0.8, 0, 1, 0);
	glTranslatef(100, 0, -10.0);
	glColor3ub(198, 62, 60);
	gluSphere(planet, 4.5, 36, 18);
	glPopMatrix();

	//Jupiter
	glPushMatrix();
	glRotatef(x_rotation * 0.438, 0, 1, 0);
	glTranslatef(125, 0, -10.0);
	glColor3ub(231, 203, 191);
	gluSphere(planet, 16, 36, 18);
	glPopMatrix();

	//saturn
	glPushMatrix();
	glRotatef(x_rotation * 0.325, 0, 1, 0);
	glTranslatef(165, 0, -10.0);
	glColor3f(0.8f, 0.6f, 0.5f);
	gluSphere(planet, 15, 36, 18);
	glColor3f(0.8f, 0.6f, 0.5f);
	glLineWidth(7);
	drawOrbit(18);
	glPopMatrix();

	//uranus
	glPushMatrix();
	glRotatef(x_rotation * 0.228, 0, 1, 0);
	glTranslatef(200, 0, -10.0);
	glColor3ub(36, 97, 253);
	gluSphere(planet, 9, 36, 18);
	glPopMatrix();

	//Neptune
	glPushMatrix();
	glRotatef(x_rotation * 0.182, 0, 1, 0);
	glTranslatef(225, 0, -10.0);
	glColor3ub(153, 223, 254);
	gluSphere(planet, 8.8, 36, 18);
	glPopMatrix();





	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////  view port 2  ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	glEnable(GL_SCISSOR_TEST);
	glScissor(Width * 0.7, 35, Width / 3, Height / 3.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
	glViewport(Width * 0.65, 35, Width / 2.5 , Height / 3.5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0 , 0.0 , 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	if (!animate) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glColor3f(1, 1, 1);
		glTranslatef(-8, 50, 0.0);
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	planet = gluNewQuadric();
	gluQuadricDrawStyle(planet, GLU_FILL);
	gluDeleteQuadric(planet);

	glDisable(GL_LIGHTING);

	//for space craft
	glPushMatrix();
	glTranslatef(cameraX, cameraY, offset-300);
	glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
	glCallList(spacecraft);
	glPopMatrix();
	


	//to edit all shape
	glPushMatrix();
	glTranslatef(0.0, 0.0, -400);
	glTranslatef(0.0, 0.0, -10);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(0, 0.0f, 1.0f, 0.0f);
	glRotatef(0, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glLineWidth(0.1);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	drawOrbit(40);
	drawOrbit(60);
	drawOrbit(80);
	drawOrbit(100);
	drawOrbit(125);
	drawOrbit(165);
	drawOrbit(200);
	drawOrbit(225);

	glPopMatrix();


	glPushMatrix();
	glColor3f(0.8, 0.498039, 0.196078);
	gluSphere(planet, 20, 36, 18);
	glColor3f(1, 1, 0);
	glEnable(GL_BLEND);
	glBlendFunc(first, second);
	gluSphere(planet, 30, 36, 18);
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_positio[] = {0,0, 0.0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_positio);
	GLfloat light_dif[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	GLfloat light_am[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_am);




	//mercury
	glPushMatrix();
	glRotatef(x_rotation * 1.6, 0, 1, 0);
	glTranslatef(40, 0, -10.0);
	glColor3ub(204, 126, 56);
	gluSphere(planet, 4.5, 36, 18);
	glPopMatrix();

	//venus
	glPushMatrix();
	glRotatef(x_rotation * 1.17, 0, 1, 0);
	glTranslatef(60, 0, -10.0);
	glColor3ub(215, 122, 98);
	gluSphere(planet, 6, 36, 18);
	glPopMatrix();

	//Earth
	glPushMatrix();
	glRotatef(x_rotation, 0, 1, 0);
	glTranslatef(80, 0, -10.0);
	glColor3f(0.275f, 0.51f, 0.71f);
	gluSphere(planet, 6.5, 36, 18);

	//moon
	glRotatef(x_rotation * 70, 0.0, 1.0, 0.0);
	glTranslatef(2, 0, -10.0);
	glColor3f(0.75f, 0.75f, 0.75f);
	gluSphere(planet, 3, 36, 18);

	glPopMatrix();


	//mars
	glPushMatrix();
	glRotatef(x_rotation * 0.8, 0, 1, 0);
	glTranslatef(100, 0, -10.0);
	glColor3ub(198, 62, 60);
	gluSphere(planet, 5, 36, 18);
	glPopMatrix();

	//Jupiter
	glPushMatrix();
	glRotatef(x_rotation * 0.438, 0, 1, 0);
	glTranslatef(125, 0, -10.0);
	glColor3ub(231, 203, 191);
	gluSphere(planet, 16, 36, 18);
	glPopMatrix();

	//saturn
	glPushMatrix();
	glRotatef(x_rotation * 0.325, 0, 1, 0);
	glTranslatef(165, 0, -10.0);
	glColor3f(0.8f, 0.6f, 0.5f);
	gluSphere(planet, 15, 36, 18);
	glColor3f(0.8f, 0.6f, 0.5f);
	glLineWidth(2);
	drawOrbit(18);
	glPopMatrix();


	//uranus
	glPushMatrix();
	glRotatef(x_rotation * 0.228, 0, 1, 0);
	glTranslatef(200, 0, -10.0);
	glColor3ub(36, 97, 253);
	gluSphere(planet, 9, 36, 18);
	glPopMatrix();

	//Neptune
	glPushMatrix();
	glRotatef(x_rotation * 0.182, 0, 1, 0);
	glTranslatef(225, 0, -10.0);
	glColor3ub(153, 223, 254);
	gluSphere(planet, 8.8, 36, 18);
	glPopMatrix();
	


	glPopMatrix();


	glutSwapBuffers();
}

void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	Height = h;
	Width = w;
	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 1000.0);
	//glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 500);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;

	case 'x':
		angle_x -= 10.0f;
		glutPostRedisplay();
		break;

	case 'X':
		angle_x += 10.0f;
		glutPostRedisplay();
		break;

	case 'y':
		angleY -= 5.0f;
		glutPostRedisplay();
		break;

	case 'Y':
		angleY += 5.0f;
		if (angleY > 360.0f) angleY -= 360.0f;
		glutPostRedisplay();
		break;

	case 'z':
		angleZ -= 10.0f;
		glutPostRedisplay();
		break;

	case 'Z':
		angleZ += 10.0f;
		glutPostRedisplay();
		break;


	case 'O':
		offset += 1;
		glutPostRedisplay();
		break;
	case 'o':
		offset -= 1;
		glutPostRedisplay();
		break;
	case 'U':
		x_value += 1;
		glutPostRedisplay();
		break;
	case 'u':
		x_value -= 1;
		glutPostRedisplay();
		break;
	case ' ': 
		animate = !animate;
		break;

	case 'w':
		cameraX -= 0.3f; 
		PX -= 0.3f;
		break;
	case 'W':
		cameraX += 0.3f;
		PX += 0.3f;
		break;
	case 'h':
		cameraY -= 0.3f; 
		PY -= 0.3f;
		break;
	case 'H':
		cameraY += 0.3f; 
		PY += 0.3f;
		break;

	case 'i':
		cameraZ -= 1.0f; // move camera closer to scene
		break;
	case 'I':
		cameraZ += 1.0f; // move camera farther from scene
		break;

/*	case 'e':
		PX -= 0.1f; // move camera closer to scene
		break;
	case 'E':
		PX += 0.1f; // move camera farther from scene
		break;
	case 't':
		PY -= 0.1f; // move camera closer to scene
		break;
	case 'T':
		PY += 0.1f; // move camera farther from scene
		break;*/

	default:
		break;

	}

	glutPostRedisplay();
}

void Idle()
{
	if (animate)
		x_rotation +=0.5/5;  //speed Earth

	glutPostRedisplay();
}

void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press W/w to increase/decrease the value of X axis of the camera at gllookat()." << std::endl
		<< "Press H/h to increase/decrease the value of Y axis of the camera at gllookat()." << std::endl
		<< "Press I/i to increase/decrease the value of Z axis of the camera at gllookat()." << std::endl
		<< "Press x, X, y, Y, z, Z to translate the solar animation system." << std::endl
	<< "Press O/o to zoom in / out." << std::endl;

}


int main(int argc, char* argv[])
{

	printInteraction();

	// initialize GLUT library state
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	// Define the main window size and initial position 
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(50, 10);

	// Create and label the main window
	glutCreateWindow("Solar system");
	Setup();

	// The rendering function 
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);

	//Enter main event handling loop
	glutMainLoop();
	return 0;
}
