#include<bits/stdc++.h>

using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("input1.txt","w",stdout);
	long long level,id;
	long double lat,lon;
	while(cin>>level>>id>>lat>>lon)
	{
		cout<<fixed<<setprecision(14)<<level<<" "<<lat<<" "<<lon<<endl;
	}

	return 0;
}