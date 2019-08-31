#include <iostream>

unsigned int countNumberOfBitSet(int n)
{
	unsigned int count = 0; 
	while(n)
	{
		count  = (n & 1 == 1) ? count + 1 : count;
		n = n >> 1;
	}
	return count;
}

int main()
{
	printf("Number of bit set in 6 is %d\n", countNumberOfBitSet(6));
	printf("Number of bit set in 13 is %d\n", countNumberOfBitSet(13));
	return (0);
}
