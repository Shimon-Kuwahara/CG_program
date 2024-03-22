#include <GLUT/GLUT.h>
#include <math.h>

void display(void) {        
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3d(0.0, 0.0, 0.0);

    glBegin(GL_LINE_LOOP);
    double radius = 0.6;
    double angle = 0.0;
    for(int i = 0; i < 360; i++) {
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex2d(x, y); 
        angle += 3.14159 / 180.0 * 72.0; // 五角星の内角
        x = radius / 2.0 * cos(angle);
        y = radius / 2.0 * sin(angle);
        glVertex2d(x, y);
        angle += 3.14159 / 180.0 * 72.0; // 五角星の外角
    }
    glEnd();                               

    glFlush();
}

int main (int argc, char *argv[]) { 
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
