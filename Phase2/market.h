#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "old_map.h"
#include "hash_map.h"
#include "utils.h"
using namespace std;

class market
{
public:
    DealerMap dealer_map;
    int timestamp;
    long long int trades_done, total_money_transfered, total_shares_transfered;
    Map <heap> deals;
    hashMap stocks;
    vector<string> stock_array;

	market(int argc, char** argv);
	void start();
private:
};
