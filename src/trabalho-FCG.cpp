#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>

class GLintPoint
{
public:
    GLint x, y;
};

int random(int m)
{
    return rand() % m;
}

void drawDot(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void drawSierpinskiGasket()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLintPoint T[3] = {{10,10},{300,30},{200,300}};
    glColor3f(0.0, 1.0, 0.0);
    int index = random(3);
    GLintPoint point = T[index];
    drawDot(point.x, point.y);
    for(int i = 0; i < 10000; ++i)
    {
        index = random(3);
        point.x = (point.x + T[index].x) / 2;
        point.y = (point.y + T[index].y) / 2;
        drawDot(point.x, point.y);
    }
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("The Sierpinski Gasket");
    glutDisplayFunc(drawSierpinskiGasket);
    init();
    glutMainLoop();
    return EXIT_SUCCESS;
}
