#pragma once
#include <string>
using namespace std;
class Stock
{
public:
	Stock();
	Stock(string, string, float, float, float);
	~Stock();
	string symbol;
	string companyName;
	float lastPrice;
	float change;
	float volume;

};