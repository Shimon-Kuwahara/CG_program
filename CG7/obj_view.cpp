#include <cstdio>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <cfloat>
#include <GLUT/GLUT.h>

using namespace std;

class Vertex;
class Triangle;
class Model;

class Vec3 {
public:
	double x, y, z;
	Vec3( void );
	Vec3( const double& _x, const double& _y, const double& _z );
	Vec3& operator = ( const Vec3& );
	Vec3& operator+=( const Vec3& );
	Vec3& operator-=( const Vec3& );
  
	double length();
	double length2();
	double angle(const Vec3& v);
	void set( const double& _x, const double& _y, const double& _z );
	void normalize();
	void debugout();
	Vec3(const Vec3& v);
	void set(const Vec3& v);
	void sub( const Vec3& v0, const Vec3& v1);
	void sub( const Vec3& v);
	void add( const Vec3& v);
	void scale( const double s);
	void cross( const Vec3& v0, const Vec3& v1);
	double dot( const Vec3& v);
};

inline Vec3::Vec3( const Vec3& v ) { x = v.x; y = v.y; z = v.z;}

inline Vec3::Vec3( void ) { x = 0; y = 0; z = 0;}
inline Vec3::Vec3( const double& _x, const double& _y, const double& _z ) { x = _x; y = _y; z = _z; }
inline Vec3& Vec3::operator =  ( const Vec3& v ){ x = v.x; y = v.y; z = v.z; return *this; }
inline Vec3 operator - ( const Vec3& v ) { return( Vec3( -v.x, -v.y, -v.z ) ); }
inline Vec3& Vec3::operator+=( const Vec3& v ) { x += v.x; y += v.y; z += v.z; return( *this ); }
inline Vec3& Vec3::operator-=( const Vec3& v ) { x -= v.x; y -= v.y; z -= v.z; return( *this ); }
inline Vec3 operator+( const Vec3& v1, const Vec3& v2 ) { return( Vec3( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z ) );}
inline Vec3 operator-( const Vec3& v1, const Vec3& v2 ) { return( Vec3( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z ) );}
inline Vec3 operator*( const double& k, const Vec3& v ) { return( Vec3( k*v.x, k*v.y, k*v.z ) );}
inline Vec3 operator*( const Vec3& v, const double& k ) { return( Vec3( v.x*k, v.y*k, v.z*k ) );}
inline Vec3 operator/( const Vec3& v, const double& k ) { return( Vec3( v.x/k, v.y/k, v.z/k ) );}
//----  内積の定義
inline double operator*( const Vec3& v1, const Vec3& v2 ) { return( v1.x*v2.x + v1.y*v2.y + v1.z*v2.z );}
//----  外積の定義
inline Vec3  operator%( const Vec3& v1, const Vec3& v2 ) { return( Vec3( v1.y*v2.z - v1.z*v2.y,  v1.z*v2.x - v1.x*v2.z,  v1.x*v2.y - v1.y*v2.x ) );}
inline double Vec3::length() { return( sqrt( x*x + y*y + z*z ) );}
inline double Vec3::length2() { return( x*x + y*y + z*z  );}
inline void Vec3::normalize() { double l = length(); x/=l; y/=l; z/=l;}
inline void Vec3::debugout() { printf("Vec3(%f %f %f)\n", x, y, z );}
inline void Vec3::set( const double& _x, const double& _y, const double& _z ) { x = _x; y = _y; z = _z; }
inline double Vec3::angle(const Vec3& v) {
        Vec3 c = (*this)%v;
        return atan2(c.length(), (*this)*v);
}

class Vertex {
public:
	Vec3 p;

	Vertex(double _x, double _y, double _z) {
		p.x = _x;
		p.y = _y;
		p.z = _z;
	}
};

class Triangle {
public:
	Vertex* vertices[3];
	Vec3 normal;

	Triangle(Vertex *v0, Vertex *v1, Vertex *v2 ) {
		vertices[0] = v0;
		vertices[1] = v1;
		vertices[2] = v2;
	}

