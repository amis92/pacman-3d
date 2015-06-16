#include "Game.h"
#include "glut.h"
#include "BoardDrawer.h"

const Board Game::board;

void Game::SetAmbientLighting()
{
	const auto amb = 0.5f;
	GLfloat global_ambient[] = { amb, amb, amb, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void Game::PointLight(const float x, const float y, const float z,
	const float amb, const float diff, const float spec, const GLenum light)
{
	GLfloat light_ambient[] = { amb, amb, amb, 1.0 };
	GLfloat light_diffuse[] = { diff, diff, diff, 1.0 };
	GLfloat light_specular[] = { spec, spec, spec, 1.0 };

	GLfloat light_position[] = { x, y, z, 0.0 };

	glLightfv(light, GL_AMBIENT, light_ambient);
	glLightfv(light, GL_DIFFUSE, light_diffuse);
	glLightfv(light, GL_SPECULAR, light_specular);
	glLightfv(light, GL_POSITION, light_position);

	glEnable(light); //enable the light after setting the properties
}

void Game::Init(int* argcp, char** argv)
{
	glutInit(argcp, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Pacman 3D - OpenGL");

	glutSpecialFunc(OnSpecialKeys);
	glutKeyboardFunc(OnKeyboard);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Display);

	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	SetAmbientLighting();
	PointLight(-10, 5, 30, 0.2, 1.0, 1.0, GL_LIGHT0);
}

void Game::Display()
{
	static auto frame_no = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (frame_no < 360) frame_no++; else frame_no = 0;
	glMatrixMode(GL_MODELVIEW);
	{
		glPushMatrix();
		gluLookAt(0., 5., 40., 0., 0., 0., 0., 1., 0.);
		BoardDrawer drawer(board);
		drawer.Draw();
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

void Game::RunMainLoop()
{
	glutMainLoop();
}

void Game::Reshape(int width, int height)
{
	if (height > 0 && width > 0)
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		auto const aspect = width < height
			                    ? double(height) / double(width)
			                    : double(width) / double(height);
		gluPerspective(65.0, double(width) / double(height), 4.0, 150.0);
		glMatrixMode(GL_MODELVIEW);
	}
}

void Game::OnKeyboard(unsigned char key, int x, int y)
{
	/*if (key == 'w' && camz > 10.0)
		camz -= 0.1;
	else if (key == 's' && camz < 55.0)
		camz += 0.1;*/
	glutPostRedisplay();
}

void Game::OnSpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		// TODO ruch w lewo
		break;

	case GLUT_KEY_UP:
		// TODO ruch w górę
		break;

	case GLUT_KEY_RIGHT:
		// TODO ruch w prawo
		break;

	case GLUT_KEY_DOWN:
		// TODO ruch w dół
		break;
	}
	glutPostRedisplay();
}
