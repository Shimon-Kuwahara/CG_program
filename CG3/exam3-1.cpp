#define _USE_MATH_DEFINES // Visual Studio用の定義（M_PIの定義）
#include <cstdlib>
#include <GLUT/GLUT.h>
#include <cmath>

// 色を表現するための共用体
union color {
    struct { float r, g, b, a; };
    float colors[4];
};

// ティーポットのデータ構造
struct TeapotData {
    color ambient, diffuse, specular;
    float shininess, angle;
};

const int g_NumTeapots = 8;
TeapotData g_Teapots[g_NumTeapots];

const float g_TeapotSize = 1.f;
const float g_InnerRadius = 6.f;
const float g_OuterRadius = 7.5f;
const float g_HeightAmplitude = 0.8f;
const float g_HeightOffset = 0.2f;

const float g_EyeCenterY = 9.f;
const float g_EyeCenterZ = 30.f;
const float g_EyeRadius = 8.f;
float g_EyeY, g_EyeZ;

const int g_AnimationIntervalMsec = 10;

float g_RotationDegree = 0.f;
const float g_DeltaRotationDegree = 0.3;

int g_WindowWidth = 512;
int g_WindowHeight = 512;

// シリンダーを描画する関数
void displayCylinder(float radius, float height, int nSlices) {
    // 側面
    const float deltaTheta = 2 * M_PI / (float)nSlices;

    glNormal3f(0, 1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, height, 0);
    for (int i = 0; i <= nSlices; i++) {
        const float theta = deltaTheta * i;
        glVertex3f(radius * cosf(theta), height, radius * sinf(theta));
    }
    glEnd();

    // 底面
    glNormal3f(0, -1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for (int i = 0; i <= nSlices; i++) {
        const float theta = deltaTheta * i;
        glVertex3f(radius * cosf(theta), 0, radius * sinf(theta));
    }
    glEnd();

    // 側面
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= nSlices; i++) {
        const float theta = deltaTheta * i;
        const float cosTheta = cosf(theta);
        const float sinTheta = sinf(theta);
        glNormal3f(cosTheta, 0, sinTheta);
        glVertex3f(radius * cosTheta, height, radius * sinTheta);
        glVertex3f(radius * cosTheta, 0, radius * sinTheta);
    }
    glEnd();
}

