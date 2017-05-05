#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<vector>
#include<bits/stdc++.h>
#include<set>
using namespace std;

void circularhotspot(string input, string output)
//int main()
{
	//ofstream myfile ("OUTPUTRING.txt");
	//ifstream myfile1 ("circle.txt");
  

  ofstream myfile (output.c_str());
  ifstream myfile1 (intput.c_str());
  long long int len=0,n,k=0,i,t=0,j,m,b[55000],x,y,a[50000],flag[50000],flag1[55000],f1=0,hspt[50000],kl=0;
	double mx1,mx2,mn1,mn2,x1,y1,x2,y2,c,d;
  double z=0.04,s,s1,z1,B,f,max=0,mx,max1=0,s2,nz;
  vector<pair<double,pair<double,double > > > v1,v3;
	vector<pair<double,pair<double,pair<double,double > > > > v4,v5;
  double LR[50000],LR2[55000];
  std::string line;
  vector< pair<double,double> > v,v2;
  while(!myfile1.eof())
     {
        myfile1>>c>>d;
        v.push_back(std::make_pair(c,d));
        len++;
     }
  for(i=0;i<len;i++)
    flag[i]=-1;
  for(i=0;i<ceil(len*1.01);i++)
    flag1[i]=-1;
  for(i=0;i<len;i++)
    a[i]=0;
  for(i=0;i<ceil(len*1.01);i++)
    b[i]=0;
  sort(v.begin(),v.end());
	mn1=v[0].first;
	mn2=v[0].second;
	mx1=v[v.size()-1].first;
	mx2=v[v.size()-1].second;
	for(i=0;i<ceil(len*0.01);i++)
	 {
	    y2=(mx2-mn2);
	    x2=(mx1-mn1);
	    x1=x2*((double)rand()/RAND_MAX)+mn1;
	    y1=y2*((double)rand()/RAND_MAX)+mn2;
	    v2.push_back(std::make_pair(x1,y1));
	 }
	for(i=0;i<len;i++)
	  v2.push_back(v[i]);
	sort(v2.begin(),v2.end());
	/*for(i=0;i<14;i++)
	   cout<<v2[i].first<<'\t'<<v2[i].second<<'\n';*/
  for(i=0;i<len;i++)
    {
        for(j=0;j<len;j++)
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
    B=(len*z1)/s1;
    for(i=0;i<len;i++)
       {
           for(j=0;j<len;j++)
		   {
			   s2=sqrt(pow(v[i].first-v[j].first,2)+pow(v[i].second-v[j].second,2));
			   if(s2<=z)
            {
                a[i]++;
            }      
		   }
           if(a[i]>B)
             LR[i]=a[i]*log(a[i]/B)+(len-a[i])*log((len-a[i])/(len-B));
           else
             LR[i]=0;
           if(isnan(LR[i]))
             LR[i]=0;
       }

    for(i=0;i<len;i++)
       {
           v1.push_back(make_pair(LR[i],v[i]));
        
       }
    B=(len*1.01*z1)/s1;
    for(i=0;i<len*1.01;i++)
       {
           for(j=0;j<len*1.01;j++)
                if(sqrt(pow(v2[i].first-v2[j].first,2)+pow(v2[i].second-v2[j].second,2))<=z)
                  b[i]++;
           if(b[i]>B)
             LR2[i]=b[i]*log(b[i]/B)+(len*1.01-b[i])*log((len*1.01-b[i])/(len*1.01-B));
           else
             LR2[i]=0;
           if(isnan(LR2[i]))
             LR2[i]=0;
       }


    for(i=0;i<ceil(len*1.01);i++)
       {
           v3.push_back(make_pair(LR2[i],v2[i]));
       }
    sort(v1.begin(),v1.end());
    reverse(v1.begin(),v1.end());
    sort(v3.begin(),v3.end());
    reverse(v3.begin(),v3.end());
    /*for(i=0;i<len;i++)
       myfile<<v5[i].first<<'\n';*/
    for(i=0;i<len;i++)
       {
           f1=0;
           for(j=0;j<len;j++)
              //if(i!=j)
              {
                  f=sqrt(pow(v1[i].second.first-v[j].first,2)+pow(v1[i].second.second-v[j].second,2));
                  if(f<=z)
                  {
                      if(flag[j]!=-1)
                        {
                            f1=1;
                            for(k=0;k<j;k++)
                               if(flag[k]==i)
                                 flag[k]=-1;  
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
                  //myfile<<v1[hspt[kl-1]].second.first<<" "<<v1[hspt[kl-1]].second.second<<'\n';
              }
       }   
    
    int pos[kl];
    for(i=0;i<kl;i++)
		pos[i]=-1;
    //myfile<<kl<<" "<<len<<'\n';
    for(i=0;i<ceil(len*1.01);i++)
       {
           f1=0;
           for(j=0;j<ceil(len*1.01);j++)
              //if(i!=j)
              {
                  f=sqrt(pow(v3[i].second.first-v3[j].second.first,2)+pow(v3[i].second.second-v3[j].second.second,2));
                  if(f<=z)
                  {
                      if(flag1[j]!=-1)
                        {
                            f1=1;
                            for(k=0;k<(len*1.01);k++)
                               if(flag1[k]==i)
                                 flag1[k]=-1;
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
           for(j=0;j<ceil(len*1.01);j++)
           if(v1[hspt[i]].first>=v3[j].first)
             {  
                 pos[i]=j+1;
                 break;
             }
          if(j==ceil(len*1.01)&&pos[i]==-1)
             pos[i]=ceil(len*1.01)+1;
       }
    /*for(i=0;i<kl;i++)
    myfile<<float(pos[i])/float(len*.01+1.0)<<'\n';  
    myfile<<kl<<'\n';   
	/*for(i=0;i<kl;i++)
		myfile<<v5[hspt[i]].second.second.first<<' '<<v5[hspt[i]].second.second.second<<" "<<v5[hspt[i]].second.first<<'\n';
    myfile.close();
   for(i=0;i<kl;i++)
       {
           cout<<hspt[i]<<" ";
       }
    cout<<'\n';
    for(i=0;i<14;i++)
       cout<<v3[i].first<<'\t'<<v3[i].second.first<<"\t"<<v3[i].second.second<<'\n';*/
    for(i=0;i<kl;i++)
       if(float(pos[i])/float(len*.01+1.0)<95)
         myfile<<v1[hspt[i]].second.first<<' '<<v1[hspt[i]].second.second<<'\n';
    myfile.close();
    myfile1.close();
    //return 0;
}