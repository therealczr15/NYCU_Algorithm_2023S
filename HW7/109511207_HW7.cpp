#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std; 

/*vector<double> p = {   0,0.05,0.04,0.02,0.07,0.08,0.09,0.04,0.08,0.03};
vector<double> q = {0.08,0.06,0.04,0.04,0.03,0.06,0.07,0.06,0.04,0.02};*/

vector<double> p = {   0,0.05,0.15,0.15,0.10,0.10}; 
vector<double> q = {0.05,0.10,0.05,0.10,0.05,0.10};

/*vector<double> p = {   0,0.15,0.10,0.05,0.10,0.20}; 
vector<double> q = {0.05,0.10,0.05,0.05,0.05,0.10};*/

// max function
int max(int a,int b)
{
	if(a > b)
		return a;
	return b;
}

//find OBST search cost
void Optimal_BST(vector<vector<double>> &e,vector<vector<double>> &w,vector<vector<int>> &r)
{
	for(int i=1;i<=p.size();i++)
	{
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}
	for(int l=1;l<=p.size()-1;l++)
	{
		for(int i=1;i<=p.size()-l;i++)
		{
            int j=i+l-1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for(int k=i;k<=j;k++)
			{
                double t = e[i][k-1] + e[k+1][j] + w[i][j];
                if(t < e[i][j])
				{
                    e[i][j] = t;
                    r[i][j] = k;
                }
            }
        }
	}
}

// find OBST height
int Depth(vector<vector<int>> &r,int root,int left,int right)
{
	int ldep, rdep;
	if(root-1 < left)
		ldep = 1;
	else
	{
		int lroot = r[left][root-1];
		ldep = Depth(r,lroot,left,root-1) + 1;
	}
	if(root+1 > right)
		rdep = 1;
	else
	{
		int rroot = r[root+1][right];
		rdep = Depth(r,rroot,root+1,right) + 1;
	}	
	return max(ldep,rdep);
}

// by recursive and r table to backtrack the OBST
void fillOBST(vector<vector<int>> &r,vector<vector<string>> &obst,int root,int left,int right,int level)
{
	obst[level][2*root] = "k" + to_string(root);
	if(root-1 < left)
		obst[level+1][2*root-1] = "d" + to_string(root-1);
	else
	{
		int lroot = r[left][root-1];
		fillOBST(r,obst,lroot,left,root-1,level+1);
	}
	if(root+1 > right)
		obst[level+1][2*root+1] = "d" + to_string(root);
	else
	{
		int rroot = r[root+1][right];
		fillOBST(r,obst,rroot,root+1,right,level+1);
	}
}

// print OBST
void printOBST(vector<vector<int>> &r)
{
	int root = r[1][p.size()-1];
	int depth = Depth(r,root,1,p.size()-1) + 1;
	vector<vector<string>> obst(depth+1,vector<string> (2*p.size(),"  "));
	fillOBST(r,obst,root,1,p.size()-1,1);
	for(int i=0;i<=depth;i++)
	{
        for(int j=1;j<=2*p.size()-1;j++)
            cout << obst[i][j]<<" ";
        cout << "\n\n";
    }
}

int main()
{
	vector<vector<double>> e(p.size()+1,vector<double> (p.size(),0)); // table e
	vector<vector<double>> w(p.size()+1,vector<double> (p.size(),0)); // table w
	vector<vector<int>> r(p.size(),vector<int> (p.size(),0)); // table r
	Optimal_BST(e,w,r); // find OBST search cost
	
	// cout
	cout << "Smallest search cost: " << e[1][p.size()-1] << '\n';
    cout << "Root: " << r[1][p.size()-1] << '\n';
    cout << "\nOptimal Binary Search Tree are below:\n";
    printOBST(r);
	return 0;
}
