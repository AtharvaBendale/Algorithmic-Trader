#include<vector>
#include "dealer_map.h"
#include "median.h"
using namespace std;

struct DealNode{
    string dealer;
    int price, quantity;
    int start_time, exp_time;
    long long int price_index, time_index; // price_time is index of this DealNode in the price_heap's vector, time_index is index of this DealNode in the time_heap's vector
    long long int order_cnt;

    bool operator >(DealNode &deal){
        return (price>deal.price) || ((price==deal.price) && (order_cnt<deal.order_cnt));
    }
    bool operator ==(DealNode &deal){
        return (price==deal.price) && (order_cnt==deal.order_cnt);
    }
    bool operator <(DealNode &deal){
        return deal > *this;
    }
    bool operator >>(DealNode &deal){
        return (price>deal.price) || ((price==deal.price) && (order_cnt>deal.order_cnt));
    }
    bool operator <<(DealNode &deal){
        return deal >> *this;
    }
    bool operator <=(DealNode &deal){
        return (*this < deal) || (*this == deal);
    }
    bool operator >=(DealNode &deal){
        return (*this > deal) || (*this == deal);
    }
};


// A heap which uses price of deals to maintain order
class price_max_heap{
    private:
    public:
    vector<DealNode*> arr;
    long long int n;

    price_max_heap(){
        n=0;
    }
    long long int parent(long long int i){
        if(i>n || i==0) return -1; 
        return (i-1)/2;
    }
    long long int left(long long int i){
        return (2*i+1 >=n)? -1 : 2*i+1;
    }
    long long int right(long long int i){
        return (2*i+2 >= n)? -1 : 2*i+2;
    }
    void swap(long long int i,long long int j){
        arr[i]->price_index=j;
        arr[j]->price_index=i;
        DealNode* temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    void heapify(long long int i){
        bool flag = false;
        while(parent(i)!=-1 && *arr[i]>*arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
            flag = true;
        }
        if(flag) {return;}
        if(left(i)==-1){return;}
        if(right(i)==-1){ if(*arr[i] < *arr[left(i)]){swap(i, left(i)); return;} }
        else{
            if(*arr[i]<*arr[left(i)] && *arr[i]<*arr[right(i)])
            {
                if(*arr[left(i)]>*arr[right(i)]){swap(i,left(i));heapify(left(i));}
                else{swap(i,right(i));heapify(right(i));}
            }
            else if(*arr[i]<*arr[left(i)]){swap(i,left(i));heapify(left(i));}
            else if(*arr[i]<*arr[right(i)]){swap(i,right(i));heapify(right(i));}
            else return;
        } 
    }
    void insert(DealNode* node){
        arr.push_back(node);
        node->price_index=n;
        long long int i=n;
        while(parent(i)!=-1 && *arr[i]>*arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
        }
        n++;
    }
    void delete_element(long long int index){
        if(n){
            swap(index,n-1);
            n--;
            heapify(index);
            arr.pop_back();
        }
    }
    DealNode* top(){
        return (n>0)?arr[0]:nullptr;
    }
    long long int size_of_heap(){
        return n;
    }
};

class price_min_heap{
    private:
    public:
    vector<DealNode*> arr;
    long long int n;

