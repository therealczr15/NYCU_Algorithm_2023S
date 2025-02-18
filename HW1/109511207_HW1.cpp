#include <iostream>
#include <cstdlib> 
#include <vector>
#include <windows.h>
#include <ctime>
using namespace std;

void istSort(vector<int> &v,int size)
{
	int key;
	int j;
	for(int i=1;i<size;i++)
	{
		key = v[i];
		j = i-1;
		while(v[j] > key && j >= 0)
		{
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = key;
	}
}

void merge(vector<int> &v,int begin,int mid,int end)
{
	int lIdx = 0, rIdx = 0;
	vector<int> v1;
	v1.assign(v.begin()+begin, v.begin()+mid+1);
	vector<int> v2;
	v2.assign(v.begin()+mid+1, v.begin()+end+1);
	v1.insert(v1.end(),2147483647);
	v2.insert(v2.end(),2147483647);
	for(int i=begin;i<=end;i++)
	{
		if(v1[lIdx] <= v2[rIdx])
		{
			v[i] = v1[lIdx];
			lIdx++;
		}
		else
		{
			v[i] = v2[rIdx];
			rIdx++;
		}
	}
}

void mgeSort(vector<int> &v,int begin,int end)
{
	int mid = (begin + end) / 2;
	if(begin < end)
	{
		mgeSort(v,begin,mid);
		mgeSort(v,mid+1,end);
		merge(v,begin,mid,end);
	}
}

int main()
{
	int size;
	double t;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	srand(time(NULL));
	cout << "Enter an integer for data size or enter CTRL+Z to terminate the program: ";
	while(cin >> size)
	{
		int mode;
		vector<int> istVec(size);
		vector<int> mgeVec(size);
		for(int i=0;i<size;i++)
		{
			istVec[i] = rand() * rand();
			mgeVec[i] = istVec[i];
		}
		cout << "Enter 1 for insertion sort, 2 for merge sort: "; //choose insertion sort or merge sort
		cin >> mode; 
		int showData, showSort;
		cout << "Enter 1 to show generated data otherwise hide it: "; //whether to show generated data
		cin >> showData;
		cout << "Enter 1 to show data after sorted otherwise hide it: "; //whether to show sorted data
		cin >> showSort;
		if(mode == 1)
		{
			if(showData == 1)
			{
				cout << "\nThe random generated data is below:\n"; // generate random data
				for(int i=0;i<size;i++)
					cout << istVec[i] << '\n';
			}
			cout << "--------------------\n";
			cout << "Insertion Sort...\n\n"; // doing insertion sorting
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBeginTime);
			istSort(istVec,size);
			QueryPerformanceCounter(&nEndTime);
			if(showSort == 1)
			{
				cout << "After insertion sort: \n";
				for(int i=0;i<size;i++)
					cout << istVec[i] << '\n';
			}
			t = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; // calculate totol time spend
			cout << "\nInsertion sort time used: " << t*1000 << " ms\n";
			cout << "--------------------\n\n";
		}
		else if(mode == 2)
		{
			if(showData == 1)
			{
				cout << "\nThe random generated data is below:\n"; // generate random data
				for(int i=0;i<size;i++)
					cout << istVec[i] << '\n';
			}
			cout << "--------------------\n";
			cout << "Merge Sort...\n\n"; // doing merge sorting
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBeginTime);
			mgeSort(mgeVec,0,size-1);
			QueryPerformanceCounter(&nEndTime);
			if(showSort == 1)
			{
				cout << "After merge sort: \n";
				for(int i=0;i<size;i++)
					cout << mgeVec[i] << '\n';
			}
			t = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; // calculate totol time spend
			cout << "\nMerge sort time used: " << t*1000 << " ms\n";
			cout << "--------------------\n\n";	
		}
		else
		{
			cout << "WRONG MODE, please enter again\n";
		}
		cout << "Enter an integer for data size or enter CTRL+Z to terminate the program: ";
	}
	
	return 0;
} 
