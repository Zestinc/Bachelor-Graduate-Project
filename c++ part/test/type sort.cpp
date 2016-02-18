#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std;
vector<string> str;
map<string, bool> exi;

int main()
{
	freopen("envo type.txt", "r", stdin);
	freopen("envo type sort.txt", "w", stdout);
	string s;
	while(cin>>s)
	{
		if(s[0] == '"')
		{
			s.erase(0,1);
			s.append("\"");
		}
		if(!exi[s])
		{
			exi[s] = true;
			str.push_back(s);
		}
	}
	sort(str.begin(), str.end());
	for(int i = 0 ; i < str.size() ; ++i)
		cout<<str[i]<<endl;
}