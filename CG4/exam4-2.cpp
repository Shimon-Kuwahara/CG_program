#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <GLUT/GLUT.h>

using namespace std;

// 3�����x�N�g�����������߂̃N���X
class Vector3d {
public:
	double x, y, z;
	Vector3d() { x = y = z = 0; }
	Vector3d(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
	void set(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }

	// ������1�ɐ��K������
	void normalize() {
		double len = length();
		x /= len; y /= len; z /= len;
	}

	// ������Ԃ�
	double length() { return sqrt(x * x + y * y + z * z); }

	// s�{����
	void scale(const double s) { x *= s; y *= s; z *= s; }

	// ���Z�̒�`
	Vector3d operator+(Vector3d v) { return Vector3d(x + v.x, y + v.y, z + v.z); }

	// ���Z�̒�`
	Vector3d operator-(Vector3d v) { return Vector3d(x - v.x, y - v.y, z - v.z); }

	// ���ς̒�`
	double operator*(Vector3d v) { return x * v.x + y* v.y + z * v.z; }

	// �O�ς̒�`
	Vector3d operator%(Vector3d v) { return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	
	// ������Z�̒�`
	Vector3d& operator=(const Vector3d& v){ x = v.x; y = v.y; z = v.z; return (*this); }

	// ���Z����̒�`
	Vector3d& operator+=(const Vector3d& v) { x += v.x; y += v.y; z += v.z; return (*this); }

	// ���Z����̒�`
	Vector3d& operator-=(const Vector3d& v) { x -= v.x; y -= v.y; z -= v.z; return (*this); }

	// �l���o�͂���
	void print() { printf("Vector3d(%f %f %f)\n", x, y, z); }
};

// �}�C�i�X�̕����̕t�����x�N�g����������悤�ɂ��邽�߂̒�` ��Fb=(-a); �̂悤�ɋL�q�ł���
Vector3d operator-( const Vector3d& v ) { return( Vector3d( -v.x, -v.y, -v.z ) ); }

// �x�N�g���Ǝ����̐ς�������悤�ɂ��邽�߂̒�` ��F c=5*a+2*b; c=b*3; �̂悤�ɋL�q�ł���
Vector3d operator*( const double& k, const Vector3d& v ) { return( Vector3d( k*v.x, k*v.y, k*v.z ) );}
Vector3d operator*( const Vector3d& v, const double& k ) { return( Vector3d( v.x*k, v.y*k, v.z*k ) );}

// �x�N�g���������Ŋ��鑀���������悤�ɂ��邽�߂̒�` ��F c=a/2.3; �̂悤�ɋL�q�ł���
Vector3d operator/( const Vector3d& v, const double& k ) { return( Vector3d( v.x/k, v.y/k, v.z/k ) );}


// ���̂̏����i�[����N���X
class Sphere {
public:
	Vector3d position; // ���S�ʒu
	float color[3];    // �`��F

	void setColor(float r, float g, float b) {
		color[0] = r; color[1] = g; color[2] = b;
	}

	// ���̋��̂�`�悷�郁���o�֐�
	void display() { 
		glPushMatrix(); // ���݂̃��f���ϊ��s���ޔ����Ă���

		// ���W�̕��s�ړ��ƃX�P�[���ϊ����{���ċ��̂�`�悷��
		glTranslated(position.x, position.y, position.z);
		glScaled(2, 2, 2);
		glutSolidSphere(1.0, 32, 32);
		
		glPopMatrix();  // �ޔ����Ă������f���ϊ��s���߂�
	}
};

// 3�̋��̂��������Ă���
Sphere g_Sphere[3];

// �I����Ԃɂ��鋅�̂�ID�ԍ��i0,1,2�j��ێ�����B�I����Ԃ̋����������-1�Ƃ���B
int g_SelectedSphereID = -1;

// �N���b�N���ꂽ3�������W��ێ�����
Vector3d g_SelectedPos;

// �E�B���h�E�T�C�Y��ێ�����
int g_WindowWidth = 512;
int g_WindowHeight = 512;

// �I���������̂�ID�ԍ��i0,1,2�j��Ԃ�
// �I���������̂������ꍇ�� -1 ��Ԃ�
int pickSphere(int x, int y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// �Ɩ����ʂ𖳂����ĒP�F�ŕ`�悷��
	glDisable(GL_LIGHTING);

	// 3�̋��̂�`�悷��
	for (int i = 0; i < 3; i++) {
		// RGB��R�����ɋ��̂�ID��ݒ肷��(unsigned byte�^)
		glColor3ub(i, 0, 0);
		g_Sphere[i].display();
	}

	// �����ƃX���C�h���Q�l�Ɏ��̂悤�ȃv���O�����R�[�h��ǉ�����
	// ��glReadPixels �֐��������āA�N���b�N�����ʒu�����F�ł��邩�擾����
	// ���擾�����F�����āA�ǂ̋��̂�I�����������肵�A����ID�� return ����B
	GLubyte pixelColor[3];
  glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelColor);
	
	return (pixelColor[0] == 255) ? -1 : (int)pixelColor[0];
	// ���K�؂Ȓl��Ԃ��悤�ɂ���
}

// �`��֐�
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// �������e�ϊ��s��̐ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, g_WindowWidth / (float)g_WindowHeight, 1.0, 100.0);

