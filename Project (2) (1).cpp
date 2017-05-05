#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<vector>
#include<bits/stdc++.h>
#include<set>
using namespace std;
int main()
{
	ofstream myfile ("OUTPUTRING.txt");
  ifstream myfile1 ("input.txt");
    long long int n,k=0,i,t=0,j,m,b[14],x,y,a[10],flag[10],flag1[14],f1=0,hspt[10],kl=0,len;
	double mx1,mx2,mn1,mn2,x1,y1,x2,y2;
    double c,d,z=0.04,s,s1,z1,B,f,max=0,mx,max1=0,s2;
    vector<pair<double,pair<double,double > > > v1,v3;
	vector<pair<double,pair<double,pair<double,double > > > > v4,v5;
    double LR[10],LR2[14];
    for(i=0;i<10;i++)
       flag[i]=-1;
    for(i=0;i<14;i++)
       flag1[i]=-1; 
    for(i=0;i<10;i++)
       a[i]=0;
    for(i=0;i<14;i++)
       b[i]=0;		
    vector< pair<double,double> > v,v2;
    while(!myfile1.eof())
       {
            myfile1>>c>>d;
            v.push_back(std::make_pair(c,d));
           len++;
       }
    for(i=0;i<len;i++)
       myfile<<v[i].first<<" "<<v[i].second<<'\n';   
    sort(v.begin(),v.end());
	mn1=v[0].first;
	mn2=v[0].second;
	mx1=v[v.size()-1].first;
	mx2=v[v.size()-1].second;
	for(i=0;i<4;i++)
	   {
	       y2=(mx2-mn2);
	       x2=(mx1-mn1);
	       x1=x2*((double)rand()/RAND_MAX)+mn1;
	       y1=y2*((double)rand()/RAND_MAX)+mn2;
	       v2.push_back(std::make_pair(x1,y1));
	   }
	for(i=0;i<10;i++)
	   v2.push_back(v[i]);
	sort(v2.begin(),v2.end());     
	/*for(i=0;i<14;i++)
	   cout<<v2[i].first<<'\t'<<v2[i].second<<'\n';*/   
    for(i=0;i<10;i++)
       {
           for(j=0;j<10;j++)
              {
                  mx=sqrt(pow(v[i].first-v[j].first,2)+pow(v[i].second-v[j].second,2));
                  if(max<mx)
                    max=mx;
              }
       }
    s=max/2;
    s1=3.14*s*s;
    //cout<<s<<'\n';
    z1=3.14*z*z;
    B=(10*z1)/s1;
    for(i=0;i<10;i++)
       {
		   max=0;
           for(j=0;j<10;j++)
		   {
			   s2=sqrt(pow(v[i].first-v[j].first,2)+pow(v[i].second-v[j].second,2));
			   if(s2>max)
				   max=s2;
         if(s2<=z)
           a[i]++;
         myfile<<s2<<'\n';
		   }  
           if(a[i]>B)          
             LR[i]=log(pow(a[i]/B,a[i])*pow((10-a[i])/(10-B),10-a[i]));
           else
             LR[i]=0;
		 v1.push_back(make_pair(max,v[i]));
       }
    for(i=0;i<10;i++)
       {
           v5.push_back(make_pair(LR[i],v1[i]));
       }   
    B=(14*z1)/s1;
    for(i=0;i<14;i++)
       {
           for(j=0;j<14;j++)
                if(sqrt(pow(v2[i].first-v2[j].first,2)+pow(v2[i].second-v2[j].second,2))<=z)
                  b[i]++;
           if(b[i]>B)          
             LR2[i]=log(pow(b[i]/B,b[i])*pow((14-b[i])/(14-B),14-b[i]));
           else
             LR2[i]=0;
       }   
    
    
    for(i=0;i<14;i++)
       {
           v3.push_back(make_pair(LR2[i],v2[i]));
       }   
    sort(v5.begin(),v5.end());
    reverse(v5.begin(),v5.end());
    sort(v3.begin(),v3.end());
    reverse(v3.begin(),v3.end());
    
    for(i=0;i<10;i++)
       {
           f1=0;
           for(j=0;j<10;j++)
              //if(i!=j)
              {
                  f=sqrt(pow(v5[i].second.second.first-v[j].first,2)+pow(v5[i].second.second.second-v[j].second,2));
                  if(f<=z)
                  {
                      if(flag[j]!=-1)
                        {
                            f1=1;
                            break;
                        }
                      else
                        {
                            flag[j]=i;
                        }
                  }
              }
           if(f1==0)
              {
                  hspt[kl++]=i;
              }
       }
    int pos[kl];
    for(i=0;i<kl;i++)
		pos[i]=-1;
       
    for(i=0;i<14;i++)
       {
           f1=0;
           for(j=0;j<14;j++)
              //if(i!=j)
              {
                  f=sqrt(pow(v3[i].second.first-v3[j].second.first,2)+pow(v3[i].second.second-v3[j].second.second,2));
                  if(f<=z)
                  {
                      if(flag1[j]!=-1)
                        {
                            f1=1;
                            break;
                        }
                      else
                        {
                            flag1[j]=i;
                        }
                  }
              }
       }
    for(i=0;i<kl;i++)
       {
           //cout<<v1[hspt[i]].first<<endl;
           for(j=0;j<14;j++)
           if(v5[hspt[i]].first>=v3[j].first)
             {
                 pos[i]=j+1;
                 break;
             }
          if(j==14&&pos[i]==-1)
             pos[i]=j+1;
       }
  myfile<<kl<<'\n';     
	for(i=0;i<kl;i++)   
		myfile<<v5[hspt[i]].second.second.first<<' '<<v5[hspt[i]].second.second.second<<" "<<v5[hspt[i]].second.first<<'\n';
    myfile.close();	
   /* for(i=0;i<kl;i++)
       {
           cout<<hspt[i]<<" ";
       }
    cout<<'\n';
    for(i=0;i<14;i++)
       cout<<v3[i].first<<'\t'<<v3[i].second.first<<"\t"<<v3[i].second.second<<'\n';*/
    for(i=0;i<kl;i++)
       cout<<pos[i]/5.0<<'\n';
    return 0;
}