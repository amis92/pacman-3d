#include <windows.h>
#include <GL/gl.h>
#include "glut.h"


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Pacman 3D - OpenGL");

	glutMainLoop();

	return 0;
}