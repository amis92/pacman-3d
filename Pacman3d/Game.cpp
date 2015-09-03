#include "Game.h"
#include "glut.h"
#include "BoardDrawer.h"
#include "TextureLoader.h"
#define _USE_MATH_DEFINES
#include <math.h>

GLuint Game::textures[TexturesSize];

const Board Game::board;
double Game::cameraArc = 0;
double Game::cameraRadius = 30;
double const Game::maxCameraArc = M_PI / 12;

void Game::SetAmbientLighting()
{
	const auto amb = 0.8f;
	GLfloat global_ambient[] = {amb, amb, amb, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void Game::PointLight(const float x, const float y, const float z,
                      const float amb, const float diff, const float spec, const GLenum light)
{
	GLfloat light_ambient[] = {amb, amb, amb, 1.0};
	GLfloat light_diffuse[] = {diff, diff, diff, 1.0};
	GLfloat light_specular[] = {spec, spec, spec, 1.0};

	GLfloat light_position[] = {x, y, z, 0.0};

	glLightfv(light, GL_AMBIENT, light_ambient);
	glLightfv(light, GL_DIFFUSE, light_diffuse);
	glLightfv(light, GL_SPECULAR, light_specular);
	glLightfv(light, GL_POSITION, light_position);

	glEnable(light); //enable the light after setting the properties
}

void Game::LoadTextures()
{
	textures[TestTextureIndex] = TextureLoader::LoadBmpTex("img/test.bmp");
	textures[FloorTextureIndex] = TextureLoader::LoadRawTex("img/block_lblue.raw", 256, 256);
	textures[WallTextureIndex] = TextureLoader::LoadRawTex("img/block_wall.raw", 256, 256);
	textures[WallFloorTextureIndex] = TextureLoader::LoadRawTex("img/block_brown.raw", 256, 256);
}

void Game::PositionCamera()
{
	auto camz = cameraRadius * cos(cameraArc);
	auto camx = cameraRadius * sin(cameraArc);
	auto camy = 1.f;
	gluLookAt(camx, camy, camz, 0., 0., 0., 0., 1., 0.);
}

void Game::RecalculateCameraArc(int frameNo)
{
	auto period = double(frameNo) / 360.0;
	auto zeroOneZeroSin = sin(period * M_PI * 2);
	cameraArc = zeroOneZeroSin * maxCameraArc;
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

	LoadTextures();
}

void Game::Display()
{
	static auto frameNo = 0;
	if (frameNo < 360) frameNo++; else frameNo = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	{
		glPushMatrix();
		RecalculateCameraArc(frameNo);
		PositionCamera();
		PointLight(-30, 30, 30, 0.2, 1.0, 0.0, GL_LIGHT0);
		BoardDrawer drawer(board, textures);
		drawer.Draw(frameNo);
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
	Sleep(10);
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
