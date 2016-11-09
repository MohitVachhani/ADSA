//This is a dp solution
#include<iostream>
using namespace std;
int main()
{
	int n;
	cout<<"Enter the number of matrix:"<<endl;
	cin>>n;
	int a[n+1];
	int x,y;
	int i;
	for(i=0;i<n;i++)
	{
		cin>>x>>y;
		a[i]=x;
	}
	a[n]=y;
	int answer[n+1][n+1];
	int j;
	n=n+1;
	for(i=1;i<n;i++)
		answer[i][i]=0;
	for (i=1; i<n; i++)
        answer[i][i] = 0;
 	int k,l,q;
 	for (L=2; L<n; L++)
    {
        for (i=1; i<n-L+1; i++)
        {
            j = i+L-1;
            answer[i][j] = INT_MAX;
            for (k=i; k<=j-1; k++)
            {
                q = answer[i][k] + answer[k+1][j] + a[i-1]*a[k]*a[j];
                if (q < answer[i][j])
                    answer[i][j] = q;
            }
        }
    }
    cout<<answer[1][n-1]<<endl;
}