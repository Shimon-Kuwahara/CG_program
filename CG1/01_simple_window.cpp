#include <GL/glut.h> 

// 画面を初期化して白色で塗りつぶす
void display(void) {        
	glClearColor(1.0, 1.0, 1.0, 1.0);  // 背景色を白に設定
	glClear(GL_COLOR_BUFFER_BIT);     // 画面をクリア

	/* ここに描画コードを追加する */

	glFlush(); // 描画を実行
}

// グラフィックス初期化
int main(int argc, char* argv[]) { 
	glutInit(&argc, argv);          // GLUTの初期化
	glutInitWindowSize(400, 400);  // ウィンドウのサイズ設定
	glutCreateWindow(argv[0]);      // ウィンドウの生成
	glutDisplayFunc(display);       // 描画関数の登録
	glutMainLoop();                 // イベントループの開始
	return 0;
}
