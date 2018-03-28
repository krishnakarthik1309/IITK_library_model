#include <GL/glew.h>
#include <GL/freeglut.h>

#include "textFile.h"


// Vertex Attribute Locations
GLuint vertexLoc=0, normalLoc=1, texCoordLoc=2;

// Uniform Bindings Points
GLuint matricesUniLoc = 1, materialUniLoc = 2;

GLuint texUnit = 0;

// Program and Shader Identifiers
GLuint program, vertexShader, fragmentShader;

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}


void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}


GLuint setupShaders(char *vertexFileName, char *fragmentFileName) {

	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	GLuint p,v,f;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead(vertexFileName);
	fs = textFileRead(fragmentFileName);

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	printShaderInfoLog(v);
	printShaderInfoLog(f);

	p = glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);

	glBindFragDataLocation(p, 0, "myoutput");

	glBindAttribLocation(p,vertexLoc,"position");
	glBindAttribLocation(p,normalLoc,"normal");
	glBindAttribLocation(p,texCoordLoc,"texCoord");

	glLinkProgram(p);
	glValidateProgram(p);
	printProgramInfoLog(p);

	program = p;
	vertexShader = v;
	fragmentShader = f;

	GLuint k = glGetUniformBlockIndex(p,"Matrices");
	glUniformBlockBinding(p, k, matricesUniLoc);
	glUniformBlockBinding(p, glGetUniformBlockIndex(p,"Material"), materialUniLoc);

	texUnit = glGetUniformLocation(p,"texUnit");

	return(p);
}
