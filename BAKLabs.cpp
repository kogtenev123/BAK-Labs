#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Spring {
public:
	Spring(double c, double x) {
		k = c;
		lo = x;
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
	void fix(double i, double j) {
		x = i;
		y = j;
		fixed = true;
	}
	bool load(float m) {
		if (m1 == 0) {
			m1 = m;
			return true;
		}
		else if(m2 == 0 && fixed == false) {
			m2 = m;
			return true;
		}
		return false;
	}
private:
	float k; //∆есткость пружины
	float lo, l; // длина и начальна€ длина
	float x, y; // оординаты подвеса
	float m1, m2; //массы грузов
	bool fixed;	//зафиксирована ли пружина
};


class Point {
public:
	Point() {
		m = 0;
	}
	Point(double r, vector<double> v) {
		m = r;
		c = v;
	}
	float Weight() {
		return m;
	}
	void hook(Spring& spring) {
		if (spring.load(m))
			s.push_back(spring);
	}
private:
	vector<Spring> s; //пружины, к которым подвешена данная точка
	vector<double> c;//координаты точки
	float m;
};



int main() {
	Spring s(40, 0.15);
	vector<double> v;
	v.push_back(0);
	v.push_back(0);
	Point p(0.2, v);
	const double dt = 0.001, g = 9.8;
	double ddl, dl = 0;
	double l = s.length();
	for (int i = 0; i < 1000; i++) {
		ddl = (g - s.Stif() * (s.length() - s.length0()) / p.Weight()) * dt * dt;
		dl += ddl;
		s.deform(dl);
		cout << s.length() << endl;
	}
	return 0;
}
