#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void swap(int &a,int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int RM_Partition(vector<int> &v,int p,int r)
{
	int i = rand()%(r-p+1)+p;
	swap(v[r],v[i]);
	int pivot = v[r];
	i = p - 1;
	for(int j=p;j<=r-1;j++)
	{
		if(v[j] <= pivot)
		{
			i++;
			swap(v[i],v[j]);
		}
	}
	swap(v[i+1],v[r]);
	return (i+1);
}

void RM_Quicksort(vector<int> &v,int p,int r)
{
	if(p<r)
	{
		int q = RM_Partition(v,p,r);
		RM_Quicksort(v,p,q-1);
		RM_Quicksort(v,q+1,r);
	}
}

int main()
{
	srand(time(NULL));
	int size;
	double t;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	cout << "Enter an integer for data size or enter CTRL+Z to terminate the program: ";
	while(cin >> size)
	{
		vector<int> v;
		for(int i=0;i<size;i++)
			v.push_back(rand());
		int showData, showSort;
		cout << "Enter 1 to show generated data otherwise hide it: "; //whether to show generated data
		cin >> showData;
		cout << "Enter 1 to show data after sorted otherwise hide it: "; //whether to show sorted data
		cin >> showSort;
		if(showData == 1)
		{
			cout << "\nThe random generated data is below:\n"; // generate random data
			for(int i=0;i<size;i++)
				cout << v[i] << '\n';
		}
		cout << "--------------------\n";
		cout << "Quick Sort...\n\n"; 
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		RM_Quicksort(v,0,v.size()-1); // do quick sort 
		QueryPerformanceCounter(&nEndTime);
		if(showSort == 1)
		{
			cout << "After quick sort: \n";
			for(int i=0;i<size;i++)
				cout << v[i] << '\n';
		}
		t = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; // calculate totol time spend
		cout << "\nQuick sort time used: " << t*1000 << " ms\n";
		cout << "--------------------\n\n";
		cout << "Enter an integer for data size or enter CTRL+Z to terminate the program: ";
	}
	return 0;
} 


