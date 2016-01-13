#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "17";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2008";
	static const double UBUNTU_VERSION_STYLE = 8.05;
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 1;
	static const long REVISION = 2;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 4;
	#define RC_FILEVERSION 1,0,1,2
	#define RC_FILEVERSION_STRING "1, 0, 1, 2\0"
	static const char FULLVERSION_STRING[] = "1.0.1.2";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 1;
	

#endif //VERSION_h
