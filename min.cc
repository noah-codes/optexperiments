#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef double (*F) (double);

// F : double --> double
double error(vector<double> x, F f, F h)
{
	double sum = 0;
	for(vector<double>::iterator i = x.begin(); i != x.end(); ++i)
	{
		double d = f(*i) - h(*i);
		sum += d * d;
	}
	
	return sum / x.size();
}

double derror(vector<double> x, F f, F h, F dh)
{
	double sum = 0;
	for(vector<double>::iterator i = x.begin(); i != x.end(); ++i)
	{
		sum += (f(*i) - h(*i)) * dh(*i);
	}
	
	return 2 * sum;
}

auto build_h(double n) -> function<double (double)>
{
	return [=] (double x) { return n * x; };
}

int main(int argc, char * argv[])
{
	auto f = [] (double x) { return 2 * x; };
	auto h = [] (double x) { return 2 * x; };
	
	auto g = build_h(3);
	cout << g(10) << endl;
	
	vector<double> x;
	x.push_back(10);
	x.push_back(11);
	x.push_back(11);
	x.push_back(12);
	
	cout << error(x, f, h) << endl;
}


