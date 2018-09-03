#include "Stock.h"
using namespace std;



Stock::Stock()
{
}

Stock::Stock(string symbol, string companyName, float lastPrice, float change, float volume)
{
	this->symbol = symbol;
	this->companyName = companyName;
	this->lastPrice = lastPrice;
	this->change = change;
	this->volume = volume;
}


Stock::~Stock()
{
}