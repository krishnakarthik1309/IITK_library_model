extern const aiScene* scene;
extern float scaleFactor;
extern std::map<std::string, GLuint> textureIdMap;

bool Import3DFromFile( const std::string& pFile);
int LoadGLTextures(const aiScene* scene);
