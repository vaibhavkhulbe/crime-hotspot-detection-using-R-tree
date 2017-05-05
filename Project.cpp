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
  freopen("england.txt","r",stdin);
  freopen("out.txt","w",stdout);
	//ofstream myfile ("OUTPUTCIR.txt");
    long long int n,k=0,i,t=0,j,m,b[4600],x,y,a[4500],flag[4500],flag1[4600],f1=0,hspt[4600],kl=0;
	float mx1,mx2,mn1,mn2,x1,y1,x2,y2;
    float c,d,z=0.04,s,s1,z1,B,f,max=0,mx;
    vector<pair<float,pair<float,float > > > v1,v3;
    double LR[10],LR2[14];
    for(i=0;i<4500;i++)
       flag[i]=-1;
    for(i=0;i<4600;i++)
       flag1[i]=-1; 
    for(i=0;i<4500;i++)
       a[i]=0;
    for(i=0;i<4600;i++)
       b[i]=0;		
    vector< pair<float,float> > v,v2;
    for(i=0;i<4500;i++)
       {
           cin>>c>>d;
           v.push_back(std::make_pair(c,d));
       }
       //cout<<"anything";
    sort(v.begin(),v.end());
	mn1=v[0].first;
	mn2=v[0].second;
	mx1=v[v.size()-1].first;
	mx2=v[v.size()-1].second;
	for(i=0;i<100;i++)
	   {
	       y2=(mx2-mn2);
	       x2=(mx1-mn1);
	       x1=x2*((float)rand()/RAND_MAX)+mn1;
	       y1=y2*((float)rand()/RAND_MAX)+mn2;
	       v2.push_back(std::make_pair(x1,y1));
	   }
	for(i=0;i<4500;i++)
	   v2.push_back(v[i]);
	sort(v2.begin(),v2.end());     
	/*for(i=0;i<14;i++)
	   cout<<v2[i].first<<'\t'<<v2[i].second<<'\n';*/   
    for(i=0;i<4500;i++)
       {
           for(j=0;j<4500;j++)
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
    for(i=0;i<4500;i++)
       {
           for(j=0;j<4500;j++)
                if(sqrt(pow(v[i].first-v[j].first,2)+pow(v[i].second-v[j].second,2))<=z)
                  a[i]++;
           if(a[i]>B)          
             LR[i]=log(pow(a[i]/B,a[i])*pow((4500-a[i])/(4500-B),4500-a[i]));
           else
             LR[i]=0;
       }
    for(i=0;i<4500;i++)
       {
           v1.push_back(make_pair(LR[i],v[i]));
       }   
       
       
       
       
       
    B=(4600*z1)/s1;
    for(i=0;i<4600;i++)
       {
           for(j=0;j<4600;j++)
                if(sqrt(pow(v2[i].first-v2[j].first,2)+pow(v2[i].second-v2[j].second,2))<=z)
                  b[i]++;
           if(b[i]>B)          
             LR2[i]=log(pow(b[i]/B,b[i])*pow((4600-b[i])/(4600-B),4600-b[i]));
           else
             LR2[i]=0;
       }   
    
    
    for(i=0;i<4600;i++)
       {
           v3.push_back(make_pair(LR2[i],v2[i]));
       }   
    sort(v1.begin(),v1.end());
    reverse(v1.begin(),v1.end());
    sort(v3.begin(),v3.end());
    reverse(v3.begin(),v3.end());
    
    for(i=0;i<4500;i++)
       {
           f1=0;
           for(j=0;j<4500;j++)
              //if(i!=j)
              {
                  f=sqrt(pow(v1[i].second.first-v1[j].second.first,2)+pow(v1[i].second.second-v1[j].second.second,2));
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
       
    for(i=0;i<4600;i++)
       {
           f1=0;
           for(j=0;j<4600;j++)
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
           for(j=0;j<4600;j++)
           if(v1[hspt[i]].first>=v3[j].first)
             {
                 pos[i]=j+1;
                 break;
             }
          if(j==14&&pos[i]==-1)
             pos[i]=j+1;
       } 
    //for(i=0;i<kl;i++)
       //cout<<pos[i]/101.0<<'\n';      
	//for(i=0;i<kl;i++)   
		//cout<<v1[hspt[i]].second.first<<' '<<v1[hspt[i]].second.second<<'\n';
   /* for(i=0;i<kl;i++)
       {
           cout<<hspt[i]<<" ";
       }
    cout<<'\n';
    for(i=0;i<14;i++)
       cout<<v3[i].first<<'\t'<<v3[i].second.first<<"\t"<<v3[i].second.second<<'\n';*/
    for(i=0;i<kl;i++)
       if(pos[i]<=4)
         cout<<v1[hspt[i]].second.first<<' '<<v1[hspt[i]].second.second<<'\n';
    return 0;
}