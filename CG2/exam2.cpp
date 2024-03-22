#include <math.h>
#include <GLUT/GLUT.h>

// 円周率πを定義（定義がされていない場合に備えて）
#ifndef M_PI
#define M_PI 3.14159265358979
#endif

// 星を描画するディスプレイリストのID
#define ID_DRAW_STAR 1 // glNewListで使用するID

int rotateAngle; // 回転角度を格納する変数

// 画面表示関数
void display(void) {        
	glClearColor(1.0, 1.0, 1.0, 1.0);  // 背景色を白に設定
	glClear(GL_COLOR_BUFFER_BIT);       // 画面をクリアして背景色で塗りつぶす

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0); // 赤色
	glRotated(rotateAngle, 0, 0, 1);
	glTranslated(0.5, 0, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glColor3d(0.0, 0.0, 0.0); // 黒色
	glRotated(rotateAngle*5, 0, 0, 1);
	glScaled(0.2,0.2,1);
	glTranslated(0.5, 0, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0); // 緑色
	glRotated(rotateAngle, 0, 0, 1);
	glTranslated(0, 0.5, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 0.0, 1.0); // 青色
	glRotated(rotateAngle, 0, 0, 1);
	glTranslated(-0.5, 0, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glPopMatrix();

	glutSwapBuffers(); // ダブルバッファを切り替えて画面を更新
}

// タイマー関数
void timer(int value) {
	rotateAngle++; // 回転角度を増加

	glutPostRedisplay(); // 画面再描画を要求
	glutTimerFunc(100, timer, 0); // 100ミリ秒ごとにタイマーを再設定
}

// 星のディスプレイリストを生成する関数
void buildDisplayList() {
	glNewList(ID_DRAW_STAR, GL_COMPILE);

	double r0 = 0.15; // 内側の半径
	double r1 = 0.4;  // 外側の半径
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 5; i++) { // 5つの頂点で星を描画
		int deg = i * 72;
		glVertex3d(r0 * cos((deg - 36) * M_PI / 180.0), r0 * sin((deg - 36) * M_PI / 180.0), 0);  // 内側の頂点
		glVertex3d(r1 * cos(deg * M_PI / 180.0), r1 * sin(deg * M_PI / 180.0), 0);  // 外側の頂点
		glVertex3d(r0 * cos((deg + 36) * M_PI / 180.0), r0 * sin((deg + 36) * M_PI / 180.0), 0);  // 内側の頂点
	}
	glEnd();

	glEndList();
}

// メイン関数
int main(int argc, char *argv[]) { 
	glutInit(&argc, argv);          // GLUTの初期化
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowSize(400, 400);  // ウィンドウサイズを設定
	glutCreateWindow(argv[0]);      // ウィンドウを作成
	glutDisplayFunc(display);       // 画面表示関数を設定

	glutTimerFunc(100, timer, 0); // 100ミリ秒ごとにタイマーを設定

	buildDisplayList();
	
	rotateAngle = 0;                // 回転角度の初期化

	glutMainLoop();                 // GLUTメインループの開始
	return 0;
}
