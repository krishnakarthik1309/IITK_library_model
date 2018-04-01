extern GLuint matricesUniBuffer;
extern float modelMatrix[16];
extern std::vector<float *> matrixStack;

void multMatrix(float *a, float *b);
void crossProduct( float *a, float *b, float *res);
void normalize(float *a);
void setIdentityMatrix( float *mat, int size);
void setTranslationMatrix(float *mat, float x, float y, float z);
void setScaleMatrix(float *mat, float sx, float sy, float sz);
void setRotationMatrix(float *mat, float angle, float x, float y, float z);
void pushMatrix();
void popMatrix();
void setModelMatrix();
void scale(float x, float y, float z);
void rotate(float angle, float x, float y, float z);
void buildProjectionMatrix(float fov, float ratio, float nearp, float farp);