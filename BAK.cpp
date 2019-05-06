#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Vector {
	double x, y, z;
	Vector() {
		x = 0;
		y = 0;
		z = 0;
	}
	Vector(double g) {
		x = 0;
		y = g;
		z = 0;
	}  
	Vector(double u, double v) {
		x = u;
		y = v;
		z = 0;
	} 
};

Vector operator+(const Vector& v, const Vector& u) {
	Vector r(v.x + u.x, v.y + u.y);
	return r;
}

Vector operator-(const Vector& v, const Vector& u) {
	Vector r(v.x - u.x, v.y - u.y);
	return r;
}

Vector operator*(const double& a, Vector& u) {
	u.x *= a;
	u.y *= a;
	return u;
}

Vector operator/(Vector& u, const double& a) {
	if (a != 0) {
		u.x /= a;
		u.y /= a;
	}
	return u;
}

class Spring {
public:
	Spring(double c, double x, double x0) {
		k = c;
		lo = x0;
		l = x;
		m1 = 0;
		m2 = 0;
	}
	void deform (double dx) {
		l += dx;
	}
	float length() {
		return l;
	}
	float length0() {
		return lo;
	}
	float Stif() {
		return k;
	}
	bool load(double m, Vector v) { //Подвесить груз к пружине!!!!!!!!
		if (m1 == 0) {
			m1 = m;
			r = v;
			return true;
		}
		else if(m2 == 0 && fixed == false) {
			m2 = m;
			return true;
		}
		return false;		
	}
	void fix(double i, double j) {  //зафиксировать пружину в данной точке
		fixed = true;
		Vector v(i, j);
		p = v;
	}
	void move(const Vector& v) {
		r = r + v;
		l = sqrt((p.x - r.x) * (p.x - r.x) + (p.y - r.y) * (p.y - r.y));
	}
	Vector force() {
		Vector f(p.x - r.x, p.y - r.y);
		f = (k * (l - lo) / l) * f;
		return f;
	}
private:
	double k; //Жесткость пружины
	double lo, l; // длина и начальная длина 
	Vector r; //Координаты груза
	double m1, m2; //массы грузов
	bool fixed;	//зафиксирована ли пружина
	Vector p; //координаты точки подвеса
};


class Point {
public:	
	Point() {
		m = 0;
	}
	Point(double p, double v, double u, double V1, double V2) {
		m = p;
		Vector t(v, u);
		Vector q(V1, V2);
		r = t;
		V = q;
	}
	double Weight() {
		return m;
	}
	void hook(Spring& spring) { //подцепить груз к пружине
		if (spring.load(m, r))
			s.push_back(spring);
	}
	void del_hook() { //открепить пружину от груза!!!!
		s.pop_back();
	}
	double loc_x() {
		return r.x;
	}
	double loc_y() {
		return r.y;
	} 	
	void move(Vector dr) { //сдвинуть фиговину
		r = r + dr;
		for(int i = 0; i < s.size(); i++) {
			s[i].move(dr);
		}
	}
	Vector Movement(double dt) {
		double g = -9.8;
		Vector a = Force(g);
		a = a / m;
		Vector V1 = V;
		V = V + dt * a;
		return dt * V1 + (dt * dt / 2) * a;
	}	
private:	
	vector<Spring> s; //пружины, к которым подвешена данная точка
	Vector r;//координаты точки
	double m; //масса
	Vector V; //скорость
	bool side;
	Vector Force(double g) {
		Vector f(g * m);
		for(int i = 0; i < s.size(); i++) {
			Vector u = s[i].force();
			f = f + u;
		}
		return f;		
	} 	
};





int main() {
	Spring s(40, 0.18, 0.15);
	s.fix(2.0, 2.0);
	Point p(0.05, 1.95, 1.82, 0, 0);
	p.hook(s);
	for (int i = 0; i < 5000; i++) {
		Vector v = p.Movement(0.00045);
		p.move(v);
		cout << p.loc_x() << "   " << p.loc_y() << "   " << s.length() << "   " << s.length() - s.length0()  << endl;
	}
	return 0;
} 







