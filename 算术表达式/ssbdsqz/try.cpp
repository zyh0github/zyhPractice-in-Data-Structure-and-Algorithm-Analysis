#include<iostream>
#include<stdlib.h>
using namespace std;

int main()
{
	char a[]={"123asd.3255 5.4a 4.3 a"};
	double d;
	d=atof(a);
	
	printf("%lf",d);
	
	return 0;
}
