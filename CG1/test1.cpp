#include <GLUT/GLUT.h>
#include <math.h>

int depthNum = 3;
void drawKochSnowflake(double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    } else {
        // 再帰ケース：線分を3つに分割してコッホの雪片を描画
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

    // 正三角形の頂点座標
    double triangleSize = 0.6;
    double triangleHeight = triangleSize * sqrt(3) / 2;
    double triangleX[3] = {0.0, -triangleSize / 2, triangleSize / 2};
    double triangleY[3] = {0.0, triangleHeight, triangleHeight};

    glBegin(GL_LINES);

    // 正三角形の各辺にコッホ雪片を描画
    for (int i = 0; i < 3; i++) {
        double x1 = triangleX[i];
        double y1 = triangleY[i];
        double x2 = triangleX[(i + 1) % 3];
        double y2 = triangleY[(i + 1) % 3];
        drawKochSnowflake(x1, y1, x2, y2, depthNum);
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