    price_min_heap(){
        n=0;
    }
    long long int parent(long long int i){
        if(i>n || i==0) return -1; 
        return (i-1)/2;
    }
    long long int left(long long int i){
        return (2*i+1 >=n)? -1 : 2*i+1;
    }
    long long int right(long long int i){
        return (2*i+2 >= n)? -1 : 2*i+2;
    }
    void swap(long long int i,long long int j){
        arr[i]->price_index=j;
        arr[j]->price_index=i;
        DealNode* temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    void heapify(long long int i){
        bool flag = false;
        while(parent(i)!=-1 && *arr[i]<<*arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
            flag = true;
        }
        if(flag){return;}
        if(left(i)==-1) return;
        if(right(i)==-1){ if(*arr[i] >> *arr[left(i)]){swap(i, left(i)); return;} }
        else{
            if(*arr[i]>>*arr[left(i)]&& *arr[i]>>*arr[right(i)])
            {
                if(*arr[left(i)]<<*arr[right(i)]){swap(i,left(i));heapify(left(i));}
                else{swap(i,right(i));heapify(right(i));}
            }
            else if(*arr[i]>>*arr[left(i)]){swap(i,left(i));heapify(left(i));}
            else if(*arr[i]>>*arr[right(i)]){swap(i,right(i));heapify(right(i));}
            else return;
        } 
    }
    void insert(DealNode* node){
        arr.push_back(node);
        node->price_index=n;
        long long int i=n;
        while(parent(i)!=-1 && *arr[i]<<*arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
        }
        n++;
    }
    void delete_element(long long int index){
        if(n){
            swap(index,n-1);
            n--;
            heapify(index);
            arr.pop_back();
        }
    }
    DealNode* top(){
        return (n>0)?arr[0]:nullptr;
    }
    long long int size_of_heap(){
        return n;
    }
};

// A heap which uses price of deals to maintain order
class time_heap{
    private:
    public:
    vector<DealNode*> arr;
    long long int n;

    time_heap(){
        n=0;
    }
    long long int parent(long long int i){
        if(i>n || i==0) return -1; 
        return (i-1)/2;
    }
    long long int left(long long int i){
        return (2*i+1 >=n)? -1 : 2*i+1;
    }
    long long int right(long long int i){
        return (2*i+2 >= n)? -1 : 2*i+2;
    }
    void swap(long long int i,long long int j){
        arr[i]->time_index=j;
        arr[j]->time_index=i;
        DealNode* temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    void heapify(long long int i){
        bool flag = false;
        while(parent(i)!=-1 && arr[i]->exp_time<arr[parent(i)]->exp_time){
            swap(i,parent(i));
            i=parent(i);
            flag = true;
        }
        if(flag){return;}
        if(left(i)==-1) return;
        if(right(i)==-1){ if(arr[i]->exp_time > arr[left(i)]->exp_time){swap(i, left(i)); return;} }
        else{
            if(arr[i]->exp_time>arr[left(i)]->exp_time&& arr[i]->exp_time>arr[right(i)]->exp_time)
            {
                if(arr[left(i)]->exp_time<arr[right(i)]->exp_time){swap(i,left(i));heapify(left(i));}
                else{swap(i,right(i));heapify(right(i));}
            }
            else if(arr[i]->exp_time>arr[left(i)]->exp_time){swap(i,left(i));heapify(left(i));}
            else if(arr[i]->exp_time>arr[right(i)]->exp_time){swap(i,right(i));heapify(right(i));}
            else return;
        } 
    }
    void insert(DealNode* node){
        if(node->start_time > node->exp_time) {return;}
        arr.push_back(node);
        node->time_index=n;
        long long int i=n;
        while(parent(i)!=-1 && arr[i]->exp_time<arr[parent(i)]->exp_time){
            swap(i,parent(i));
            i=parent(i);
        }
        n++;
    }
    void delete_element(long long int index){
        if(n){
            swap(index,n-1);
            n--;
            heapify(index);
            delete arr[n];
            arr.pop_back();
        }
    }
    DealNode* top(){
        return (n>0)?arr[0]:nullptr;
    }
    void flush(int timestamp, price_max_heap &pr_heap){
        DealNode* temp = top();
        while((temp && temp->exp_time < timestamp) || (temp && temp->quantity==0)){
            pr_heap.delete_element(temp->price_index);
            delete_element(temp->time_index);
            temp = top();
        }
    } // deletes all the elements from this time_heap and given price_heap having exp_time < timestamp
    void flush(int timestamp, price_min_heap &pr_heap){
        DealNode* temp = top();
        while((temp && temp->exp_time < timestamp)  || (temp && temp->quantity==0)){
            pr_heap.delete_element(temp->price_index);
            delete_element(temp->time_index);
            temp = top();
        }
    }
    long long int size_of_heap(){
        return n;
    }
};



class heap{
    private:
    public:
    pair<price_max_heap*, time_heap*> buy_heap;
    pair<price_min_heap*, time_heap*> sell_heap;
    vector<int> heap_state;
    long long int num_buy, num_sell;
    


