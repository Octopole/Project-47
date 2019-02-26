#include <GL/glut.h>

static int window;

static GLfloat radius = 1.0;
static GLint slices = 20;
static GLint stacks = 20;

static GLfloat rotateX = 0.0;
static GLfloat rotateY = 0.0;
static GLfloat rotateZ = 0.0;

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	// Axes.
	glBegin(GL_LINES);
		// Red x-axis.
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);
		// Green y-axis.
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 5, 0);
		// Blue z-axis.
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 5);
	glEnd();
	// Sphere.
	glColor3f(1, 1, 1);
	glutWireSphere(radius, slices, stacks);
	// Rotation.
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	glRotatef(rotateZ, 0.0, 0.0, 1.0);
	rotateX = 0.0;
	rotateY = 0.0;
	rotateZ = 0.0;
	glutSwapBuffers();
}

void reshape(GLint w, GLint h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 80.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(1.0, 2.0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			rotateX = -1.0;
			glutPostRedisplay();
			break;
		case 's':
			rotateX = 1.0;
			glutPostRedisplay();
			break;
		case 'q':
			rotateY = -1.0;
			glutPostRedisplay();
			break;
		case 'e':
			rotateY = 1.0;
			glutPostRedisplay();
			break;
		case 'a':
			rotateZ = -1.0;
			glutPostRedisplay();
			break;
		case 'd':
			rotateZ = 1.0;
			glutPostRedisplay();
			break;
		case 27:
			glutDestroyWindow(window);
			exit(0);
	}
}

int main(int argc, char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 1280);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow(argv[0]);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