	void setNormal() {
		normal = (vertices[1]->p - vertices[0]->p) % (vertices[2]->p - vertices[0]->p);
		normal.normalize();
	}
};

class Model {
public:
	std::list<Triangle*> triangles;
	std::list<Vertex*> vertices;

public:
	void sizeNormalize() {
		std::list<Vertex*>::iterator it_v;
		Vec3 minV(DBL_MAX, DBL_MAX, DBL_MAX);
		Vec3 maxV(-DBL_MAX, -DBL_MAX, -DBL_MAX);
		for( it_v = vertices.begin(); it_v != vertices.end(); it_v++ ) {
			minV.x = min(minV.x, (*it_v)->p.x);
			minV.y = min(minV.y, (*it_v)->p.y);
			minV.z = min(minV.z, (*it_v)->p.z);
			maxV.x = max(maxV.x, (*it_v)->p.x);
			maxV.y = max(maxV.y, (*it_v)->p.y);
			maxV.z = max(maxV.z, (*it_v)->p.z);
		}

		Vec3 center = 0.5*(minV + maxV);
		double size = (maxV - minV).length();
		for( it_v = vertices.begin(); it_v != vertices.end(); it_v++ ) {
			(*it_v)->p = ((*it_v)->p - center) / size / 2;
		}
	}

	void addFace( Vertex *v0, Vertex *v1, Vertex *v2 ) {
		Triangle *tri = new Triangle(v0, v1, v2);
		triangles.push_back( tri );
		tri->setNormal();
	}

};

	
Model *g_model;
bool bShowVertex;
double rotateAngleH_deg; // 画面水平方向の回転角度
double rotateAngleV_deg; // 縦方向の回転角度
int preMousePositionX;   // マウスカーソルの位置を記憶しておく変数
int preMousePositionY;   // マウスカーソルの位置を記憶しておく変数
bool mouseLeftPressed;
bool mouseRightPressed;
double modelScale;

const GLfloat lightDiffuse[] = { 1 , 1 , 1 , 1 };
const GLfloat materialDiffuseFront[] = { 0 , 1.0 , 0 , 1};
const GLfloat materialDiffuseBack[] = { 1.0 , 1.0 , 0 , 1};
const GLfloat lightPosition[] = { 50 , 50 , 50 , 0 };


Model* readFile(const char* filename) {

	std::ifstream ifs(filename);
	std::string token(BUFSIZ, '\0');

	Model *model = new Model();
	std::vector<Vertex*> vertices; // インデックスで頂点を参照するためのvector

	while (!(ifs >> token).fail()) {
		if (token[0] == '#') {
			ifs.ignore(BUFSIZ, '\n');
			continue;
		}

		if (token == "v") {
			double x, y, z;
			ifs >> x >> y >> z;
			ifs.ignore(BUFSIZ, '\n');

			Vertex *v = new Vertex(x, y, z);
			model->vertices.push_back(v);
			vertices.push_back(v);	
		}
		else if (token == "f"){
			int index0, index1, index2;
			ifs >> index0 >> index1 >> index2;
			ifs.ignore(BUFSIZ, '\n');
		
			if(index0 <= vertices.size() && index1 <= vertices.size() && index2 <= vertices.size()) {
				if(index0 != index1 && index1 != index2 && index2 != index1) {
					model->addFace( vertices[index0-1], vertices[index1-1], vertices[index2-1] );
				}
			}

		} else {
			ifs.ignore(BUFSIZ, '\n'); 
		}
	}

	model->sizeNormalize();
	return model;
}

