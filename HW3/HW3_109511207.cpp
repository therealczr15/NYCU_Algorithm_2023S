#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>

using namespace std;

class Heap
{
	public:
		vector<int> v;
		int size;	
};

void maxHeapify(Heap &h,int i)
{
	int largest;
	
	// left node index
	int l = 2*i+1;
	
	// right node index
	int r = 2*i+2;
	
	// decide the largest node is i, left or right
	if(l <= h.size-1 && h.v[l] > h.v[i])
		largest = l;
	else
		largest = i;
	if(r <= h.size-1 && h.v[r] > h.v[largest])
		largest = r;
		
	// if the largest node is not i, then swap and do maxHeapify for previous largest node
	if (largest != i )
	{
		int t = h.v[i];
		h.v[i] = h.v[largest];
		h.v[largest] = t;
		maxHeapify(h,largest);
	}	
}

void buildMaxHeap(Heap &h)
{
	h.size = h.v.size();
	for(int i=h.v.size()/2-1;i>=0;i--)
		maxHeapify(h,i);
}

void heapSort(Heap &h)
{
	buildMaxHeap(h);
	for(int i=h.v.size()-1;i>=1;i--)
	{
		int t = h.v[0];
		h.v[0] = h.v[i];
		h.v[i] = t;
		h.size--;
		maxHeapify(h,0);
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
		Heap h;
		for(int i=0;i<size;i++)
			h.v.push_back(rand());
		int showData, showSort;
		cout << "Enter 1 to show generated data otherwise hide it: "; //whether to show generated data
		cin >> showData;
		cout << "Enter 1 to show data after sorted otherwise hide it: "; //whether to show sorted data
		cin >> showSort;
		if(showData == 1)
		{
			cout << "\nThe random generated data is below:\n"; // generate random data
			for(int i=0;i<size;i++)
				cout << h.v[i] << '\n';
		}
		cout << "--------------------\n";
		cout << "Heap Sort...\n\n"; 
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		heapSort(h); // do heap sort 
		QueryPerformanceCounter(&nEndTime);
		if(showSort == 1)
		{
			cout << "After heap sort: \n";
			for(int i=0;i<size;i++)
				cout << h.v[i] << '\n';
		}
		t = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; // calculate totol time spend
		cout << "\nHeap sort time used: " << t*1000 << " ms\n";
		cout << "--------------------\n\n";
		cout << "Enter an integer for data size or enter CTRL+Z to terminate the program: ";
	}
	return 0;
} 


