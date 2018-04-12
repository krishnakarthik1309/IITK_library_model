extern float scaleFactor;
extern std::map<std::string, GLuint> textureIdMap;

const aiScene* Import3DFromFile( const std::string& pFile);
int LoadGLTextures(const aiScene* scene);
