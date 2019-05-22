#include <stdio.h>
#include <stdlib.h>

static int reverse(int x)
{
	int sign = x < 0 ? -1 : 1;
	unsigned int v = 0;
	if (x == 0 || x == -2147483648 || x == 2147483647)
		return 0;
	if (sign < 0)
		x = -x;
	while (x != 0) {
		unsigned int m = x / 10;
		unsigned int k = m * 10;
		unsigned int r = x - k;
		unsigned int p = v / 10;
		v = (v * 10) + r;
		if ((v / 100) != p)
			return 0;
		x = m;
	}
	if (v > 2147483647)
		return 0;
	return sign * (int)v;
}
//
//int main(int argc, char *argv[])
//{
//	long v[] = {123, 321, -120, 1534236469, 1563847412};
//	int i;
//
//	for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++)
//		printf("v %d -> %d\n", (long)v[i], reverse((int)v[i]));
//	return 0;
//}
