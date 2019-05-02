#include <stdio.h>

int main()
{
	int x, z, vet1[10] = {31, 5, -2, 5, -15, 11, 30, 7, 0, -6}, vet2[10], count;
	for (x = 0; x < 10; x++)
	{
		count = 0;
		for (z = 0; z < 10; z++)
		{
			if (vet1[x] == vet1[z])
				count++;
		}
		vet2[x] = count;
	}
	return 0;
}