#include <iostream>
#include <cstring>
using namespace std;

unsigned int countNumberOfBitSet(int n)
{
	unsigned int count = 0; 
	while(n)
	{
		count  = n & 1 == 1 ? count + 1 : count;
		n = n >> 1;
	}
	return count;
}

int main()
{
	printf("%d", countNumberOfBitSet(6));
	return (0);
}
