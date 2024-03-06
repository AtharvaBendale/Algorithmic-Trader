#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<unistd.h>
#include "market.h"
using namespace std;

market::market(int argc, char** argv)
{
    timestamp = -__INT32_MAX__;
    trades_done = 0;
    total_money_transfered = 0;
    total_shares_transfered = 0;
}


void market::start()
{
	ifstream infile;
    infile.open("output.txt");
    long long int order_cnt = 0;
    string line; getline(infile, line);
    while(getline(infile, line)){
        if(line == "!@") {break;}
        order_cnt++;
        vector<string> order = getInfo(line);
        vector<int> new_order_state (stock_array.size(), 0);
        bool buy_or_sell = (order[2]=="BUY");             // "true" for buy order, "false" for sell order
        int price = stoi(order[order.size()-3]), quantity = stoi(order[order.size()-2]), start_time = stoi(order[0]);
        int exp_time = stoi(order[order.size()-1]) + start_time;
        timestamp = start_time;
        if(quantity==0) {continue;}
        // Making the state vector of new order
        for(int i=3; i<order.size()-3; i+=2){
            int index = stocks.search(order[i]);
            if(index!=-1){new_order_state[index] += stoi(order[i+1]);}
            else{new_order_state.push_back(stoi(order[i+1])); stock_array.push_back(order[i]); stocks.insert(order[i], new_order_state.size()-1);}
        }

        // Searching for existing heap in the tree, if not present then making a new heap
        heap* new_heap = deals.getdata(new_order_state);

        if(new_heap==nullptr){
            new_heap = new heap(new_order_state);
            deals.insert(new_order_state, new_heap);
        }

        if(!dealer_map.search(order[1])){dealer_map.insert(order[1]);}

        new_heap->process(dealer_map, stock_array, buy_or_sell, timestamp, trades_done, total_money_transfered, total_shares_transfered, order[1], start_time, exp_time, order_cnt, quantity, price);

    }

    // Printing End Of Day statistics
    cout << endl << "---End of Day---" << endl <<"Total Amount of Money Transferred: $" << total_money_transfered << endl << "Number of Completed Trades: " << trades_done << endl << "Number of Shares Traded: " << total_shares_transfered << endl;
    vector<Dealer*> dealer_list = dealer_map.dealer_list;
    for(Dealer* i : dealer_list) {
        cout << i->key << " bought " << i->bought << " and sold " << i->sold << " for a net transfer of $" << i->net << endl;
    }
}
