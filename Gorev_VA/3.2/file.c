#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 0.000001

double min_value(double(*f) (double), double a, double b, int* Error);
double min_value(double(*f) (double), double a, double b, int* Error)
{
	double x0, x1, x2, f0, f1, f2;
	int q;
	if (a > b)
	{
		x1 = a;
		a = b;
		b = x1;
	}
	x0 = b - (b - a) * (sqrt(5) - 1) * 0.5;
	q = 1;
	for (int i = 1; i <= 1000; i++)
	{
		if (q)
			x1 = a + (b - a) * (sqrt(5) - 1) * 0.5;
		else
			x0 = b - (b - a) * (sqrt(5) - 1) * 0.5;

		if ((*f)(x0) >= (*f)(x1))
		{
			a = x0;
			x0 = x1;
			q = 1; // �� ��������� ���� ����� ������� �1
		}
		else
		{
			b = x1;
			x1 = x0;
			q = 0; // �� ��������� ���� ����� ������� �0
		}
		printf("  %f %f %f %f\n", a, x0, x1, b);
		if ((b - a) < eps)
			break;
	}

	if ((b - a) >= eps)
	{
		*Error = 1;
		return 0.0;
	}
	else
	{
		x2 = x0;
		x0 = a;
		x1 = b;
		f0 = (*f)(x0);
		f1 = (*f)(x1);
		f2 = (*f)(x2);
		a = x2 - ((x2 - x1) * (x2 - x1) * (f2 - f0) - (x2 - x0) * (x2 - x0) * (f2 - f1)) / ((x2 - x1) * (f2 - f0) - (x2 - x0) * (f2 - f1)) * 0.5;
		*Error = 0;
		return f(a);
	}
}

double F1(double x);
double F1(double x)
{
	return x * x * x - x;
}

double F2(double x);
double F2(double x)
{
	return sin(x);
}

double F3(double x);
double F3(double x)
{
	return x + 1.5;
}

int main(void)
{
	int* Error;
	Error = (int*)malloc(1 * sizeof(int));
	printf("f(x) = x^3 - x at [0, 2]\n");
	printf(" calculated min value: %f\n actual min value:     %f\n", min_value(F1, 0.0, 2.0, Error), -0.3849001795);

	printf("f(x) = sin(x) at [3, 6]\n");
	printf(" calculated min value: %f\n actual min value:     %f\n", min_value(F2, 3.0, 6.0, Error), -1.0);

	printf("f(x) = x^3 - x at [0, 1]\n");
	printf(" calculated min value: %f\n actual min value:     %f\n", min_value(F3, 0.0, 2.0, Error), 1.5);
	return 0;
}