	// �J�����r���[���W�ւ̕ϊ��s��̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);

	// 3�̋��̂�`��
	for (int i = 0; i < 3; i++) {
		// ���̂��ƂɐF��ύX����
		glMaterialfv(GL_FRONT, GL_DIFFUSE, g_Sphere[i].color);

		// ���̂̕`����s��
		g_Sphere[i].display();
	}

	// �����I������Ă����Ԃł���΁A�N���b�N���W�Ɋւ������\������
	if(g_SelectedSphereID != -1) {
		// �Ɩ����ʂȂ��ŒP�F�`��
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		// �N���b�N���W�ɓ_��`��
		glColor3f(1, 0, 0);
		glPointSize(5.f);
		glBegin(GL_POINTS);
		glVertex3d(g_SelectedPos.x, g_SelectedPos.y, g_SelectedPos.z);
		glEnd();

		// ������`�悷��ʒu�̎w��
		glRasterPos3d(g_SelectedPos.x, g_SelectedPos.y, g_SelectedPos.z);

		// �\�����镶����̍\�z
		// ������ sprintf_s �ŃR���p�C���G���[�ɂȂ�ꍇ�� sprintf ���g������
		char str[256];
		sprintf(str, "sphere[%d] (%lf, %lf, %lf)", g_SelectedSphereID,
				g_SelectedPos.x, g_SelectedPos.y, g_SelectedPos.z);

		// �������1�������`��
		for (int i = 0; str[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
		}
	}

	glutSwapBuffers();
}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ�Ƃ��̏���
void resize(int w, int h) {
	if (h < 1) return;

	glViewport(0, 0, w, h);

	g_WindowWidth = w;
	g_WindowHeight = h;
}

// �}�E�X�J�[�\���ʒu�Ɋ�Â��I������
void MousePick(int x, int _y) {

	printf("MousePick(%d, %d)\n", x, _y);

	// �}�E�X�N���b�N�œ�������W�͍��㌴�_�Ȃ̂� OpenGL�̍��W�n�ƍ��킹�邽�߂�y���W�𔽓]����
	const int y = g_WindowHeight - _y;

	g_SelectedSphereID = pickSphere(x, y);

	// �����I������Ă��Ȃ��Ȃ牽�����Ȃ�
	if (g_SelectedSphereID == -1) return;

	// �N���b�N�����ꏊ�̍��W�l�i3�������W�j���擾����

	double M[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, M);
	double P[16];
	glGetDoublev(GL_PROJECTION_MATRIX, P);
	int V[4];
	glGetIntegerv(GL_VIEWPORT, V);

	float z;
	glReadPixels(x, y, 1,1,GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	double objx, objy, objz;
	gluUnProject(x, y, z, M, P, V, &objx, &objy, &objz);
	g_SelectedPos = Vector3d (objx, objy, objz);

	// �����ƃX���C�h���Q�l�Ɏ��̂悤�ȃv���O�����R�[�h��ǉ�����
	// �����݂̃��f���r���[�s����擾����
	// �����݂̓������e�s��̎擾���擾����
	// �����݂̃r���[�|�[�g�̏����擾
	// ���}�E�X�N���b�N�����ʒu�̉��s�����iz�l�j���擾����
	// ����L�̏��Ɋ�Â��āA�N���b�N�����ʒu�̃��[���h���W���擾����
	// ���擾�����l�́Ag_SelectedPos �Ɋi�[���Ă����i���\���̎��Ɏg�p����j

}

// �}�E�X�N���b�N�̃C�x���g����
void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) MousePick(x, y); 
	glutPostRedisplay();
}

// �}�E�X�h���b�O�̃C�x���g����
void motion(int x, int y) {
	MousePick(x, y);
	glutPostRedisplay();
}

// �L�[�������ꂽ�Ƃ��̃C�x���g����
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


void init() {
	// 3�̋��̂̈ʒu�ƐF��ݒ肵�Ă���
	g_Sphere[0].position.set(-5, 0, 0);
	g_Sphere[1].position.set( 0, 0, 0);
	g_Sphere[2].position.set( 5, 0, 0);
	g_Sphere[0].setColor(1, 0, 0);
	g_Sphere[1].setColor(0, 1, 0);
	g_Sphere[2].setColor(0, 0, 1);

	glClearDepth(1000.0);
	glClearColor(1, 1, 1, 1); // �w�i�̐F�𔒂ɐݒ�

	// �Ɩ��̐ݒ�
	float lightAmbientColor[] = { 0.2f, 0.2f, 0.2f, 0.0f };
	float lightDiffuseColor[] = { 1.f, 1.f, 1.f, 0.0f };
	float lightSpecularColor[] = { 0.4f, 0.4f, 0.4f, 0.0f };
	float lightPosition[] = { 0.0f, 30.0f, 30.0f, 0.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// �ގ��̐ݒ�
	float specularColor[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuseColor[] = { 1.f, 0.f, 0.f, 1.f };
	float shininess = 64.f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
}

int main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(g_WindowWidth, g_WindowHeight);
	glutCreateWindow("Mouse Picking");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();

	return 0;
}

