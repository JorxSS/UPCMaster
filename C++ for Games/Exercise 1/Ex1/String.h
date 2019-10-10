
class String {
	
public:
	char* str;
	int nlength;
	String(const char*);
	String(const String&);
	~String(void) { delete[]str; }
	int length() const { return nlength; }
	String operator+ (const String&);
	String operator=(const char * src);
	bool operator== (const char*);
	void clear();
};
