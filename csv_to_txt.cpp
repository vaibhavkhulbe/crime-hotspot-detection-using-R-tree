#include<bits/stdc++.h>

using namespace std;



//void readcsv(string csvname,)

int main(){
	string str;
	long s,s1,s2,j;
	string lat,lon,type;
	freopen("england.csv","r",stdin);
	freopen("out2.txt","w",stdout);
	getline(cin,str);
	ofstream outc,outr,outl;
	outc.open("circle.txt",ios::out|ios::trunc);
	outr.open("ring.txt",ios::out|ios::trunc);
	outl.open("linear.txt",ios::out|ios::trunc);
	
	//cout<<str;
	set<string> strset;
	vector<string> v;
	for(int i=0;i<78963;i++){
		getline(cin,str);
		s=s1=s2=-1;
		for(j=0;j<9;j++){
			s=str.find(',',s+1);
			
		}
		s1=s;
		s2=str.find(',',s1+1);
		type=str.substr(s1+1,s2-s1-1);

		//strset.insert(type);

		s=s1=s2=-1;
		for(j=0;j<4;j++){
			s=str.find(',',s+1);
			
		}
		s1=s;
		s2=str.find(',',s1+1);
		//strset.insert(str.substr(s1+1,s2-s1-1));
			//cout<<s1<<" "<<s2<<endl;
		lon=str.substr(s1+1,s2-s1-1);
		

		s1=str.find(',',s2);
		s2=str.find(',',s1+1);
		lat=str.substr(s1+1,s2-s1-1);
		if(type.compare("Anti-social behaviour")==0 || type.compare("Drugs")==0  || type.compare("Other crime")==0 || type.compare("Public order")==0 
			|| type.compare("Possession of weapons")==0){
			outc<<lat<<" "<<lon<<"\n";	
		}
		else if(type.compare("Vehicle crime")==0 || type.compare("Shoplifting")==0 || type.compare("Violence and sexual offences")==0 || type.compare("Other theft")==0)
		{
			outr<<lat<<" "<<lon<<"\n";	
		}
		else
		{
			outl<<lat<<" "<<lon<<"\n";	
		}
		
	}
	outl.close();
	outr.close();
	outc.close();
	int i=1;
	set<string>::iterator it;
	//for(it=strset.begin();it!=strset.end();it++){
		//v.pushback(*it);
	//}
}