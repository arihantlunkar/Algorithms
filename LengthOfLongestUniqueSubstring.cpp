#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

int main() {
	
	const char* str = "ABDEFGABEFQWERTYUIOP";
	
	set<char> s; 
	int maxCount = 0;
	
	int j = 0;
	int i = 0;
	
	while(j<strlen(str))
	{
		if(s.find(str[j]) == s.end())
		{
			s.insert(str[j]);
			j++;
			maxCount = std::max(j-i, maxCount);
		}
		else
		{
			s.erase(str[i]);
			++i;
		}
	}
	
	printf("maxCount is %d", maxCount);
	
	return 0;
}