    heap(vector<int> init){
        heap_state = init;
        buy_heap.first = new price_max_heap();
        buy_heap.second = new time_heap();
        sell_heap.first = new price_min_heap();
        sell_heap.second = new time_heap();
        num_buy = 0;
        num_sell = 0;
    }

    void report_deal(string buy_name, string sell_name, int quantity, int price, vector<int> state, DealerMap dealer_map, vector<string> stock_array, long long int &total_money_transfered, long long int &total_shares_transfered){
        cout << buy_name << " purchased " << quantity << " share of ";
        for(int i = 0; i<state.size(); i++){
            if(state[i]==1){
                cout << stock_array[i] << " ";
            } else if(state[i]!=0){
                cout << stock_array[i] << " " << state[i] << " ";
            }
        }
        cout << "from " << sell_name << " for $" << price << "/share\n";
        Dealer* buyer = dealer_map.search(buy_name);
        Dealer* seller = dealer_map.search(sell_name);
        buyer->bought += quantity;
        seller->sold += quantity;
        buyer->net -= quantity * price;
        seller->net += quantity * price;
        total_money_transfered += quantity * price;
        total_shares_transfered += quantity;
    }

    void process(DealerMap &dealer_map, vector<string> &stock_array, bool buy_or_sell, int timestamp, long long int &trades_done, long long int &total_money_transfered, long long int &total_shares_transfered, string dealer, int start_time, int exp_time, long long int order_cnt, int quantity, int price){

        DealNode* new_order;
        new_order = new DealNode();
        new_order->dealer = dealer;
        new_order->start_time = start_time;
        new_order->exp_time = exp_time;
        new_order->order_cnt = order_cnt;
        new_order->price_index = -1;
        new_order->time_index = -1;
        new_order->quantity = quantity;
        new_order->price = price;


        if(new_order->quantity == 0) { return;}
        buy_heap.second->flush(timestamp, *(buy_heap.first));
        sell_heap.second->flush(timestamp, *(sell_heap.first));
        num_buy = buy_heap.first->size_of_heap();
        num_sell = sell_heap.first->size_of_heap();        
        if(buy_or_sell){
            if(num_sell==0){
                buy_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    buy_heap.second->insert(new_order);
                }
                return;
            }
            DealNode* sell_node = sell_heap.first->top();
            if(new_order->price < sell_node->price){
                buy_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    buy_heap.second->insert(new_order);
                }
                return;
            }
            while(new_order->price >= sell_node->price){
                int quantity_dealed = min(new_order->quantity, sell_node->quantity);
                new_order->quantity -= quantity_dealed;
                sell_node->quantity -= quantity_dealed;
                report_deal(new_order->dealer, sell_node->dealer, quantity_dealed, sell_node->price, heap_state, dealer_map, stock_array, total_money_transfered, total_shares_transfered);
                trades_done++;
                if(sell_node->quantity==0){
                    sell_heap.first->delete_element(sell_node->price_index);
                    if(sell_node->start_time<=sell_node->exp_time){
                        sell_heap.second->delete_element(sell_node->time_index);
                    } else {delete sell_node;}
                }
                sell_node = sell_heap.first->top();
                if(new_order->quantity==0 || !sell_node){break;}
            }
            if(new_order->quantity>0){
                buy_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    buy_heap.second->insert(new_order);
                }
            } else if (new_order->quantity==0) {if(new_order){delete new_order;}}
            return;
        } else {
            if(num_buy==0){
                sell_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    sell_heap.second->insert(new_order);
                }
                return;
            }
            DealNode* buy_node = buy_heap.first->top();
            if(new_order->price > buy_node->price){
                sell_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    sell_heap.second->insert(new_order);
                }
                return;
            }
            while(new_order->price <= buy_node->price){
                int quantity_dealed = min(new_order->quantity, buy_node->quantity);
                new_order->quantity -= quantity_dealed;
                buy_node->quantity -= quantity_dealed;
                report_deal(buy_node->dealer, new_order->dealer, quantity_dealed, buy_node->price, heap_state, dealer_map, stock_array, total_money_transfered, total_shares_transfered);
                trades_done++;
                if(buy_node->quantity==0){
                    buy_heap.first->delete_element(buy_node->price_index);
                    if(buy_node->start_time<=buy_node->exp_time){
                        buy_heap.second->delete_element(buy_node->time_index);
                    } else {delete buy_node;}
                }
                buy_node = buy_heap.first->top();
                if(new_order->quantity==0 || !buy_node){break;}
            }
            if(new_order->quantity>0){
                sell_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    sell_heap.second->insert(new_order);
                }
            } else if(new_order->quantity==0) {if(new_order){delete new_order;}}
            return;
        }
    }
    void process2(Median* exists_or_not, bool buy_or_sell, int timestamp, string dealer, int start_time, int exp_time, long long int order_cnt, int quantity, int price){

        DealNode* new_order;
        new_order = new DealNode();
        new_order->dealer = dealer;
        new_order->start_time = start_time;
        new_order->exp_time = exp_time;
        new_order->order_cnt = order_cnt;
        new_order->price_index = -1;
        new_order->time_index = -1;
        new_order->quantity = quantity;
        new_order->price = price;

        if(new_order->quantity == 0) {delete new_order; return;}
        buy_heap.second->flush(timestamp, *(buy_heap.first));
        sell_heap.second->flush(timestamp, *(sell_heap.first));
        num_buy = buy_heap.first->size_of_heap();
        num_sell = sell_heap.first->size_of_heap();
        
        if(buy_or_sell){
            if(num_sell==0){
                buy_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    buy_heap.second->insert(new_order);
                }
                return;
            }
            DealNode* sell_node = sell_heap.first->top();
            if(new_order->price < sell_node->price){
                buy_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    buy_heap.second->insert(new_order);
                }
                return;
            }
            while(new_order->price >= sell_node->price){
                int quantity_dealed = min(new_order->quantity, sell_node->quantity);
                new_order->quantity -= quantity_dealed;
                sell_node->quantity -= quantity_dealed;
                exists_or_not->insert(sell_node->price, quantity_dealed);
                if(sell_node->quantity==0){
                    sell_heap.first->delete_element(sell_node->price_index);
                    if(sell_node->start_time<=sell_node->exp_time){
                        sell_heap.second->delete_element(sell_node->time_index);
                    } else {delete sell_node;}
                }
                sell_node = sell_heap.first->top();
                if(new_order->quantity==0 || !sell_node){break;}
            }
            if(new_order->quantity>0){
                buy_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    buy_heap.second->insert(new_order);
                }
            } else if (new_order->quantity==0) {if(new_order){delete new_order;}}
            return;
        } else {
            if(num_buy==0){
                sell_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    sell_heap.second->insert(new_order);
                }
                return;
            }
            DealNode* buy_node = buy_heap.first->top();
            if(new_order->price > buy_node->price){
                sell_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    sell_heap.second->insert(new_order);
                }
                return;
            }
            while(new_order->price <= buy_node->price){
                int quantity_dealed = min(new_order->quantity, buy_node->quantity);
                new_order->quantity -= quantity_dealed;
                buy_node->quantity -= quantity_dealed;
                exists_or_not->insert(buy_node->price, quantity_dealed);
                if(buy_node->quantity==0){
                    buy_heap.first->delete_element(buy_node->price_index);
                    if(buy_node->start_time<=buy_node->exp_time){
                        buy_heap.second->delete_element(buy_node->time_index);
                    } else {delete buy_node;}
                }
                buy_node = buy_heap.first->top();
                if(new_order->quantity==0 || !buy_node){break;}
            }
            if(new_order->quantity>0){
                sell_heap.first->insert(new_order);
                if(new_order->start_time<=new_order->exp_time){
                    sell_heap.second->insert(new_order);
                }
            } else if(new_order->quantity==0) {if(new_order){delete new_order;}}
            return;
        }
    }
};