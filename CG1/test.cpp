#include <GLUT/GLUT.h>
#include <math.h>

void drawKochSnowflake(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    } else {
        double deltaX = (x2 - x1) / 3;
        double deltaY = (y2 - y1) / 3;
        double xA = x1 + deltaX;
        double yA = y1 + deltaY;
        double xB = xA + (deltaX * cos(M_PI / 3)) - (deltaY * sin(M_PI / 3));
        double yB = yA + (deltaX * sin(M_PI / 3)) + (deltaY * cos(M_PI / 3));
        double xC = x1 + 2 * deltaX;
        double yC = y1 + 2 * deltaY;

        drawKochSnowflake(x1, y1, xA, yA, depth - 1);
        drawKochSnowflake(xA, yA, xB, yB, depth - 1);
        drawKochSnowflake(xB, yB, xC, yC, depth - 1);
        drawKochSnowflake(xC, yC, x2, y2, depth - 1);
    }
}

void display(void) {        
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    double radius = 0.6;
    double angleIncrement = 2 * M_PI / 6;
    for (int i = 0; i < 6; i++) {
        double x1 = radius * cos(i * angleIncrement);
        double y1 = radius * sin(i * angleIncrement);
        double x2 = radius * cos((i + 1) * angleIncrement);
        double y2 = radius * sin((i + 1) * angleIncrement);
        drawKochSnowflake(x1, y1, x2, y2, 4); 
    }
    glEnd();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
