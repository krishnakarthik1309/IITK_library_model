#include <GL/glew.h>
#include <GL/freeglut.h>

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

int main(int argc, char **argv)
{
	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitContextVersion (3, 3);
	glutInitContextFlags (GLUT_COMPATIBILITY_PROFILE );

	glutInitWindowSize(900, 700);
	glutCreateWindow("IITK Library");

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
