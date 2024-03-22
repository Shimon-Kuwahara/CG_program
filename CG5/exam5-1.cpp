#include <cstdlib>
#include <cmath>
#include <vector>

// 2次元ベクトルを扱うためのクラス
class Vector2d {
public:
	double x, y;
	Vector2d() { x = y = 0; }
	Vector2d(double _x, double _y) { x = _x; y = _y; }
	void set(double _x, double _y) { x = _x; y = _y; }

	// 長さを1に正規化する
	void normalize() {
		double len = length();
		x /= len; y /= len; 
	}

	// 長さを返す
	double length() { return sqrt(x * x + y * y); }

	// s倍する
	void scale(const double s) { x *= s; y *= s; }

	// 加算の定義
	Vector2d operator+(Vector2d v) { return Vector2d(x + v.x, y + v.y); }

	// 減算の定義
	Vector2d operator-(Vector2d v) { return Vector2d(x - v.x, y - v.y); }

	// 内積の定義
	double operator*(Vector2d v) { return x * v.x + y* v.y; }

	// 代入演算の定義
	Vector2d& operator=(const Vector2d& v){ x = v.x; y = v.y; return (*this); }

	// 加算代入の定義
	Vector2d& operator+=(const Vector2d& v) { x += v.x; y += v.y; return (*this); }

	// 減算代入の定義
	Vector2d& operator-=(const Vector2d& v) { x -= v.x; y -= v.y; return (*this); }

	// 値を出力する
	void print() { printf("Vector2d(%f %f)\n", x, y); }
};

// マイナスの符号の付いたベクトルを扱えるようにするための定義 例：b=(-a); のように記述できる
Vector2d operator-( const Vector2d& v ) { return( Vector2d( -v.x, -v.y ) ); }

// ベクトルと実数の積を扱えるようにするための定義 例： c=5*a+2*b; c=b*3; のように記述できる
Vector2d operator*( const double& k, const Vector2d& v ) { return( Vector2d( k*v.x, k*v.y ) );}
Vector2d operator*( const Vector2d& v, const double& k ) { return( Vector2d( v.x*k, v.y*k ) );}

// ベクトルを実数で割る操作を扱えるようにするための定義 例： c=a/2.3; のように記述できる
Vector2d operator/( const Vector2d& v, const double& k ) { return( Vector2d( v.x/k, v.y/k ) );}

int main(int argc, char**argv) {
	// =====================================================
	// 2次元ベクトルクラス Vector2d の使い方の例
	// =====================================================

	// 2次元ベクトル(1, 2)の作成
	Vector2d v0(1, 2);

	// 作成した2次元ベクトルのx,y座標値を確認
	v0.print();

	// 2次元ベクトル(2, 4)の作成
	Vector2d v1(2, 4);

	// ベクトルの加算
	Vector2d v2 = v0 + v1;

	// 加算した結果の確認
	v2.print();

	// ベクトルの減算
	Vector2d v3 = v1 - v0;

	// 減算した結果の確認
	v3.print();

	// ベクトルの長さの確認
	printf("v3.length() = %lf\n", v3.length());

	// ベクトルのスカラー倍
	v3 = 5.0 * v3;

	// スカラー倍した結果の確認
	v3.print();

	// ベクトルの長さの正規化
	v3.normalize();

	// 正規化した結果の確認
	v3.print();

	// ベクトルの長さの確認
	printf("v3.length() = %lf\n", v3.length());


	// =====================================================
	// std::vector を要素数を変更可能な配列として使う例
	// =====================================================

	std::vector<Vector2d> vec; // 配列の宣言 （Vector2d 型のオブジェクトを格納できる）
	vec.push_back(v0); // 配列の末尾に v0 を追加
	vec.push_back(v1); // 配列の末尾に v1 を追加
	vec.push_back(v2); // 配列の末尾に v2 を追加

	printf("vec.size() = %d\n", vec.size()); // 配列に入っている要素数を確認

	// 配列の先頭要素を取得
	Vector2d firstElement = vec[0];

	// 取得した要素の値を出力
	printf("firstElement=(%lf, %lf)\n", firstElement.x, firstElement.y);

	// 全ての要素を出力
	for(unsigned int i = 0; i < vec.size(); i++) {
		printf("vec[%d]=(%lf, %lf)\n", i, vec[i].x, vec[i].y);
	}


	// ★課題：以下にコメント文で指示する内容のプログラムコードを追加すること
	
	// (1) vec を空にする

	vec.clear();

	// (2) 次の2次元ベクトルを vec に格納する  
	// (5.0, 2.0), (3.2, -2.3), (4.1, 9.2), (-2.0, 4.0), (0.0, -2.7)

	vec.push_back(Vector2d(5.0, 2.0));
	vec.push_back(Vector2d(3.2, -2.3));
	vec.push_back(Vector2d(4.1, 9.2));
	vec.push_back(Vector2d(-2.0, 4.0));
	vec.push_back(Vector2d(0.0, -2.7));

	// (3) 上記の2次元ベクトルを全て加算した結果を Vector2d vecSum に格納する

	Vector2d vecSum(0.0, 0.0);
	for(unsigned int i = 0; i < vec.size(); i++) {
		vecSum += vec[i];
	}
	// (4) vecSum の内容(x,yの値)と、vecSum の長さを出力する

	printf("vecSum=(%lf, %lf)\n", vecSum.x, vecSum.y);

	printf("vecSum.length() = %lf\n", vecSum.length());
	// Visual Studio でコンソールがすぐに閉じないようにするため
	// system("pause"); 

	return 0;
}
