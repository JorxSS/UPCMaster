#include <iostream>
using namespace std;

template < typename type >
class Vec3 {
public:
	type x, y, z;
	Vec3(): x(0), y(0), z(0) {}
	Vec3(type a, type b, type c): x(a),y(b),z(c) {}
	Vec3(const Vec3 &b): x(b.x), y(b.y), z(b.z) {}
	void Normalize();
	double distance_to(const Vec3<type> &b);
	Vec3<type> operator+(Vec3<type> right);
};

template <typename type>
void Vec3<type>::Normalize() {
	double magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

template <typename type>
double Vec3<type>::distance_to(const Vec3<type> &b) {
	return sqrt(pow(x - b.x, 2.0) + pow(y - b.y, 2.0) + pow(z - b.z, 2.0));
}

template <typename type>
Vec3<type> Vec3<type>::operator+(Vec3<type> right) {
	return Vec3<type>(x + right.x, y + right.y, z + right.z);

}