#include <stdlib.h>
#include <stdio.h>

int[][] recognize(char array[], size_t lines, size_t cols)
{
	int result[lines*cols][2];
	int count = 0;
	int line = 0;
	for(int i = 0; i<lines; i++)
	{
		
		
		if (line == 1)
		{
			result[count] = -1;
		}
		line = 1;
		for(int j = 0; j<cols; j++)
		{
			if (array[j + i * cols]==1)
			{
				line = 0;
				int coord[] = around(array[], cols, i, j);
			}
		}
}

int[] around(char array[], size_t cols, size_t i, size_t j)
{
	int result[];
	if(array[j+1 + i * cols] == 1)
	{
		result[0] = i;
		result[1] = j+1;
		return result;
	}
	if(array[j-1 + i * cols] == 1)
        {
                result[0] = i;
                result[1] = j-1;
                return result;
        }
	if(array[j + (i+1) * cols] == 1)
        {
                result[0] = i+1;
                result[1] = j;
                return result;
        }
	if(array[j + (i-1) * cols] == 1)
        {
                result[0] = i-1;
                result[1] = j;
                return result;
        }
	else
	{
                result[0] = -1;
                result[1] = -1;
                return result;
	}
}
