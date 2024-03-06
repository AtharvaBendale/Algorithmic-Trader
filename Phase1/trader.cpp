#include "receiver.h"
#include "hash_map.h"
#include "map.h"
#include "pair.h"
#include "utils.h"
#include "part_two.h"
#include "part_three.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc,char** argv) {
    
    Receiver rcv; 
    bool foundDollar = false;
    std::string message = "";
    while(!foundDollar){
        std::string buff = rcv.readIML();
        message += buff;
        if(buff.find('$') != std::string::npos) {
            rcv.terminate(); foundDollar = true;
        }
    }

    if(std::stoi(argv[1])==1)
    {
        hashMap *M=new hashMap();
        std::vector<std::string>lines=splitString(message);
        for(auto line: lines)
        {
            std::vector<std::string> stock_info=get_info(line);
            int offer = std::stoi(stock_info[1]);
            if(!M->search(stock_info[0])) {
                M->insert(stock_info[0],offer);
                std::cout<<stock_info[0]<<" "<<stock_info[1]<<" ";
                (stock_info[2][0]=='s')?std::cout<<"b\n":std::cout<<"s\n";
            }      
            else{
                HashNode* stock=M->search(stock_info[0]);
                // Checking if there exists an initial order which can cancel this order
                if(stock_info[2][0]=='s' && offer>=stock->best_sell){ std::cout<<"No Trade\n"; continue;}
                if(stock_info[2][0]=='b' && offer<=stock->best_buy){ std::cout<<"No Trade\n"; continue;}
                if(stock_info[2][0]=='b' && offer==stock->best_sell){stock->best_sell = __INT32_MAX__;
                if(offer>=stock->best_buy){stock->best_buy=-__INT32_MAX__;}
                std::cout<<"No Trade\n"; continue;}
                if(stock_info[2][0]=='s' && offer==stock->best_buy){stock->best_buy = -__INT32_MAX__;
                if(offer<=stock->best_sell){stock->best_sell=__INT32_MAX__;}
                std::cout<<"No Trade\n"; continue;}

                if(offer<stock->value && stock_info[2][0]=='s' && offer!=stock->best_sell){
                    stock->value=offer;
                    std::cout<<stock_info[0]<<" "<<stock_info[1]<<" b\n";
                    stock->best_sell = __INT32_MAX__;
                }
                else if(offer>stock->value && stock_info[2][0]=='b' && offer!=stock->best_buy){
                    stock->value=offer;
                    std::cout<<stock_info[0]<<" "<<stock_info[1]<<" s\n";
                    stock->best_buy = -__INT32_MAX__;
                }
                else{
                    std::cout<<"No Trade\n";
                    if(stock_info[2][0]=='s' && offer<stock->best_sell){stock->best_sell = offer;}
                    else if(stock_info[2][0]=='b' && offer>stock->best_buy){stock->best_buy = offer;}
                }
            }  
        }
    }
    
    else if(std::stoi(argv[1])==2)
    {
        int total_profit = 0;
        Map m;                                                               // a map from the stocks to their index
        std::vector<std::string> stocks;                                     // all stock names
        std::vector<int>prices, sign_arr;                                    // prices for each order 
        std::vector<std::vector<int>> grid;                                  // the row represents an order and each column represents a stock
        std::vector<std::string> order_rows;
        int order_no=0;
        std::vector<std::string> allOrders = splitString(message);
        for(int order=0;order<allOrders.size();order++){
            std:: string s=allOrders[order];
            s.erase(std::remove(s.begin(), s.end(), '\r'), s.cend());       //stripping the order of leading and trailing carriage return
            s.erase(std::remove(s.begin(), s.end(), '\n'), s.cend());       //stripping the order of leading and trailing carriage return
            std::vector<std::string>deal=get_info(s);
            int flag_sign = (deal[deal.size()-1]=="b")?1:(-1);
            for(int i=0;i<deal.size()-2;i+=2){
                int flag=-1;
                for(int j=0; j<stocks.size();j++){
                    if(stocks[j]==deal[i])
                    {flag=j; break;}
                }
                if(flag==-1){                                               // this stock in the order has not been encountered before
                for(int i=0;i<grid.size();i++) grid[i].push_back(0);
                    stocks.push_back(deal[i]);
                    m[deal[i]]=stocks.size()-1;
                }
            }
            std::vector<int>new_row(stocks.size(),0);
            for(int i=0;i<deal.size()-2;i+=2){
                new_row[m[deal[i]]]=flag_sign * stoi(deal[i+1]);
            }
            for(int i=0;i<deal.size()-2;i+=2){
                int flag=-1;
                for(int j=0; j<stocks.size();j++){
                    if(stocks[j]==deal[i])
                    {flag=j; break;}
                }
                if(flag==-1){                                               // this stock in the order has not been encountered before
                for(int i=0;i<grid.size();i++) grid[i].push_back(0);
                    stocks.push_back(deal[i]);
                    m[deal[i]]=stocks.size()-1;
                }
            }
            for(int i=0;i<deal.size()-2;i+=2){
                new_row[m[deal[i]]]=flag_sign * stoi(deal[i+1]);
            }
            bool should_not_add_new_row = false;
            int identical_index;
            for(int i=0; i<grid.size(); i++){
                should_not_add_new_row = true;
                for(int j=0; j<grid[0].size(); j++){
                    if(flag_sign * new_row[j]!=grid[i][j] * sign_arr[i]) {should_not_add_new_row = false; break;}
                }
                if(should_not_add_new_row) {identical_index = i; break;}
            }
            if(should_not_add_new_row){
                if(flag_sign != sign_arr[identical_index] && prices[identical_index]==stoi(deal[deal.size()-2]) ) {
                    grid.erase(grid.begin()+identical_index);
                    prices.erase(prices.begin()+identical_index);
                    sign_arr.erase(sign_arr.begin()+identical_index);
                    order_rows.erase(order_rows.begin()+identical_index);
                }
                else if( (flag_sign == sign_arr[identical_index]) && (flag_sign * stoi (deal[deal.size()-2]) >= prices[identical_index])){
                    if((flag_sign * stoi (deal[deal.size()-2]) != prices[identical_index])){
                        grid.erase(grid.begin()+identical_index);
                        prices.erase(prices.begin()+identical_index);
                        sign_arr.erase(sign_arr.begin()+identical_index);
                        order_rows.erase(order_rows.begin()+identical_index);
                        grid.push_back(new_row);
                        sign_arr.push_back(flag_sign);
                        prices.push_back(flag_sign * stoi(deal[deal.size()-2]));
                        order_rows.push_back(s);
                    }
                } else {
                    grid.push_back(new_row);
                    sign_arr.push_back(flag_sign);
                    prices.push_back(flag_sign * stoi(deal[deal.size()-2]));
                    order_rows.push_back(s);
                }
            }
            else{
                    grid.push_back(new_row);
                    sign_arr.push_back(flag_sign);
                    prices.push_back(flag_sign * stoi(deal[deal.size()-2]));
                    order_rows.push_back(s);
            }

            total_profit += arbritrages_part_two(grid, order_rows, prices);
        }
        std::cout << total_profit << std::endl;
    }
    else if(std::stoi(argv[1])==3)
    {
        int total_profit = 0;
        Map m;                                                              // a map from the stocks to their index
        std::vector<std::string> stocks;                                    // all stock names
        std::vector<Order*> book;                                           // the row represents an order and each column represents a stock
        std::vector<std::string> order_rows;
        std::vector<std::string> allOrders = splitString(message);
        for(std::string s : allOrders){
            s.erase(std::remove(s.begin(), s.end(), '\r'), s.cend());
            s.erase(std::remove(s.begin(), s.end(), '\n'), s.cend());
            std::vector<std::string> deal = get_info(s);
            int flag_sign = (deal[deal.size()-1]=="b")?1:(-1);
            for(int i=0;i<deal.size()-3;i+=2){
                if(!m.has(deal[i])){                                       // this stock in the order has not been encountered before
                    for(int j=0;j<book.size();j++) {book[j]->stocks.push_back(0);}
                    stocks.push_back(deal[i]);
                    m[deal[i]]=stocks.size()-1;
                }
            }
            Order* new_order = new Order(flag_sign * stoi(deal[deal.size()-3]), stoi(deal[deal.size()-2]), s, stocks.size(), flag_sign);
            for(int i=0;i<deal.size()-3;i+=2){
                new_order->stocks[m[deal[i]]] = flag_sign * stoi(deal[i+1]);
            }
            bool should_not_add_new_row = false, check_arbritrage = true;;
            int identical_index;
            for(int i=0; i<book.size(); i++){
                if(stoi(deal[deal.size()-3]) != book[i]->price * book[i]->sign) {continue;}
                should_not_add_new_row = true;
                for(int j=0; j<book[0]->stocks.size(); j++){
                    if(flag_sign * new_order->stocks[j] != book[i]->stocks[j] * book[i]->sign) {should_not_add_new_row = false; break;}
                }
                if(should_not_add_new_row) {identical_index = i; break;}
            }
            if(should_not_add_new_row){
                if(flag_sign == book[identical_index]->sign){
                    new_order->quantity += book[identical_index]->quantity;
                    book.erase(book.begin()+identical_index);
                    book.push_back(new_order);
                }
                else{
                    if(new_order->quantity == book[identical_index]->quantity){book.erase(book.begin()+identical_index); check_arbritrage = false;}
                    else if(new_order->quantity < book[identical_index]->quantity){
                        book[identical_index]->quantity -= new_order->quantity;
                        check_arbritrage = false;
                    }
                    else{
                        new_order->quantity -= book[identical_index]->quantity;
                        book.erase(book.begin()+identical_index);
                        book.push_back(new_order);
                    }
                }
            } else {book.push_back(new_order);}
            if(check_arbritrage) {total_profit += arbritrages_part_three(book);}
            else{cout << "No Trade\n";}
        }
        std::cout << total_profit << std::endl;
    }
}