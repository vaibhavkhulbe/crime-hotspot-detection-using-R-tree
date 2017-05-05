#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define pb push_back
#define fastio ios_base::sync_with_stdio(false); cin.tie(0);
#define fileio freopen("inpu.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define MAX_CHILD 100

#define square(a) a*a

struct node{
	bool isLeaf,isParentLeaf;
	int type;
	double lon1,lat1,lon2,lat2;
	long long child[MAX_CHILD+1];
	int no_child;
	node()
	{

	}
	node(double lo1,double la1, double lo2,double la2)
	{
		isLeaf=false;
		lon1=lo1;
		lat1=la1;
		lon2=lo2;
		lat2=la2;
		type=-1;
		no_child=0;
		for (int i=0;i<=MAX_CHILD;i++)
			child[i]=-1;
	}
	node(double lo, double la, int l)
	{
		isLeaf=true;
		type=l;
		isParentLeaf=false;
		lon1=lon2=lo;
		lat1=lat2=la;
		no_child=0;
		for (int i=0;i<=MAX_CHILD;i++)
			child[i]=-1;
	}
};

class rtree{

private:
	vector<pair<double, double> > nodes_in_box;
	fstream file;
	long long root;

public:
	
	rtree()
	{
		root=-1;
		file.open("test.txt",ios::in | ios::out | ios::trunc | ios::binary);
	}
	rtree(long long r, string filename)
	{
		root=r;
		if(r!=-1)
			file.open( filename.c_str() , ios::in | ios::out | ios::binary);
		else
			file.open(filename.c_str() ,ios::in | ios::out | ios::trunc | ios::binary);

	}
	rtree(string filename)
	{
		root=-1;
		file.open(filename.c_str(),ios::in | ios::out | ios::trunc | ios::binary);
	}
	int getRoot(){
		return root;
	}
	void insert(double lon, double lat, int l)
	{
		if(root==-1)
		{
			node k(lon,lat,lon,lat);
			file.seekp(0);
			file.seekg(0);
			file.write((char*)&k , sizeof(node));
			root=0;

			file.seekg(0,ios::end);
			file.seekp(0,ios::end);
			k.child[k.no_child++] = file.tellp();
			k.isParentLeaf=true;

			node child(lon,lat,l);

			file.write((char*)&child , sizeof(node));
			file.seekp(root);file.seekg(root);
			file.write((char*)&k , sizeof(node));
		}
		else{

			long long p_ptr=insert_rec(lon,lat,l,root);
			if(p_ptr==-1)
				return;
			node p,r;
			file.seekp(p_ptr);file.seekg(p_ptr);
			file.read((char*)&p , sizeof(node));

			file.seekp(root);file.seekg(root);
			file.read((char*)&r , sizeof(node));
			node r1(min(p.lon1,r.lon1) , min(p.lat1,r.lat1) , max(p.lon2,r.lon2) , max(p.lat2,r.lat2));


			r1.child[r1.no_child++]=root;
			r1.child[r1.no_child++]=p_ptr;

			//r1.type = min(p.type,r.type);

			if(r.isLeaf)
				r1.isParentLeaf=true;
			else
				r1.isParentLeaf=false;

			file.seekp(0,ios::end);file.seekg(0,ios::end);
			root = file.tellp();
			file.write((char*)&r1 , sizeof(node));
			

		}
	}
	long long insert_rec(double lon, double lat, int l, long long n_ptr)
	{
		if(n_ptr==-1)
		{
			node n(lon,lat,l);
			file.seekp(0,ios::end);file.seekg(0,ios::end);
			n_ptr = file.tellp();
			file.write((char*)&n , sizeof(node));
			return n_ptr;
		}
		node n;
		file.seekp(n_ptr);file.seekg(n_ptr);
		file.read((char*)&n , sizeof(node));

		if(n.isParentLeaf)
		{
			n.child[n.no_child] = insert_rec(lon,lat,l,-1);
			n.no_child++;
			n.lon1 = min(n.lon1,lon);
			n.lat1=min(n.lat1,lat);
			n.lon2 = max(n.lon2,lon);
			n.lat2=max(n.lat2,lat);
			//n.type = min(l,n.type);
			file.seekp(n_ptr);file.seekg(n_ptr);
			file.write((char*)&n , sizeof(node));
		}
		else
		{

			node k;
			long long min1=-1,k_ptr;
			double area_inc=INT_MAX ,lon1,lon2,lat1,lat2,area;
			for(int it=0;it<n.no_child;it++)
			{
				k_ptr=n.child[it];
				file.seekp(k_ptr);file.seekg(k_ptr);
				file.read((char*)&k , sizeof(node));
				lon1 = min(k.lon1,lon);
				lat1=min(k.lat1,lat);
				lon2 = max(k.lon2,lon);
				lat2=max(k.lat2,lat);

				area = (lon2-lon1)*(lat2-lat1) - (k.lon2 - k.lon1)*(k.lat2 - k.lat1);
				if(area<=area_inc)
				{
					if(area==area_inc)
					{
						if(min1 == -1)
							min1=k_ptr;
						else {
							node m;
							file.seekp(min1);file.seekg(min1);
							file.read((char*)&m , sizeof(node));
							if(k.no_child < m.no_child)
								min1=k_ptr;
						}
					}
					else
					{
						min1=k_ptr;
						area_inc=area;
					}
				}
			}
			n.lon1 = min(n.lon1,lon);
			n.lat1=min(n.lat1,lat);
			n.lon2 = max(n.lon2,lon);
			n.lat2=max(n.lat2,lat);
			//n.type = min(n.type,l);
			k_ptr=insert_rec(lon,lat,l,min1);
			if(k_ptr!=-1)
				n.child[n.no_child++] = k_ptr;
			file.seekp(n_ptr);file.seekg(n_ptr);
			file.write((char*)&n , sizeof(node));


		}

		if(n.no_child <= MAX_CHILD)
			return -1;

		return split(n_ptr);


	}

