
template < typename type >
class Vec3 {
public:
	type x, y, z;
	Vec3(): x(0), y(0), z(0) {}
	Vec3(type x, type y, type z): x(x),y(y),z(z) {}
	Vec3(const Vec3 &b): x(b.x), y(b.y), z(b.z) {}
	void Normalize() const;
	double distance_to(const Vec3<type> &b);
	Vec3<type> operator+(Vec3<type> right);
};

template <typename type>
void Vec3<type>::Normalize() const {
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