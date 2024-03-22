#include <math.h>
#include <GLUT/GLUT.h>

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#define ID_DRAW_SHAPE1 1
#define ID_DRAW_SHAPE2 2

int rotateAngle1; // 図形1の回転角度
int rotateAngle2; // 図形2の回転角度

double scale1;    // 図形1の拡大縮小係数
double scale2;    // 図形2の拡大縮小係数

void display(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 図形1 (赤い四角形)
    glPushMatrix();
    glColor3d(1.0, 0.0, 0.0); // 赤色
    glRotated(rotateAngle1, 0, 0, 1);
    glScaled(scale1, scale1, 1);
    glCallList(ID_DRAW_SHAPE1);
    glPopMatrix();

    // 図形2 (青い円)
    glPushMatrix();
    glColor3d(0.0, 0.0, 1.0); // 青色
    glRotated(rotateAngle2, 0, 0, 1);
    glScaled(scale2, scale2, 1);
    glCallList(ID_DRAW_SHAPE2);
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    rotateAngle1++; // 図形1の回転角度を増加
    rotateAngle2++; // 図形2の回転角度を増加

    scale1 = 0.5 + 0.5 * sin(0.1 * rotateAngle1); // 図形1の拡大縮小
    scale2 = 0.5 + 0.5 * cos(0.1 * rotateAngle2); // 図形2の拡大縮小

    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void buildDisplayLists() {
    glNewList(ID_DRAW_SHAPE1, GL_COMPILE);

    glBegin(GL_POLYGON);
    glVertex2d(-0.2, -0.2);
    glVertex2d(0.2, -0.2);
    glVertex2d(0.2, 0.2);
    glVertex2d(-0.2, 0.2);
    glEnd();

    glEndList();

    glNewList(ID_DRAW_SHAPE2, GL_COMPILE);

    int num_segments = 100;
    double radius = 0.2;
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        double theta = 2.0 * M_PI * i / num_segments;
        double x = radius * cos(theta);
        double y = radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();

    glEndList();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);

    buildDisplayLists();
    rotateAngle1 = 0;
    rotateAngle2 = 0;
    scale1 = 1.0;
    scale2 = 1.0;

    glutMainLoop();
    return 0;
}