	long long split( long long n_ptr)
	{
		node n,child[MAX_CHILD+1];
		long long child_ptr[MAX_CHILD+1],child1[MAX_CHILD],child2[MAX_CHILD];
		
		file.seekp(n_ptr); file.seekg(n_ptr);
		file.read((char*)&n , sizeof(node));

		int size1=0,size2=0;
		double max_dis=0,dis,a1,a2,lo1,lo2,la1,la2;
		int it1=0,it2=1;
		double avg_lon[MAX_CHILD+1],avg_lat[MAX_CHILD+1];
		for(int i=0;i<=MAX_CHILD; i++)
		{
			child_ptr[i]=n.child[i];
			n.child[i]=-1;
			file.seekp(child_ptr[i]);file.seekg(child_ptr[i]);
			file.read((char*)&child[i] , sizeof(node));

			avg_lon[i] = child[i].lon1 + child[i].lon2;
			avg_lat[i] = child[i].lat1 + child[i].lat2;
			avg_lon[i]/=2.0;
			avg_lat[i]/=2.0;

			for(int j=0; j<i;j++)
			{
				dis = square((avg_lon[i] - avg_lon[j])) + square((avg_lat[i] - avg_lat[j])) ;
				if(dis>=max_dis)
				{
					max_dis=dis;
					it1=i;
					it2=j;
				}
			}
		}
		n.lon1 = child[it1].lon1;
		n.lat1 = child[it1].lat1;
		n.lon2 = child[it1].lon2;
		n.lat2 = child[it1].lat2;
		//n.type=child[it1].type;
		node p(child[it2].lon1,child[it2].lat1,child[it2].lon2,child[it2].lat2);
		p.isParentLeaf=n.isParentLeaf;
		//p.type=child[it2].type;
		n.no_child=0;

		n.child[n.no_child++]= child_ptr[it1];
		p.child[p.no_child++]= child_ptr[it2];
		for(int i=0;i<=MAX_CHILD;i++)
		{
			if(i!=it1 && i!=it2)
			{
				lo1=min(n.lon1 , child[i].lon1);
				lo2=max(n.lon2 , child[i].lon2);
				la1=min(n.lat1 , child[i].lat1);
				la2=max(n.lat2 , child[i].lat2);
				a1 = (lo2-lo1)*(la2-la1) - (n.lon2 - n.lon1)*(n.lat2 - n.lat1);
			
				lo1=min(p.lon1 , child[i].lon1);
				lo2=max(p.lon2 , child[i].lon2);
				la1=min(p.lat1 , child[i].lat1);
				la2=max(p.lat2 , child[i].lat2);
				a2 = (lo2-lo1)*(la2-la1) - (p.lon2 - p.lon1)*(p.lat2 - p.lat1);

				if(a1<a2)
				{
					n.child[n.no_child++]= child_ptr[i];	
					n.lon1=min(n.lon1 , child[i].lon1);
					n.lon2=max(n.lon2 , child[i].lon2);
					n.lat1=min(n.lat1 , child[i].lat1);
					n.lat2=max(n.lat2 , child[i].lat2);
					//n.type=min(n.type,child[i].type);
				}
				else
				{
					p.child[p.no_child++]= child_ptr[i];	
					p.lon1=min(p.lon1 , child[i].lon1);
					p.lon2=max(p.lon2 , child[i].lon2);
					p.lat1=min(p.lat1 , child[i].lat1);
					p.lat2=max(p.lat2 , child[i].lat2);
					//p.type=min(p.type,child[i].type);
				}

			}
		}

		file.seekp(n_ptr);file.seekg(n_ptr);
		file.write((char*)&n , sizeof(node));

		file.seekp(0,ios::end);file.seekg(0,ios::end);
		long long p_ptr=file.tellp();
		file.write((char*)&p , sizeof(node));
		return p_ptr;

	}

