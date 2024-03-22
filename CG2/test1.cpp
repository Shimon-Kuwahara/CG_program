#include <math.h>
#include <GLUT/GLUT.h>

int rotateAngle; // 回転角度を格納する変数

// 画面表示関数
void display(void) {        
	glClearColor(1.0, 1.0, 1.0, 1.0);  // 背景色を白に設定
	glClear(GL_COLOR_BUFFER_BIT);       // 画面をクリアして背景色で塗りつぶす

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(rotateAngle*2, 0, 0, 1);

	glColor3d(1.0, 1.0, 0.0);   // 色を赤(R,G,B)に設定
	glBegin(GL_TRIANGLES);
	    glVertex3d(0,     0, 0); 
	    glVertex3d(0.5,   0, 0); 
	    glVertex3d(0.5, 0.5, 0); 
	glEnd();                               

	glutSwapBuffers(); // ダブルバッファを切り替えて画面を更新
}

// タイマー関数
void timer(int value) {
	rotateAngle++; // 回転角度を増加

	glutPostRedisplay(); // 画面再描画を要求
	glutTimerFunc(50, timer, 0); // 100ミリ秒ごとにタイマーを再設定
}

// メイン関数
int main(int argc, char *argv[]) { 
	glutInit(&argc, argv);          // GLUTの初期化
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowSize(400, 400);  // ウィンドウサイズを設定
	glutCreateWindow(argv[0]);      // ウィンドウを作成
	glutDisplayFunc(display);       // 画面表示関数を設定

	glutTimerFunc(100, timer, 0); // 100ミリ秒ごとにタイマーを設定

	rotateAngle = 0;                // 回転角度の初期化

	glutMainLoop();                 // GLUTメインループの開始
	return 0;
}
