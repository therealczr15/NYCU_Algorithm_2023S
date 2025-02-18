#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int nxtX[4] = {-1, 0, 1, 0}, nxtY[4] = {0, 1, 0, -1};

struct Point
{
	int x;
	int y;	
};

void BFS(int** array,Point** prev,int** d,Point &curPoint,queue<Point> &q)
{
	// push current point into queue
	q.push({curPoint.x,curPoint.y});
	d[0][0] = 0;
	
	// while queue size is greater than 0
	while(q.size())
	{
		Point p = q.front();
		q.pop();
		
		// check four direction and check array element is 1 first
		for(int i=0;i<4;i++)
		{
			int x = p.x + nxtX[i];
			int y = p.y + nxtY[i];
			if(x>=0 && x<17 && y>=0 && y<17 && array[x][y]==1 && d[x][y]==-1)
			{
				d[x][y] = d[p.x][p.y] + 1;
				prev[x][y] = p;
				q.push({x,y});
			}
		}
		// check four direction and check array element is 2
		for(int i=0;i<4;i++)
		{
			int x = p.x + nxtX[i];
			int y = p.y + nxtY[i];
			if(x>=0 && x<17 && y>=0 && y<17 && array[x][y]==2 && d[x][y]==-1)
			{
				d[x][y] = d[p.x][p.y] + 1;
				prev[x][y] = p;
				q.push({x,y});
			}
		}
	}
}

void printBFS(int** array,Point** prev,int x,int y,fstream &oFile)
{
	//use recursive to print
	if(prev[x][y].x != 0 || prev[x][y].y != 0) 
		printBFS(array,prev,prev[x][y].x,prev[x][y].y,oFile);	
	else
		oFile << '(' << prev[x][y].x+1 << ',' << prev[x][y].x+1 << ')' << '\n';
	oFile << '(' << x+1 << ',' << y+1 << ')' << '\n';
	if(array[x][y] == 2)
		oFile << '(' << x+1 << ',' << y+1 << ')' << '\n';
}

int main()
{
	//open file
	fstream iFile, oFile;
	iFile.open("input.txt");
	oFile.open("109511207_output.txt",ios::out);
	
	// count number of pattern
	int c = 1; 
	
	//initialize
	int **array = new int*[17];
		for(int i=0;i<17;i++)
			array[i] = new int[17];
			
	while(iFile >> array[0][0]) 
	{
		// number of pattern 
		oFile << "pattern " << c << '\n'; 
		
		//initialize
		Point **prev = new Point*[17];
		for(int i=0;i<17;i++)
			prev[i] = new Point[17];
		int **d = new int*[17];
		for(int i=0;i<17;i++)
			d[i] = new int[17];
		for(int i=0;i<17;i++)
		{
			for(int j=0;j<17;j++)
			{
				d[i][j] = -1;
				prev[i][j].x = -1;
				prev[i][j].y = -1;
			}
		}
		queue<Point> q;
		for(int i=0;i<17;i++)
			for(int j=0;j<17;j++)
				if(i||j)
					iFile >> array[i][j];
					
		// set current point to (0,0)			
		Point curPoint = {0,0};
		
		// do BFS
		BFS(array,prev,d,curPoint,q);
		
		// output
		oFile << "step=" << d[16][16] + 1 << '\n';
		printBFS(array,prev,16,16,oFile);
		oFile << '\n';
		
		// renew number of pattern
		c++;
	}
	return 0;
}
