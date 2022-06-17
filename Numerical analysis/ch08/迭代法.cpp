#include <iostream >
#include"diedaifa.h"
int main()
{
	double arr[N][N] = { {1,2,3,4,5},{-2,3,4,5,6},{-3,-4,5,6,7},{-4,-5,-6,7,8},{-5,-6,-7,-8,9} };
	double arr1[N][1] = { 55,66,63,36,-25 };
	guassai(arr1, arr);
	jacobi(arr1, arr);
	return 0;
}
