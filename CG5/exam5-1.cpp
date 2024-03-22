#include <cstdlib>
#include <cmath>
#include <vector>

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

int main(int argc, char**argv) {
	// =====================================================
	// 2�����x�N�g���N���X Vector2d �̎g�����̗�
	// =====================================================

	// 2�����x�N�g��(1, 2)�̍쐬
	Vector2d v0(1, 2);

	// �쐬����2�����x�N�g����x,y���W�l���m�F
	v0.print();

	// 2�����x�N�g��(2, 4)�̍쐬
	Vector2d v1(2, 4);

	// �x�N�g���̉��Z
	Vector2d v2 = v0 + v1;

	// ���Z�������ʂ̊m�F
	v2.print();

	// �x�N�g���̌��Z
	Vector2d v3 = v1 - v0;

	// ���Z�������ʂ̊m�F
	v3.print();

	// �x�N�g���̒����̊m�F
	printf("v3.length() = %lf\n", v3.length());

	// �x�N�g���̃X�J���[�{
	v3 = 5.0 * v3;

	// �X�J���[�{�������ʂ̊m�F
	v3.print();

	// �x�N�g���̒����̐��K��
	v3.normalize();

	// ���K���������ʂ̊m�F
	v3.print();

	// �x�N�g���̒����̊m�F
	printf("v3.length() = %lf\n", v3.length());


	// =====================================================
	// std::vector ��v�f����ύX�\�Ȕz��Ƃ��Ďg����
	// =====================================================

	std::vector<Vector2d> vec; // �z��̐錾 �iVector2d �^�̃I�u�W�F�N�g���i�[�ł���j
	vec.push_back(v0); // �z��̖����� v0 ��ǉ�
	vec.push_back(v1); // �z��̖����� v1 ��ǉ�
	vec.push_back(v2); // �z��̖����� v2 ��ǉ�

	printf("vec.size() = %d\n", vec.size()); // �z��ɓ����Ă���v�f�����m�F

	// �z��̐擪�v�f���擾
	Vector2d firstElement = vec[0];

	// �擾�����v�f�̒l���o��
	printf("firstElement=(%lf, %lf)\n", firstElement.x, firstElement.y);

	// �S�Ă̗v�f���o��
	for(unsigned int i = 0; i < vec.size(); i++) {
		printf("vec[%d]=(%lf, %lf)\n", i, vec[i].x, vec[i].y);
	}


	// ���ۑ�F�ȉ��ɃR�����g���Ŏw��������e�̃v���O�����R�[�h��ǉ����邱��
	
	// (1) vec ����ɂ���

	vec.clear();

	// (2) ����2�����x�N�g���� vec �Ɋi�[����  
	// (5.0, 2.0), (3.2, -2.3), (4.1, 9.2), (-2.0, 4.0), (0.0, -2.7)

	vec.push_back(Vector2d(5.0, 2.0));
	vec.push_back(Vector2d(3.2, -2.3));
	vec.push_back(Vector2d(4.1, 9.2));
	vec.push_back(Vector2d(-2.0, 4.0));
	vec.push_back(Vector2d(0.0, -2.7));

	// (3) ��L��2�����x�N�g����S�ĉ��Z�������ʂ� Vector2d vecSum �Ɋi�[����

	Vector2d vecSum(0.0, 0.0);
	for(unsigned int i = 0; i < vec.size(); i++) {
		vecSum += vec[i];
	}
	// (4) vecSum �̓��e(x,y�̒l)�ƁAvecSum �̒������o�͂���

	printf("vecSum=(%lf, %lf)\n", vecSum.x, vecSum.y);

	printf("vecSum.length() = %lf\n", vecSum.length());
	// Visual Studio �ŃR���\�[���������ɕ��Ȃ��悤�ɂ��邽��
	// system("pause"); 

	return 0;
}
