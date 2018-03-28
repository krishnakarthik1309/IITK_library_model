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
#include "generateBuffers.h"


struct MyMesh{

	GLuint vao;
	GLuint texIndex;
	GLuint uniformBlockIndex;
	int numFaces;
};

struct MyMaterial{

	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
};

// Replace the model name by your model's filename
static const std::string modelname = "pkkelkar.obj";

// Uniform Buffer for Matrices
// this buffer will contain 3 matrices: projection, view and model
// each matrix is a float array with 16 components
GLuint matricesUniBuffer;
#define MatricesUniBufferSize sizeof(float) * 16 * 3
#define ProjMatrixOffset 0
#define ViewMatrixOffset sizeof(float) * 16
#define ModelMatrixOffset sizeof(float) * 16 * 2
#define MatrixSize sizeof(float) * 16

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

	LoadGLTextures(scene);

	glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) glutGetProcAddress("glGetUniformBlockIndex");
	glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) glutGetProcAddress("glUniformBlockBinding");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glutGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glutGetProcAddress("glBindVertexArray");
	glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) glutGetProcAddress("glBindBufferRange");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) glutGetProcAddress("glDeleteVertexArrays");

	program = setupShaders((char *) "shaders/vertexShader.glsl", (char *) "shaders/fragmentShader.glsl");
	genVAOsAndUniformBuffer(scene, textureIdMap);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//
	// Uniform Block
	//
	glGenBuffers(1,&matricesUniBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, matricesUniBuffer);
	glBufferData(GL_UNIFORM_BUFFER, MatricesUniBufferSize,NULL,GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, matricesUniLoc, matricesUniBuffer, 0, MatricesUniBufferSize);	//setUniforms();
	glBindBuffer(GL_UNIFORM_BUFFER,0);

	glEnable(GL_MULTISAMPLE);

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

	// cleaning up
	textureIdMap.clear();

	// clear myMeshes stuff
	for (unsigned int i = 0; i < myMeshes.size(); ++i) {

		glDeleteVertexArrays(1,&(myMeshes[i].vao));
		glDeleteTextures(1,&(myMeshes[i].texIndex));
		glDeleteBuffers(1,&(myMeshes[i].uniformBlockIndex));
	}
	// delete buffers
	glDeleteBuffers(1,&matricesUniBuffer);

	return 0;
}
