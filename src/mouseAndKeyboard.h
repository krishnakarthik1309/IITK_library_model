extern float camX, camY, camZ, alpha, beta, r;
extern int startX, startY, tracking;

void processKeys(unsigned char key, int xx, int yy);
void processMouseButtons(int button, int state, int xx, int yy);
void processMouseMotion(int xx, int yy);
void mouseWheel(int wheel, int direction, int x, int y);