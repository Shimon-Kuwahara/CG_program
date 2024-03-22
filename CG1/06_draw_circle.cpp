#include <GL/glut.h> // ���C�u�����p�w�b�_�t�@�C���̓ǂݍ���
#include <math.h>

// �\�����������̊֐��ŋL��
void display(void) {        
	glClearColor (1.0, 1.0, 1.0, 1.0);  // �����F�w��
	glClear (GL_COLOR_BUFFER_BIT );     // ��ʏ���

	glColor3d(0.0, 0.0, 0.0);   // �F�w��(R,G,B)��0�`1�܂�
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 5; i++) {
		double x = cos(i * 3.14159 /180.0);
		double y = sin(i * 3.14159 /180.0);
        glVertex2d(x * 0.6, y * 0.6); 
	}
	glEnd();                               

	glFlush(); // ��ʏo��
}

// ���C���v���O����
int main (int argc, char *argv[]) { 
	glutInit(&argc, argv);          // ���C�u�����̏�����
	glutInitWindowSize(400 , 400);  // �E�B���h�E�T�C�Y���w��
	glutCreateWindow(argv[0]);      // �E�B���h�E���쐬
	glutDisplayFunc(display);       // �\���֐����w��
	glutMainLoop();                 // �C�x���g�҂�
	return 0;
}
