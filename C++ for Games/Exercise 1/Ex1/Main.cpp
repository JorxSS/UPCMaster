#include "Vec3.h"
#include "String.h"
#include <iostream> 

int main() {

	Vec3<int> a;
	Vec3<int> b(1, 0, 1);
	Vec3<int> c = a + b;
	Vec3<double> t(18, 25, 32);
	Vec3<double> r(54, 28, 57);
	r.Normalize();
	double dist = r.distance_to(t);

	String d("ou");
	String e("mama");
	String h(d);
	String f = d + e;
	printf(f.str);
	String m("hola");
	h.clear();
	if (f == "oumama") {
		printf("IT WORKS 1st attempt");
	}
	else {
		printf("didn't work 1st attempt");
	}
	if (m == "me") {
		printf("IT WORKS 2nd attempt");
	}else {
		printf("didn't work 2nd attempt");
	}

}