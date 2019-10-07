#include <iostream>
#include <stdio.h>
#include <assert.h>
class String {
	
public:
	char* str;
	int nlength;
	String(const char*);
	String(const String&);
	~String(void) { delete[]str; }
	int length() { return nlength; }
	String operator+ (const String&);
	bool operator== (const char*);
	void clear();
};
