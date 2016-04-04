#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>

// TODO : http://axon.cs.byu.edu/papers/Wilson.nn03.batch.pdf

using namespace std;

typedef function<double (double)> F;

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

// Key point : note that since we're deriving with respect to the weights, the derivative is *i NOT n
double derror(vector<double> x, F f, F h)
{
	double sum = 0;
	for(vector<double>::iterator i = x.begin(); i != x.end(); ++i)
	{
		sum += (f(*i) - h(*i)) * (*i);
	}
	
	return sum;
}

auto build_h(double n) -> function<double (double)>
{
	return [=] (double x) { return n * x; };
}

int main(int argc, char * argv[])
{
	vector<double> x;
	for (int i = -50; i < 50; ++i)
	{
		x.push_back(i);
	}
	
	auto f = [] (double x) { return 3 * x; };
	
	for(int i = -6; i <= 6; ++i)
	{
		auto h = build_h(i);
		cout << "HYPOTHESIS: h(x) = " << i << "x" << endl;
		cout << "ERROR: " << error(x, f, h) << endl;	
		cout << "DERIV: " << derror(x, f, h) << endl;
	}
}


