#include <cstdlib>
#include <cmath>
#include <vector>
#include <GLUT/GLUT.h>

// 2�����x�N�g�����������߂̃N���X
class Vector2d {
public:
	double x, y;
	Vector2d() { x = y = 0; }
	Vector2d(double _x, double _y) { x = _x; y = _y; }
	void set(double _x, double _y) { x = _x; y = _y; }

	// ������1�ɐ��K������
	void normalize() {
		double len = length();
		x /= len; y /= len; 
	}

	// ������Ԃ�
	double length() { return sqrt(x * x + y * y); }

	// s�{����
	void scale(const double s) { x *= s; y *= s; }

	// ���Z�̒�`
	Vector2d operator+(Vector2d v) { return Vector2d(x + v.x, y + v.y); }

	// ���Z�̒�`
	Vector2d operator-(Vector2d v) { return Vector2d(x - v.x, y - v.y); }

	// ���ς̒�`
	double operator*(Vector2d v) { return x * v.x + y* v.y; }

	// ������Z�̒�`
	Vector2d& operator=(const Vector2d& v){ x = v.x; y = v.y; return (*this); }

	// ���Z����̒�`
	Vector2d& operator+=(const Vector2d& v) { x += v.x; y += v.y; return (*this); }

	// ���Z����̒�`
	Vector2d& operator-=(const Vector2d& v) { x -= v.x; y -= v.y; return (*this); }

	// �l���o�͂���
	void print() { printf("Vector2d(%f %f)\n", x, y); }
};

// �}�C�i�X�̕����̕t�����x�N�g����������悤�ɂ��邽�߂̒�` ��Fb=(-a); �̂悤�ɋL�q�ł���
Vector2d operator-( const Vector2d& v ) { return( Vector2d( -v.x, -v.y ) ); }

// �x�N�g���Ǝ����̐ς�������悤�ɂ��邽�߂̒�` ��F c=5*a+2*b; c=b*3; �̂悤�ɋL�q�ł���
Vector2d operator*( const double& k, const Vector2d& v ) { return( Vector2d( k*v.x, k*v.y ) );}
Vector2d operator*( const Vector2d& v, const double& k ) { return( Vector2d( v.x*k, v.y*k ) );}

// �x�N�g���������Ŋ��鑀���������悤�ɂ��邽�߂̒�` ��F c=a/2.3; �̂悤�ɋL�q�ł���
Vector2d operator/( const Vector2d& v, const double& k ) { return( Vector2d( v.x/k, v.y/k ) );}

// ================================================================================================


std::vector<Vector2d> g_ControlPoints; // ����_���i�[����
Vector2d BezierPoint;
Vector2d BezierNormal;

// �\�����������̊֐��ŋL��
void display(void) {        
	glClearColor (1.0, 1.0, 1.0, 1.0);  // �����F�w��
	glClear (GL_COLOR_BUFFER_BIT );     // ��ʏ���

	// ����_�̕`��
	glPointSize(5);
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for(unsigned int i = 0; i < g_ControlPoints.size(); i++) {
		glVertex2d(g_ControlPoints[i].x, g_ControlPoints[i].y);
	}
	glEnd();

	// ����_�����Ԑ����̕`��
	glColor3d(1.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	for(unsigned int i = 0; i < g_ControlPoints.size(); i++) {
		glVertex2d(g_ControlPoints[i].x, g_ControlPoints[i].y);
	}
	glEnd();
	
	// �� �����Ƀx�W�F�Ȑ���`�悷��R�[�h��ǉ�����

	for(unsigned int i = 3; i < g_ControlPoints.size(); i += 3) {
		glColor3d(0.0, 0.0, 0.0);
		glLineWidth(1);
		glBegin(GL_LINE_STRIP);
		for (double t = 0; t <= 1; t += 0.01){
				BezierPoint = pow(1-t, 3)*g_ControlPoints[i-3] + 3*t*pow(1-t, 2)*g_ControlPoints[i-2] + 3*pow(t, 2)*(1 - t)*g_ControlPoints[i-1] + pow(t, 3)*g_ControlPoints[i];
				glVertex2d(BezierPoint.x, BezierPoint.y);
			}
		glEnd();
		
	 // �ڐ��`��
		for (double t = 0; t <= 1; t += 0.01){
				BezierPoint = pow(1-t, 3)*g_ControlPoints[i-3] + 3*t*pow(1-t, 2)*g_ControlPoints[i-2] + 3*pow(t, 2)*(1 - t)*g_ControlPoints[i-1] + pow(t, 3)*g_ControlPoints[i];

				BezierNormal = -3 * pow(1-t, 2) * g_ControlPoints[i-3] + (9 * pow(t, 2) - 12 * t + 3)* g_ControlPoints[i-2] + (-9 * pow(t, 2) + 6 * t) * g_ControlPoints[i-1] + 3 * pow(t, 2) * g_ControlPoints[i];

				BezierNormal = BezierNormal / BezierNormal.length() * 60;

				glColor3d(0.0, 0.0, 1.0);
				glLineWidth(1);
				glBegin(GL_LINE_STRIP);
				glVertex2d(BezierPoint.x, BezierPoint.y);
				glVertex2d(BezierPoint.x - BezierNormal.y, BezierPoint.y + BezierNormal.x);
				glEnd();
			}
	}

	glutSwapBuffers();
}

void resizeWindow(int w, int h) {
	h = (h == 0) ? 1 : h;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �E�B���h�E���̍��W�n�ݒ�
	// �}�E�X�N���b�N�̍��W�ƕ`����W����v����悤�Ȑ����e
	glOrtho(0, w, h, 0, -10, 10);

	glMatrixMode(GL_MODELVIEW);
}

// �L�[�{�[�h�C�x���g����
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		exit(0);  /* '\033' �� ESC �� ASCII �R�[�h */
	default:
		break;
	} 
	glutPostRedisplay();
}

// �}�E�X�C�x���g����
void mouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			// �N���b�N�����ʒu�ɐ���_��ǉ�
			g_ControlPoints.push_back(Vector2d(x, y));
		break;
		case GLUT_MIDDLE_BUTTON:
		break;
		case GLUT_RIGHT_BUTTON:
			// �����̐���_�̍폜
			if(!g_ControlPoints.empty()) {
				g_ControlPoints.pop_back();
			}
		break;
		default:
		break;
		}
		glutPostRedisplay(); // �ĕ`��
	}
}

// ���C���v���O����
int main (int argc, char *argv[]) { 
	glutInit(&argc, argv);          // ���C�u�����̏�����
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE); // �`�惂�[�h�̎w��
	glutInitWindowSize(800 , 800);  // �E�B���h�E�T�C�Y���w��
	glutCreateWindow(argv[0]);      // �E�B���h�E���쐬
	glutDisplayFunc(display);       // �\���֐����w��
	glutReshapeFunc(resizeWindow);  // �E�B���h�E�T�C�Y���ύX���ꂽ�Ƃ��̊֐����w��
	glutKeyboardFunc(keyboard);     // �L�[�{�[�h�C�x���g�����֐����w��
	glutMouseFunc(mouse);           // �}�E�X�C�x���g�����֐����w��
	glutMainLoop();                 // �C�x���g�҂�
	return 0;
}