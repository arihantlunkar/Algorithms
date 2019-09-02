#include <iostream>
#include <pthread.h> 
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <set>
using namespace std;

int main() {
	
	const char* str = "ABDEFGABEF";
	
	set<char> s; 
	
	int maxCount = -1;
	int j = 0;
	
	for(int i=0;i<strlen(str);)
	{
		if(s.find(str[i]) == s.end())
		{
			s.insert(str[i]);
			++i;
			
			if((i-j) > maxCount)
				maxCount = i-j;
		}
		else
		{
			s.erase(str[i]);
			++j;
		}
	}
	
	printf("maxCount is %d", maxCount);
	
	return 0;
}
