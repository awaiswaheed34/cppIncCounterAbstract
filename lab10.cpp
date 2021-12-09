#include <iostream>
using namespace std;

class Counter {
public:
	virtual void inc() = 0;
	virtual void dec() = 0;
	virtual operator int() = 0;
	virtual ~Counter() {};
};


class LimitedCounter :public Counter
{
public:

	LimitedCounter(int init, int up)
	{
		initial = init;
		upper = up;
	}

	void inc()
	{
		if (initial < upper)
			initial++;
	}
	void dec()
	{
		if (initial > 0)
			initial--;
	}
	operator int()
	{
		return initial;
	}

private:
	int initial;
	int upper;
};


class OverflowCounter : public Counter
{
public:
	OverflowCounter(int init, int up)
	{
		initial = init;
		upper = up;
	}
	void inc()
	{
		if (initial == upper)
		{
			initial = 0;
		}
		else
		{
			initial++;
		}
	}

	void dec()
	{
		if (initial == 0)
		{
			initial = upper;
		}
		else
		{
			initial--;
		}
	}
	operator int()
	{
		return initial;
	}
private:
	int initial;
	int upper;

};

void UseCounter(Counter& ctr, int num);

int main(int argc, char** argv) {
	LimitedCounter lc(0, 5);
	OverflowCounter oc(5, 9);

	cout << oc << endl;
	UseCounter(oc, 5);
	cout << oc << endl; // should display zero
	UseCounter(oc, -1);
	cout << oc << endl; // should display 9
	oc.dec();
	cout << oc << endl; // should display 8

	cout << lc << endl;
	lc.inc();
	cout << lc << endl;
	lc.dec();
	cout << lc << endl;
	for (int i = 0; i < 10; ++i) lc.inc();
	cout << lc << endl;
	UseCounter(lc, -9);
	cout << lc << endl;

	return 0;
}


void UseCounter(Counter& ctr, int num)
{
	if (num < 0)
	{
		num *= -1;
		for (int i = 0; i < num; i++)
		{
			ctr.dec();
		}
	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			ctr.inc();
		}
	}
}