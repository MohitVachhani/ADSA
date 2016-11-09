//This code will encode and decode the text which will be entered in testcase.txt
//The code will automatically make the two file
//One will be encode which will have binary string
//Second will be decode which will have the message which was in testcase.txt
//In this code I have made two maps
//Frequency of each character is stored in freq array
//Plus this code is Case Sensative means A and a is different 
//To test this code first download it in a folder
//In that folder make a file testcase.txt
//And then type in the message 
//Then run this C++ code there will be two file generated in the same folder
//Coder - Mohit Vachhani

#include<iostream>
#include<fstream>
#include<queue>
#include<algorithm>
#include<vector>
#include<bits/stdc++.h>
#include<utility>
#include<map>
using namespace std;

vector<pair<string,string > >  answer2;
map<string,string> decode;
map<string,string> encode;
int freq[200]={0};
struct node
{
	string q;
	int frequency;
	node *left,*right;
	node(string q,int frequency)
	{
		left=right=NULL;
		this->q=q;
		this->frequency=frequency;
	}

};
void print(struct node* root,string a)
{
	if(!root)
		return;
	if(root->q !="$")
	{
		//cout<<root->q<<" "<<a<<endl;
		answer2.push_back(make_pair(root->q,a));
		encode.insert(pair<string,string>(root->q,a));
		decode.insert(pair<string,string> (a,root->q));
	}
	print(root->left,a+"0");
	print(root->right,a+"1");

}

struct compare
{
	bool operator()(const node *left,const node *right)
	{
		return left->frequency > right->frequency;
	}
};

void main_algo(string a,int freq[])
{
	struct node *left,*right,*top;
	priority_queue<node*,vector<node*>,compare> minheap;
	int i;
	for(i=0;i<a.size();i++)
	{
		string b2;
		b2.push_back(a.at(i));
		minheap.push(new node(b2,freq[i]));
		b2.clear();
	}
	while(minheap.size()!=1)
	{
		left=minheap.top();
		minheap.pop();
		right=minheap.top();
		minheap.pop();
		string c="$";
		top=new node(c,left->frequency+right->frequency);
		top->left=left;
		top->right=right;
		minheap.push(top);
	}
	print(minheap.top(),"");
}
int main()
{
	ifstream cin("testcase");
	ofstream cout1("encode");
	ofstream cout2("decode");
	string a;
	getline(cin,a);
	int i;
	// counting the frequency
	//Upper case and lower case both are different
	for(i=0;i<a.size();i++)
	{
		if(a.at(i)!=' ')
			freq[(int)a.at(i)]++;
	}
	// frequency count is displayed
	string b="";
	int count1=0;
	for(i=0;i<200;i++)
	{
		if(freq[i]!=0)
		{
			//cout<<(char)i<<" "<<freq[i]<<endl;
			b=b+(char)i;
			count1++;		
		}
	}
	int freq1[count1]={0};
	int count2=0;
	for(i=0;i<200;i++)
	{
		if(freq[i]!=0)
		{
			freq1[count2]=freq[i];
			count2++;
		}
	}
	main_algo(b,freq1);
	string b4;
	string final_answer;
	for(i=0;i<a.size();i++)
	{
		if(a.at(i)!=' ')
		{
			b4=a.at(i);
			cout1<<encode[b4];
			final_answer+=encode[b4];
		}
		if(a.at(i)==' ')
		{
			cout1<<" ";
			final_answer+=" ";
		}
	}
	string b3="";
	for(i=0;i<final_answer.size();i++)
	{
		b3=b3+final_answer.at(i);
		if(decode[b3].size()!=0 && b3!=" ")
		{
			//cout<<b3<<endl;
			cout2<<decode[b3];
			b3.clear();
			b3="";
		}
		if(b3==" ")
		{
			cout2<<" ";
			b3.clear();
			b3="";
		}
	}
	cout<<endl;
}