#include<stdio.h>

int main(void)
{
	float         a;
	unsigned int  *p;
	int bin[32];
	int i;

	printf("変換する数字を入力してください:");
	scanf("%f", &a);

    printf("%li\n", sizeof(float));
    printf("%li\n", sizeof(unsigned int));
	p = (unsigned int *)&a;
	printf("%13.10e : %08X\n", a, *p);

	for (i = 0; i < 32; i++)
	{
		bin[i] = *p % 2;
		*p = *p / 2;
	}
	for (; i > 0; i--)
	{
		printf("%d", bin[i]);
	}
	printf("\n");

	return 0;
}