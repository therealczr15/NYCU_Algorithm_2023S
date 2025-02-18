#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>

// find all LCS 

using namespace std;

void LCS_Length(vector<double> X, vector<double> Y, vector<double> Z, vector<vector<vector<int>>> &C)
{
	int m = X.size();
	int n = Y.size();
	int p = Z.size();
	
 	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=p;k++)
			{
				if(X[i-1] == Y[j-1] && X[i-1] == Z[k-1])
					C[i][j][k] = C[i-1][j-1][k-1] + 1;
				else
					C[i][j][k] = max(max(C[i-1][j][k],C[i][j-1][k]),C[i][j][k-1]);
			}			
		}
	}
}

void findAllLCS(vector<vector<vector<int>>> C, vector<double> X, vector<double> Y, vector<double> Z, int i, int j, int k, vector<double> &cLCS, vector<vector<double>> &allLCS)
{
	// if the end of the sequence is reached, then we can return
	if(i == 0 || j == 0 || k == 0)
	{
		reverse(cLCS.begin(),cLCS.end());
		allLCS.push_back(cLCS);
		reverse(cLCS.begin(),cLCS.end());
		return;	
	}	
	
	if (X[i-1] == Y[j-1] && X[i-1] == Z[k-1])
	{
		cLCS.push_back(X[i-1]);
        findAllLCS(C,X,Y,Z,i-1,j-1,k-1,cLCS,allLCS);
        cLCS.pop_back();
	}
	
	else 
	{
		// go to direction X
		if (C[i-1][j][k] >= C[i][j-1][k] && C[i-1][j][k] >= C[i][j][k-1])
			findAllLCS(C,X,Y,Z,i-1,j,k,cLCS,allLCS);
		
		// go to direction Y
		if (C[i][j-1][k] >= C[i-1][j][k] && C[i][j-1][k] >= C[i][j][k-1])
			findAllLCS(C,X,Y,Z,i,j-1,k,cLCS,allLCS);
			
		// go to direction Z
		if (C[i][j][k-1] >= C[i-1][j][k] && C[i][j][k-1] >= C[i][j-1][k])
			findAllLCS(C,X,Y,Z,i,j,k-1,cLCS,allLCS);
	}
}

int main()
{
	srand(time(NULL));
	vector<double> arrayX;
	vector<double> arrayY;
	vector<double> arrayZ;
	int sx,sy,sz;
	
	// Input size of sequence of X, Y, Z
	cout << "Input size(1-100) of Sequence X: ";
	cin >> sx;
	cout << "Input size(1-100) of Sequence Y: ";
	cin >> sy;
	cout << "Input size(1-100) of Sequence Z: ";
	cin >> sz;
	
	// Input the three sequence in order
	cout << "Input Sequence X: ";
	for(int i=0;i<sx;i++)
	{
		/*double x = rand() % 5;
		arrayX.push_back(x);*/
		double x;
		cin >> x;
		arrayX.push_back(x);
	}
	cout << "Input Sequence Y: ";
	for(int i=0;i<sy;i++)
	{
		/*double y = rand() % 5;
		arrayY.push_back(y);*/
		double y;
		cin >> y;
		arrayY.push_back(y);
	}
	cout << "Input Sequence Z: ";
	for(int i=0;i<sz;i++)
	{
		/*double z = rand() % 5;
		arrayZ.push_back(z);*/
		double z;
		cin >> z;
		arrayZ.push_back(z);
	}
	
	/*cout << "Sequence X: ";
	for(int i=0;i<sx;i++)
		cout << arrayX[i] << ' '; 
	cout << '\n';
	cout << "Sequence Y: ";
	for(int i=0;i<sy;i++)
		cout << arrayY[i] << ' '; 
	cout << '\n';
	cout << "Sequence Z: ";
	for(int i=0;i<sz;i++)
		cout << arrayZ[i] << ' '; 
	cout << '\n';*/
	
	vector<vector<vector<int>>> C(sx+1,vector<vector<int>> (sy+1,vector<int> (sz+1, 0))); //3D table C 
	LCS_Length(arrayX,arrayY,arrayZ,C);	// find LCS length
	cout << "LCS length is: "<< C[sx][sy][sz] << '\n';
	vector<double> currentLCS;
	vector<vector<double>> allLCS; // to store all possible LCS
	findAllLCS(C,arrayX,arrayY,arrayZ,sx,sy,sz,currentLCS,allLCS); // use recursive to find all possible LCS
	set<vector<double>> lcsSet(make_move_iterator(allLCS.begin()), make_move_iterator(allLCS.end())); // use set to eliminate duplicated vector
	cout << "LCS is: " << '\n';
	for (vector<double> l: lcsSet)   // output all possible LCS by set
    {
    	for(int i=0;i<l.size();i++)
    		cout << l[i] << ' ';
    	cout << '\n';
	}
	return 0;
}