	void display(long long n_ptr , int t)
	{
		if(n_ptr==-1)
			return;
		cout<<endl;
		for(int i=0;i<t;i++)
			cout<<"\t";

		node n;
		file.seekp(n_ptr); file.seekg(n_ptr);
		file.read((char*)&n , sizeof(node));
		
		cout<<"Location:"<<n_ptr<<" Start long:"<<n.lon1<<", Start lat:"<<n.lat1<<" End long:"<<n.lon2<<", End lat:"<<n.lat2<<" Type:"<<n.type<<" No. of child"<<n.no_child<<"   ";//<<" "<<n.isLeaf<<" "<<n.isParentLeaf<<"   ";
		for(int i=0;i<=MAX_CHILD;i++)
		{
			cout<<n.child[i]<<" ";
		}
		//cout<<"\t"<<n->no_child;
		for(int i=0;i<n.no_child;i++)
		{
			display(n.child[i],t+1);
		}
	}


	void display()
	{
		display(root,0);
	}




	//query
	void queryUtil(double lo1,double lo2, double la1, double la2, int type, long long ptr)
	{
		if(ptr==-1)
			return;

		node n;
		file.seekp(ptr);file.seekg(ptr);
		file.read((char*)&n , sizeof(node));


		if ( n.lon2>=lo1 && lo2>=n.lon1 && n.lat2>=la1 && la2>=n.lat1)
		{
		}
		else
			return;

		/*if(n.type==type)
			return; */

		if(n.isLeaf && n.type==type)
			nodes_in_box.pb(make_pair(n.lat1,n.lon1));

		for(int i=0;i<n.no_child;i++)
		{
			queryUtil(lo1,lo2,la1,la2,type,n.child[i]);
		}

	}



	void query(string filename,double lo1,double lo2, double la1, double la2, int type)
	{
		nodes_in_box.clear();
		double t;
		if(lo1>lo2) swap(lo1,lo2);
		if(la1>la2) swap(la1,la2);
		queryUtil(lo1,lo2,la1,la2,type,root);



	   	ofstream out;
	   	out.open(filename.c_str(),ios::out|ios::trunc);
	   	vector< pair<double, double> >::iterator it;
	    for(it=nodes_in_box.begin();it!=nodes_in_box.end();it++) out<<it->first<<" "<<it->second<<endl;
	    out.close();

	}

};



long long insert(string citytree,long long rtree, double lat,double lon,int type){

	rtree r(rtree,citytree.c_str());
	rtree.insert(lon,lat,type);
	return r.getRoot();
}

void query(string points,string citytree,long long rtree, double lat1,double lon1,double lat2,double lon2,int type){
	rtree r(rtree,citytree.c_str());
	r.query(points,lon1,lon2,lat1,lat2,type);
}

void newCity(string city){

}

int main()
{
    fastio
    fileio
    double lo,la;
    int type;
    /*rtree r;

    for(int i=0;i<4500;i++)
    {
    	cin>>type>>lo>>la;
     	//cout<<type<<" "<<lo<<" "<<la<<endl;
     	r.insert(lo,la,type);
     	//cout<<endl<<endl;
    }

    r.display();
	*/
    rtree r(88168,"test.txt");

    r.query("new.txt",76.7703,77.7324,28.9687,28.2039,1);

    //r.display();
    
    //cout<<sizeof(node)<< " "<<r.root;
    return 0;
}