// メインの描画関数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 投影行列の設定
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, g_WindowWidth / (double)g_WindowHeight, 1, 100.0);

    // モデルビュー行列の設定
    g_EyeY = 15 + 10 * sin(g_RotationDegree * M_PI / 24);
    g_EyeZ = 35 + 10 * cos(g_RotationDegree * M_PI / 24);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, g_EyeY, g_EyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    float ambientColor[] = { 0.4f, 0.2f, 0.2f, 1.0f };
    float diffuseColor[] = { 1.f, 0.8f, 0.8f, 1.0f };
    float specularColor[] = { 0.4f, 0.3f, 0.3f, 1.0f };
    float shininess = 5.f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

    // トーラスを描画
    glPushMatrix();
    glTranslatef(0, g_HeightAmplitude + g_HeightOffset + 3.f, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(g_OuterRadius, 2.f, 32, 32);
    glPopMatrix();

    // 柱を描画
    glPushMatrix();
    glTranslatef(0, -1.f, 0);
    displayCylinder(0.5f, g_HeightAmplitude + g_HeightOffset + 6.5f, 32);
    glPopMatrix();

    // 台座を描画
    glPushMatrix();
    glTranslatef(0, -2.f, 0);
    displayCylinder(g_OuterRadius, 0.7f, 64);
    glPopMatrix();

    // メリーゴーラウンド上のティーポットを描画
    glPushMatrix();
    glTranslatef(0, g_HeightAmplitude + g_HeightOffset + 5.5f, 0);
    glRotatef(g_RotationDegree, 0, 1, 0); // メリーゴーラウンドの回転
    glutSolidTeapot(g_TeapotSize);
    glPopMatrix();

    const float deltaTheta = 360 / (float)g_NumTeapots;

    // メリーゴーラウンド上のティーポットを均等に配置
    for (int i = 0; i < g_NumTeapots; i++) {
        const float thetaDegree = deltaTheta * i;

        const float thetaRad = thetaDegree * M_PI / 180.f;
        const float xPos = g_InnerRadius * sinf(thetaRad);
        const float zPos = g_InnerRadius * cosf(thetaRad);

        const float yPos = g_HeightOffset + 0.5 * (1.0 + sin(i + g_RotationDegree * M_PI / 4.0));

        // ティーポットの色設定
        glMaterialfv(GL_FRONT, GL_AMBIENT, g_Teapots[i].ambient.colors);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, g_Teapots[i].diffuse.colors);
        glMaterialfv(GL_FRONT, GL_SPECULAR, g_Teapots[i].specular.colors);
        glMaterialfv(GL_FRONT, GL_SHININESS, &g_Teapots[i].shininess);

        // ティーポットを描画
        glPushMatrix();
        glRotatef(g_RotationDegree, 0, 1, 0);
        glTranslatef(xPos, yPos, zPos);
        glRotatef(thetaDegree, 0, 1, 0);
        glRotatef(g_Teapots[i].angle, 0, 0, 1);
        glutSolidTeapot(1.2f * g_TeapotSize);
        glPopMatrix();

        // シリンダーの色設定
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

        // シリンダーを描画
        glPushMatrix();
        glRotatef(g_RotationDegree, 0, 1, 0);
        glTranslatef(xPos, -1.f, zPos);
        displayCylinder(0.3f, yPos + 1.f, 32);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// 乱数生成関数
float frand() { return rand() / (float)RAND_MAX; }

// 初期化関数
void init() {
    glClearColor(1, 1, 1, 1);
    glClearDepth(100.f);

    // 光源の設定
    float lightAmbientColor0[] = { 0.2f, 0.2f, 0.2f, 0.0f };
    float lightDiffuseColor0[] = { 0.4f, 0.4f, 0.4f, 0.0f };
    float lightSpecularColor0[] = { 0.8f, 0.8f, 0.8f, 0.0f };
    float lightPosition0[] = { 5.0f, 5.0f, 8.0f, 0.0f };

    float lightAmbientColor1[] = { 0.2f, 0.2f, 0.2f, 0.0f };
    float lightDiffuseColor1[] = { 0.4f, 0.4f, 0.4f, 0.0f };
    float lightSpecularColor1[] = { 0.8f, 0.8f, 0.8f, 0.0f };
    float lightPosition1[] = { -5.0f, 2.0f, 3.0f, 0.0f };

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientColor0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseColor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbientColor1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuseColor1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecularColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

    srand(0);

    // メリーゴーラウンド上のティーポットのパラメータをランダムに設定
    for (int i = 0; i < g_NumTeapots; i++) {
        g_Teapots[i].ambient.r = 0.2f * frand();
        g_Teapots[i].ambient.g = 0.2f * frand();
        g_Teapots[i].ambient.b = 0.2f * frand();
        g_Teapots[i].ambient.a = 1.f;

        g_Teapots[i].diffuse.r = 0.2f * frand() + 0.8f;
        g_Teapots[i].diffuse.g = 0.2f * frand() + 0.8f;
        g_Teapots[i].diffuse.b = 0.2f * frand() + 0.8f;
        g_Teapots[i].diffuse.a = 1.f;

        g_Teapots[i].specular.r = 0.3f * frand() + 0.2f;
        g_Teapots[i].specular.g = 0.3f * frand() + 0.2f;
        g_Teapots[i].specular.b = 0.3f * frand() + 0.2f;
        g_Teapots[i].specular.a = 1.f;

        g_Teapots[i].shininess = 2.f + 30 * frand();

        g_Teapots[i].angle = 15 * (2.f * frand() - 1.f);
    }

    glEnable(GL_DEPTH_TEST);
}

// アニメーションのタイマーコールバック関数
void timer(int val) {
    // メリーゴーラウンドの回転
    g_RotationDegree += g_DeltaRotationDegree;

    const float rotationRad = 2.f * g_RotationDegree * M_PI / 180.f;

    // 視点の位置の更新（上下運動しない）
    g_EyeY = g_EyeCenterY;
    g_EyeZ = g_EyeCenterZ;

    glutPostRedisplay();

    // タイマー再設定
    glutTimerFunc(g_AnimationIntervalMsec, timer, val);
}

// ウィンドウのリサイズ時のコールバック関数
void reshape(int w, int h) {
    if (h < 1) return;

    // ビューポートの設定
    glViewport(0, 0, w, h);
    g_WindowWidth = w;
    g_WindowHeight = h;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(g_WindowWidth, g_WindowHeight);

    // ウィンドウの生成
    glutCreateWindow("Teapot Merry-Go-Round");

    // コールバック関数の設定
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // ウィンドウリサイズ時のコールバック
    glutTimerFunc(g_AnimationIntervalMsec, timer, 0);

    // 初期化関数呼び出し
    init();

    // イベントループ開始
    glutMainLoop();

    return 0;
}
