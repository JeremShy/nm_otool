#include <stdio.h>

int a = 0;
extern int b;

int main()
{
	int var;
	const int iconst = 2;
	char *str = "Hello, world!\n";

	var = 3;
	printf("%s\n", str);
	return (0);
}
