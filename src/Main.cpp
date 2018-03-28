#include <GL/glew.h>
#include <GL/freeglut.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <math.h>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "load3DModel.h"
#include "shaders.h"


// the global Assimp scene object
const aiScene* scene = NULL;

// scale factor for the model to fit in the window
float scaleFactor;

// Replace the model name by your model's filename
static const std::string modelname = "pkkelkar.obj";

void mouseWheel(int wheel, int direction, int x, int y)
{

}

void processMouseMotion(int xx, int yy)
{

}

void processMouseButtons(int button, int state, int xx, int yy)
{

}

void processKeys(unsigned char key, int xx, int yy)
{

}

void changeSize(int w, int h)
{

}

void renderScene(void)
{

}

int init()
{
	if (!Import3DFromFile(modelname))
		return 0;

	scene = getScene();
	scaleFactor = getScaleFactor();
	return 1; // true
}

int main(int argc, char **argv)
{
	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitContextVersion (3, 3);
	glutInitContextFlags (GLUT_COMPATIBILITY_PROFILE );

	glutInitWindowSize(900, 700);
	glutCreateWindow("P K Keklkar Library");

	//  Callback Registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutMouseWheelFunc ( mouseWheel ) ;

	// version info
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

	// return from main loop
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//  GLUT main loop
	glutMainLoop();

	return 0;
}
