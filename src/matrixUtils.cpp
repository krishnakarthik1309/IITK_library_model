#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string.h>
#include <math.h>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#define MatricesUniBufferSize sizeof(float) * 16 * 3
#define ProjMatrixOffset 0
#define ViewMatrixOffset sizeof(float) * 16
#define ModelMatrixOffset sizeof(float) * 16 * 2
#define MatrixSize sizeof(float) * 16
#define M_PIE       3.14159265358979323846f

// Uniform Buffer for Matrices
// this buffer will contain 3 matrices: projection, view and model
// each matrix is a float array with 16 components
GLuint matricesUniBuffer;

// Model Matrix (part of the OpenGL Model View Matrix)
float modelMatrix[16];

// For push and pop matrix
std::vector<float *> matrixStack;

static inline float
DegToRad(float degrees)
{
    return (float)(degrees * (M_PIE / 180.0f));
};

void multMatrix(float *a, float *b) {

    float res[16];

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[j*4 + i] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                res[j*4 + i] += a[k*4 + i] * b[j*4 + k];
            }
        }
    }
    memcpy(a, res, 16 * sizeof(float));

}

void crossProduct( float *a, float *b, float *res)
{
    res[0] = a[1] * b[2]  -  b[1] * a[2];
    res[1] = a[2] * b[0]  -  b[2] * a[0];
    res[2] = a[0] * b[1]  -  b[0] * a[1];
}

void normalize(float *a)
{
    float mag = sqrt(a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2]);

    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}

void setIdentityMatrix( float *mat, int size)
{
    // fill matrix with 0s
    for (int i = 0; i < size * size; ++i)
        mat[i] = 0.0f;

    // fill diagonal with 1s
    for (int i = 0; i < size; ++i)
        mat[i + i * size] = 1.0f;
}

void setTranslationMatrix(float *mat, float x, float y, float z)
{
    setIdentityMatrix(mat,4);
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

void setScaleMatrix(float *mat, float sx, float sy, float sz)
{
    setIdentityMatrix(mat,4);
    mat[0] = sx;
    mat[5] = sy;
    mat[10] = sz;
}

// Defines a transformation matrix mat with a rotation
// angle alpha and a rotation axis (x,y,z)
void setRotationMatrix(float *mat, float angle, float x, float y, float z)
{
    float radAngle = DegToRad(angle);
    float co = cos(radAngle);
    float si = sin(radAngle);
    float x2 = x*x;
    float y2 = y*y;
    float z2 = z*z;

    mat[0] = x2 + (y2 + z2) * co;
    mat[4] = x * y * (1 - co) - z * si;
    mat[8] = x * z * (1 - co) + y * si;
    mat[12]= 0.0f;

    mat[1] = x * y * (1 - co) + z * si;
    mat[5] = y2 + (x2 + z2) * co;
    mat[9] = y * z * (1 - co) - x * si;
    mat[13]= 0.0f;

    mat[2] = x * z * (1 - co) - y * si;
    mat[6] = y * z * (1 - co) + x * si;
    mat[10]= z2 + (x2 + y2) * co;
    mat[14]= 0.0f;

    mat[3] = 0.0f;
    mat[7] = 0.0f;
    mat[11]= 0.0f;
    mat[15]= 1.0f;
}

void pushMatrix() {

    float *aux = (float *)malloc(sizeof(float) * 16);
    memcpy(aux, modelMatrix, sizeof(float) * 16);
    matrixStack.push_back(aux);
}

void popMatrix() {

    float *m = matrixStack[matrixStack.size()-1];
    memcpy(modelMatrix, m, sizeof(float) * 16);
    matrixStack.pop_back();
    free(m);
}

void setModelMatrix()
{
    glBindBuffer(GL_UNIFORM_BUFFER, matricesUniBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER,
            ModelMatrixOffset, MatrixSize, modelMatrix);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void scale(float x, float y, float z)
{
    float aux[16];

    setScaleMatrix(aux,x,y,z);
    multMatrix(modelMatrix,aux);
    setModelMatrix();
}

// The equivalent to glRotate applied to the model matrix
void rotate(float angle, float x, float y, float z)
{
    float aux[16];

    setRotationMatrix(aux,angle,x,y,z);
    multMatrix(modelMatrix,aux);
    setModelMatrix();
}

void buildProjectionMatrix(float fov, float ratio, float nearp, float farp)
{
    float projMatrix[16];
    float f = 1.0f / tan (fov * (M_PI / 360.0f));

    setIdentityMatrix(projMatrix,4);

    projMatrix[0] = f / ratio;
    projMatrix[1 * 4 + 1] = f;
    projMatrix[2 * 4 + 2] = (farp + nearp) / (nearp - farp);
    projMatrix[3 * 4 + 2] = (2.0f * farp * nearp) / (nearp - farp);
    projMatrix[2 * 4 + 3] = -1.0f;
    projMatrix[3 * 4 + 3] = 0.0f;

    glBindBuffer(GL_UNIFORM_BUFFER, matricesUniBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, ProjMatrixOffset, MatrixSize, projMatrix);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}