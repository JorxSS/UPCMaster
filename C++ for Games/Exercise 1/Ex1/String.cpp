#include "String.h"

String::String(const char* src) {
	assert(src != NULL);
	nlength = strlen(src) + 1;
	str = new char[nlength];
	char* ptr = str;
	while (*ptr++ = *src++);
}

String::String(const String &src) {
	nlength = src.nlength;
	str = new char[nlength];
	char* ptr = str;
	char* aux = src.str;
	while (*ptr++ = *aux++);
}

String String::operator+(const String &b)
{
	char* nstr = new char[((nlength + b.nlength) - 1)];
	char* ptr = nstr;
	char* src = str;
	while (*ptr++ = *src++);
	*ptr--;
	src = b.str;
	while (*ptr++ = *src++);
	return String(nstr);
}

String String::operator=(const char* src)
{
	assert(src != NULL);
	nlength = strlen(src) + 1;
	str = new char[nlength]; //memory leak
	char* ptr = str;
	while (*ptr++ = *src++);
}


bool String::operator== (const char* src) {

	assert(src != NULL);
	char* ptr = str;
	while (*ptr && *src && *ptr == *src) { ++ptr; ++src; }
	int ret = (unsigned char)(*ptr) - (unsigned char)(*src);
	return ret==0 ;
}

void String::clear() {
	str = new char[0]; // posarla a 0
	nlength = 0;
}