void drawModel() {
	std::list<Vertex*>::iterator it_v;

	// 頂点の描画
	if(bShowVertex) {
		glDisable(GL_LIGHTING);
		glColor3d(0,0,0);
		glPointSize(5);
		glBegin(GL_POINTS);
		for( it_v = g_model->vertices.begin(); it_v != g_model->vertices.end(); it_v++ ) {
			glVertex3d((*it_v)->p.x, (*it_v)->p.y, (*it_v)->p.z);
		}
		glEnd();
	}

	// 稜線の描画
	glDisable(GL_LIGHTING);
	glColor3d(0,0,0);
	std::list<Triangle*>::iterator it_t;
	for( it_t = g_model->triangles.begin(); it_t != g_model->triangles.end(); it_t++ ) {
		glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 3; i++) {
			glVertex3d((*it_t)->vertices[i]->p.x, (*it_t)->vertices[i]->p.y, (*it_t)->vertices[i]->p.z);
		}
		glEnd();
	}


	// 面の描画
	// glEnable(GL_LIGHTING); // 照明効果を入れる場合はコメントアウトをはずす

	// 表面の描画
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuseFront);

	for( it_t = g_model->triangles.begin(); it_t != g_model->triangles.end(); it_t++ ) {
		glColor3f((*it_t)->normal.x * 0.5 + 0.5, (*it_t)->normal.y * 0.5 + 0.5, (*it_t)->normal.z * 0.5 + 0.5);
		glBegin(GL_POLYGON);
		//glNormal3f( (*it_t)->normal.x, (*it_t)->normal.y, (*it_t)->normal.z); // 照明効果を入れる場合はコメントアウトをはずす
		for(int i = 0; i < 3; i++) {
			glVertex3d((*it_t)->vertices[i]->p.x, (*it_t)->vertices[i]->p.y, (*it_t)->vertices[i]->p.z);
		}
		glEnd();
	}

	// 裏面の描画
	glColor3f(0.5, 0.5, 0.5);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuseBack);
	for( it_t = g_model->triangles.begin(); it_t != g_model->triangles.end(); it_t++ ) {
		glBegin(GL_POLYGON);
		//glNormal3f( -(*it_t)->normal.x, -(*it_t)->normal.y, -(*it_t)->normal.z); // 照明効果を入れる場合はコメントアウトをはずす

		for(int i = 2; i >= 0; i--) {
			glVertex3d((*it_t)->vertices[i]->p.x, (*it_t)->vertices[i]->p.y, (*it_t)->vertices[i]->p.z);
		}
		glEnd();
	}


}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(0, 0.0, -1.0 / modelScale);

	glLightfv(GL_LIGHT0 , GL_POSITION , lightPosition);

	glRotated(rotateAngleV_deg, 1.0, 0.0, 0.0);
	glRotated(rotateAngleH_deg, 0.0, 1.0, 0.0);

	drawModel();

	glutSwapBuffers();
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'v') {
		bShowVertex = !bShowVertex;
	}

	glutPostRedisplay();

}

void mouse(int button, int state, int x, int y) {
	mouseLeftPressed = mouseRightPressed = false;

	switch (button) {
	case GLUT_LEFT_BUTTON:
		preMousePositionX = x;
		preMousePositionY = y;
		mouseLeftPressed = true;
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		preMousePositionX = x;
		preMousePositionY = y;
		mouseRightPressed = true;
		break;
	default:
		 break;
	}
}


void motion(int x, int y) {
	int diffX = x - preMousePositionX;
	int diffY = y - preMousePositionY;

	if(mouseLeftPressed) {
		rotateAngleH_deg += diffX * 0.3;
		rotateAngleV_deg += diffY * 0.3;
	} else if(mouseRightPressed) {
		double scale = 1.0 + diffX * 0.01;
		modelScale *= scale;
	}

	preMousePositionX = x;
	preMousePositionY = y;
	glutPostRedisplay();
}


void init(void) {
	modelScale = 1.0;
	bShowVertex = true;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	glLightfv(GL_LIGHT0 , GL_DIFFUSE , lightDiffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    glEnable (GL_POLYGON_OFFSET_FILL);
    glPolygonOffset (1.0, 0);

	glEnable(GL_CULL_FACE);

}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: specify an objfile\n");
		return 1;
	}

	g_model = readFile(argv[1]);

	glutInit(&argc, argv);
	glutInitWindowSize(600,600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	init();
	glutMainLoop();

	return 0;
}
