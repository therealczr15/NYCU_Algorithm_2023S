#include <iostream>
#include <climits>

using namespace std;

int max_top_down_cut_rod_aux(const int *p, int n, int *r, int *s)
{
	int q;
	if(r[n] >= 0)
		return r[n];
	if(n == 0)
		q = 0;
	else 
	{
		q = -1;
		int size = (n > 10) ? 10 : n;
		for(int i=1;i<=size;i++)
		{
			if(q <= (p[i] + max_top_down_cut_rod_aux(p,n-i,r,s)))
			{
				q = p[i] + max_top_down_cut_rod_aux(p,n-i,r,s);
				s[n] = i;
			}
		}
	}
	r[n] = q;
	return q;
}

void max_top_down_cut_rod(const int *p, int n)
{
	int *r = new int[n+1];
	int *s = new int[n+1];
	for(int i=0;i<=n;i++)
		r[i] = -1;
	cout << "maximum price: " << max_top_down_cut_rod_aux(p,n,r,s) << '\n';
	int count = 0;
	while(n > 0)
	{
		cout << s[n] << ' ';
		n = n - s[n];
		count++;
	}
	cout << '\n';
	cout << "number of pieces: " << count << '\n';
}

int min_top_down_cut_rod_aux(const int *p, int n, int *r, int *s)
{
	int q;
	if(r[n] >= 0)
		return r[n];
	if(n == 0)
		q = 0;
	else 
	{
		q = INT_MAX;
		int size = (n > 10) ? 10 : n;
		for(int i=1;i<=size;i++)
		{
			if(q >= (p[i] + min_top_down_cut_rod_aux(p,n-i,r,s)))
			{
				q = p[i] + min_top_down_cut_rod_aux(p,n-i,r,s);
				s[n] = i;
			}
		}
	}
	r[n] = q;
	return q;
}

void min_top_down_cut_rod(const int *p, int n)
{
	int *r = new int[n+1];
	int *s = new int[n+1];
	for(int i=0;i<=n;i++)
		r[i] = -1;
	cout << "minimum price: " << min_top_down_cut_rod_aux(p,n,r,s) << '\n';
	int count = 0;
	while(n > 0)
	{
		cout << s[n] << ' ';
		n = n - s[n];
		count++;
	}
	cout << '\n';
	cout << "number of pieces: " << count << '\n';
}

void top_down(const int *p, int n)
{
	cout << "\nTop Down:\n";
	cout << "total length: " << n << '\n';
	max_top_down_cut_rod(p,n);	
	cout << '\n';
	min_top_down_cut_rod(p,n);
}

void max_bot_up_cut_rod(const int *p, int n)
{
	int *r = new int[n+1];
	int *s = new int[n+1];
	r[0] = 0;
	int q;
	for(int j=1;j<=n;j++)
	{
		q = -1;
		int size = (j > 10) ? 10 : j;
		for(int i=1;i<=size;i++)
		{
			if(q <= p[i] + r[j-i])
			{
				q = p[i] + r[j-i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	cout << "maximum price: " << r[n] << '\n';
	int count = 0;
	while(n > 0)
	{
		cout << s[n] << ' ';
		n = n - s[n];
		count++;
	}
	cout << '\n';
	cout << "number of pieces: " << count << '\n';
}

void min_bot_up_cut_rod(const int *p, int n)
{
	int *r = new int[n+1];
	int *s = new int[n+1];
	r[0] = 0;
	int q;
	for(int j=1;j<=n;j++)
	{
		q = INT_MAX;
		int size = (j > 10) ? 10 : j;
		for(int i=1;i<=size;i++)
		{
			if(q >= p[i] + r[j-i])
			{
				q = p[i] + r[j-i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	cout << "minimum price: " << r[n] << '\n';
	int count = 0;
	while(n > 0)
	{
		cout << s[n] << ' ';
		n = n - s[n];
		count++;
	}
	cout << '\n';
	cout << "number of pieces: " << count << '\n';
}

void bot_up(const int *p, int n)
{
	cout << "\nBottom Up:\n";
	cout << "total length: " << n << '\n';
	max_bot_up_cut_rod(p,n);	
	cout << '\n';
	min_bot_up_cut_rod(p,n);
}

int main()
{
	int rodLength;
	int *price = new int[11];
	cout << "Input rod length or CTRL-Z to terminate the program: ";
	while(cin >> rodLength)
	{
		price[0] = 0;
		for(int i=1;i<=10;i++)
		{
			cout << "Input rod price of length " << i << ": ";
			cin >> price[i];
		}
		top_down(price,rodLength);
		bot_up(price,rodLength);
		cout << "Input rod length or CTRL-Z to terminate the program: ";
	}
	return 0;
}
