#include <iostream>
#include <vector>
#include <fstream>
#include <set> 
#include <algorithm>

using namespace std;

class Data
{
	public:
		int leftIdx;
		int rightIdx;
		double sum;
		int length;
		Data(int,int,double,int);
};

Data FindMaxCrossingSubarray(vector<double> &v,int low,int mid,int high)
{ 
	double leftSum = v[mid];
	double sum = v[mid];
	int leftIdx = mid;
	
	// find maximum of left
	for(int i=mid-1;i>=low;i--)
	{
		sum += v[i];
		if(sum > leftSum)
		{
			leftSum = sum;
			leftIdx = i;
		}
	}
	
	double rightSum = v[mid+1];
	sum = v[mid+1];
	int rightIdx = mid+1;
	
	// find maximum of right
	for(int i=mid+2;i<=high;i++)
	{
		sum += v[i];
		if(sum > rightSum)
		{
			rightSum = sum;
			rightIdx = i;
		}
	}
	return Data(leftIdx,rightIdx,leftSum + rightSum,rightIdx-leftIdx); 
}

Data FindMaxSubarray(vector<double> &v,int low,int high,vector<Data> &r)
{
	// base case
	if(low == high)
		return Data(low,high,v[low],high-low);
		
	// find mid
	int mid = (low + high)/2; 
	
	// divide into 3 parts and do recursive
	Data left = FindMaxSubarray(v,low,mid,r); 
	Data right = FindMaxSubarray(v,mid+1,high,r);
	Data cross = FindMaxCrossingSubarray(v,low,mid,high);
	
	// handle different case 
	// and use vector r to store info of current maximum subarray
	if(left.sum > right.sum && left.sum > cross.sum)
	{
		if(left.sum > r[0].sum)
		{
			r.clear();
			r.push_back(left);
		}
		else if(left.sum == r[0].sum)
			if(left.length <= r[0].length)
				r.push_back(left);
		return left;
	}
  	if(right.sum > left.sum && right.sum > cross.sum)
	{
		if(right.sum > r[0].sum)
		{
			r.clear();
			r.push_back(right);
		}
		else if(right.sum == r[0].sum)
			if(right.length <= r[0].length)
				r.push_back(right);
		return right;
	}
 	if(cross.sum > right.sum && cross.sum > left.sum)
	{
		if(cross.sum > r[0].sum)
		{
			r.clear();
			r.push_back(cross);
		}
		else if(cross.sum == r[0].sum)
			if(cross.length <= r[0].length)
				r.push_back(cross);
		return cross;
	}
	if(left.sum == right.sum && left.sum > cross.sum)
	{
		if(left.sum > r[0].sum)
		{
			r.clear();
			r.push_back(left);
			r.push_back(right);
		}
		else if(left.sum == r[0].sum)
		{
			if(left.length <= r[0].length)
				r.push_back(left);
			if(right.length <= r[0].length)
				r.push_back(right);
		}
		return left;
	}
	if(left.sum == cross.sum && left.sum > right.sum)
	{
		if(left.sum > r[0].sum)
		{
			r.clear();
			r.push_back(left);
			r.push_back(cross);
		}
		else if(left.sum == r[0].sum)
		{
			if(left.length <= r[0].length)
				r.push_back(left);
			if(cross.length <= r[0].length)
				r.push_back(cross);
		}
		return left;
	}
	if(right.sum == cross.sum && right.sum > left.sum )
	{
		if(right.sum > r[0].sum)
		{
			r.clear();
			r.push_back(right);
			r.push_back(cross);
		}
		else if(right.sum == r[0].sum)
		{
			if(right.length <= r[0].length)
				r.push_back(right);
			if(cross.length <= r[0].length)
				r.push_back(cross);
		}
		return right;
	}
	if(left.sum == right.sum && left.sum == cross.sum)
	{
		if(left.sum > r[0].sum)
		{
			r.clear();
			r.push_back(left);
			r.push_back(right);
			r.push_back(cross);
		}
		else if(left.sum == r[0].sum)
		{
			if(left.length <= r[0].length)
				r.push_back(left);
			if(right.length <= r[0].length)
				r.push_back(right);
			if(cross.length <= r[0].length)
				r.push_back(cross);
		}
		return left;
	}
} 

bool cmp(Data a,Data b)
{
	return (a.leftIdx < b.leftIdx);
}

int main()
{
	// initialize
	fstream iFile;
	iFile.open("data.txt");
	vector<double> array;
	vector<Data> rtnVec;
	vector<Data> outVec;
	int idx;
	double data;
	set<int> Set;
	
	// input
	while(iFile >> idx >> data)
		array.push_back(data);
	
	// let return vector to store info of maximum subarray
	rtnVec.push_back(Data(0,array.size()-1,0,array.size()));
	Data out = FindMaxSubarray(array,0,array.size()-1,rtnVec);
	
	// use set to avoid duplicate vector
	for(int i=0;i<rtnVec.size();i++)
	{
		if(!Set.count(rtnVec[i].leftIdx))
		{
			Set.insert(rtnVec[i].leftIdx);
			outVec.push_back(rtnVec[i]);
		}
	}
	
	// sort vector by index
	sort(outVec.begin(),outVec.end(),cmp);
	
	// output
	for(int i=0;i<outVec.size();i++)
		cout << outVec[i].leftIdx + 1 << ' ' << outVec[i].rightIdx + 1 << ' ' << outVec[i].sum << '\n';	
}

Data::Data(int l,int r,double s,int lth)
{
	leftIdx = l;
	rightIdx = r;
	sum = s;	
	length = lth;
}
