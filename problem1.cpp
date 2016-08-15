#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

vector <int> a[10];
int visit[10]={0};
int b[10];

int dfs(int s,int diff)
{
	visit[s]=1;
	int i;
	for(i=0;i<a[s].size();i++)
	{
		if(visit[a[s].at(i)]==0)
		{
			b[a[s].at(i)]=b[a[s].at(i)]+diff;
			dfs(a[s].at(i),diff);
		}
	}
}
int result(int i,int sum,string a)
{
	int ans;
	if(a.at(i)=='+')
		ans=sum+((int)a.at(i-1)-48);
	if(a.at(i)=='-')
		ans=sum-((int)a.at(i-1)-48);
	if(a.at(i)=='*')
		ans=sum*((int)a.at(i-1)-48);
	if(a.at(i)=='/')
		ans=sum/((int)a.at(i-1)-48);
	
	return ans;
}
int main()
{
	ifstream cin("testfile.txt");//this was used to give input from a file
	cout<<"Enter the first element:"<<endl;
	cin>>b[1];
	int i;
	for(i=2;i<=10;i++)
			b[i]=0;
	string q;
	char c;
	int number,qw5,qw1,qw2,qw3,qw4;
	int node1,node2,node3,node4,node5,node6;	
	int diff;
	while(1)
	{
		cout<<"Do you want to add more constraint:(Y/N)"<<endl;
		cin>>c;
		if(c=='N')
				break;
		cout<<"Enter the number of variable you want to enter:(1/2/3/4):"<<endl;
		cin>>number;
		cin>>q;
		node1=(int)q.at(0)-64;
		int sum=0;
		if(number>0)
		{
			node2=(int)q.at(4)-64;
			a[node2].push_back(node1);
			sum=sum+result(3,b[node2],q);
		}
		if(number>1)
		{
			node3=(int)q.at(8)-64;
			a[node3].push_back(node1);
			sum=sum+result(7,b[node3],q);
		}
		if(number>2)
		{
			node4=(int)q.at(12)-64;
			a[node4].push_back(node1);
			sum=sum+result(11,b[node4],q);
		}
		if(number>3)
		{
			node5=(int)q.at(16)-64;
			a[node5].push_back(node1);
			sum=sum+result(15,b[node5],q);
		}
		
		diff=sum-b[node1];
		b[node1]=sum;
		dfs(node1,diff);
		for(i=1;i<=10;i++)
				visit[i]=0;
		for(i=1;i<=9;i++)
		{
			cout<<b[i]<<" ";
			if(i==3 || i==6 || i==9)
				cout<<endl;
		}
	}
}