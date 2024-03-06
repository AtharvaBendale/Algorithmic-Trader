// This is your trader. Place your orders from here

#include <iostream>
#include <string>
#include <atomic>
#include<fstream>
#include<thread>
#include<chrono>
#include<vector>
#include<mutex>
#include"market.h"
using namespace std;
extern std::mutex printMutex;
extern std::atomic<int> commonTimer;
long long int cnt=0;
Map<Median>deals;
Map<heap> deals_price;
hashMap stocks;
vector<string> stock_array;

int reader(int time)
{
    ifstream infile;
    infile.open("output.txt");
    string line, client_name="22B0901_22B1061";
    long long int i=0;
    while(i<cnt){getline(infile, line); i++;}
    while(getline(infile, line)){
        if(line=="TL") { continue; }
        if(line=="!@") {
            infile.close();
            return 1;
        }
        cnt++;
        vector<string> order = getInfo(line);
        if(order[1]==client_name){ continue; }
        vector<int> new_order_state (stock_array.size(), 0);
        int price = stoi(order[order.size()-3]),quantity=stoi(order[order.size()-2]),start_time = stoi(order[0]), exp_time = stoi(order[order.size()-1])+start_time;
        if(quantity==0) {continue;}
        bool buy_or_sell = (order[2]=="BUY");
        for(int j=3; j<order.size()-3; j+=2){
            int index = stocks.search(order[j]);
            if(index!=-1){new_order_state[index] = stoi(order[j+1]);}
            else{new_order_state.push_back(stoi(order[j+1])); stock_array.push_back(order[j]); stocks.insert(order[j], new_order_state.size()-1);}
        }
        Median* exists_or_not=deals.getdata(new_order_state);
        if(!exists_or_not)
        {
            exists_or_not=new Median();
            deals.insert(new_order_state,exists_or_not);
        }
        heap* new_heap = deals_price.getdata(new_order_state);

        if(new_heap==nullptr){
            new_heap = new heap(new_order_state);
            deals_price.insert(new_order_state, new_heap);
        }
        new_heap->process2(exists_or_not, buy_or_sell, start_time, order[1], start_time, exp_time, cnt, quantity, price);

        //BUY order
        if(buy_or_sell){
            while(new_heap->buy_heap.first->top() && !(exists_or_not->invalid()) && (float)(new_heap->buy_heap.first->top()->price) > exists_or_not->get()){
                DealNode* buy_node=new_heap->buy_heap.first->top();
                {
std::lock_guard<std::mutex> lock(printMutex);

                cout << time << " " << client_name << " SELL ";
                for(int j=0;j<stock_array.size();j++){
                    if(new_order_state[j]!=0){ cout<<stock_array[j]<<" "<<new_order_state[j]<<" ";}
                }
                cout<<"$"<< buy_node->price << " #"<< buy_node->quantity << " ";
                cout<<((buy_node->exp_time>=buy_node->start_time)?buy_node->exp_time-buy_node->start_time:-1)<<endl;
}
                exists_or_not->insert(buy_node->price,buy_node->quantity);
                new_heap->buy_heap.first->delete_element(buy_node->price_index);
                if(buy_node->start_time<=buy_node->exp_time){
                    new_heap->buy_heap.second->delete_element(buy_node->time_index);
                } else {delete buy_node;}
            }
        }
        //SELL order
        else{
           while(new_heap->sell_heap.first->top() && !(exists_or_not->invalid()) && ((float)(new_heap->sell_heap.first->top()->price) < exists_or_not->get())){
                DealNode* sell_node=new_heap->sell_heap.first->top();
                {
std::lock_guard<std::mutex> lock(printMutex);

                cout << time << " " << client_name << " BUY ";
                for(int j=0;j<stock_array.size();j++){
                    if(new_order_state[j]!=0){ cout<<stock_array[j]<<" "<<new_order_state[j]<<" ";}
                }
                cout<<"$"<< sell_node->price << " #"<< sell_node->quantity << " ";
                cout<<((sell_node->exp_time>=sell_node->start_time)?sell_node->exp_time-sell_node->start_time:-1)<<endl;
}
                exists_or_not->insert(sell_node->price,sell_node->quantity);
                new_heap->sell_heap.first->delete_element(sell_node->price_index);
                if(sell_node->start_time<=sell_node->exp_time){
                    new_heap->sell_heap.second->delete_element(sell_node->time_index);
                } else {delete sell_node;}
            } 
        }
        new_heap = nullptr;
        order.clear();
        new_order_state.clear();
    }    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    infile.close();
    if(line=="!@"){ return 1; }
    return 0;
}

int trader(std::string *message)
{
    return 1;
}

void* userThread(void* arg)
{
    int thread_id = *(int*)arg;
    while(true)
    {
        int currentTime;
        {
            currentTime = commonTimer.load();
        }
        int end = reader(currentTime);
        if (end) break;
    }
    return nullptr;
}

void* userTrader(void* arg)
{
    return nullptr;
}