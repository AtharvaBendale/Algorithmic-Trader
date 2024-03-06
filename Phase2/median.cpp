#include <iostream>
#include <vector>
using namespace std;
class Median{
    public:
    vector<pair<int,int>> less, more;
    int l, m;
    int parent(int i){return (i-1)/2;}
    int left(int i, int n){return (2*i+1>=n)?-1:(2*i+1);}
    int right(int i, int n){return (2*i+2>=n)?-1:(2*i+2);}
    void swap_less(int i, int j){
        pair<int, int> temp = less[i];
        less[i] = less[j];
        less[j] = temp;
    }
    void swap_more(int i, int j){
        pair<int, int> temp = more[i];
        more[i] = more[j];
        more[j] = temp;
    }
    void balance(){
        if(less.empty() && more.empty()){return;}
        if(!more.empty() && m-more[0].second>l){less_insert(more[0]);pop_more();balance();return;}
        if(!less.empty() && l-less[0].second>m){more_insert(less[0]);pop_less();balance();return;}
        return;
    }
    void less_insert(pair<int,int> new_pair){
        int i = less.size();
        less.push_back(new_pair);
        l += new_pair.second;
        while(parent(i)!=-1 && less[i]>less[parent(i)]){swap_less(i, parent(i)); i= parent(i);}
    }
    void more_insert(pair<int,int> new_pair){
        int i = more.size();
        more.push_back(new_pair);
        m += new_pair.second;
        while(parent(i)!=-1 && more[i]<more[parent(i)]){swap_more(i, parent(i)); i=parent(i);}
    }
    void pop_less(){
        l -= less[0].second;
        swap_less(0, less.size()-1);
        less.pop_back();
        heapify_less(0);
    }
    void pop_more(){
        m -= more[0].second;
        swap_more(0, more.size()-1);
        more.pop_back();
        heapify_more(0);
    }
    void heapify_less(int i){
        if(left(i,less.size())==-1){return;}
        if(right(i,less.size())==-1){
            if(less[i]<less[left(i,less.size())]){
                swap_less(i, left(i,less.size()));
                heapify_less(left(i,less.size()));
                return;
            }
        } else {
            if(less[i]<less[left(i,less.size())] && less[i]<less[right(i,less.size())]){
                if(less[left(i,less.size())]>less[right(i,less.size())]){swap_less(i, left(i,less.size())); heapify_less(left(i,less.size())); }
                else{swap_less(i, right(i,less.size())); heapify_less(right(i,less.size())); }
            } else if(less[i]<less[left(i,less.size())]){
                swap_less(i, left(i,less.size()));
                heapify_less(left(i,less.size()));
            } else if(less[i]<less[right(i,less.size())]){
                swap_less(i, right(i,less.size()));
                heapify_less(right(i,less.size()));
            }
        }
    }
    void heapify_more(int i){
        if(left(i,more.size())==-1){return;}
        if(right(i,more.size())==-1){
            if(more[i]>more[left(i,more.size())]){
                swap_more(i, left(i,more.size()));
                heapify_more(left(i,more.size()));
                return;
            }
        } else {
            if(more[i]>more[left(i,more.size())] && more[i]>more[right(i,more.size())]){
                if(more[left(i,more.size())]<more[right(i,more.size())]){swap_more(i, left(i,more.size())); heapify_more(left(i,more.size())); }
                else{swap_more(i, right(i,more.size())); heapify_more(right(i,more.size())); }
            } else if(more[i]>more[left(i,more.size())]){
                swap_more(i, left(i,more.size()));
                heapify_more(left(i,more.size()));
            } else if(more[i]>more[right(i,more.size())]){
                swap_more(i, right(i,more.size()));
                heapify_more(right(i,more.size()));
            }
        }
    }
    public:
    Median(){l = 0; m = 0;}
    void insert(int key, int freq){
        pair<int, int> new_pair (key, freq);
        if(!more.empty() && key <= more[0].first){less_insert(new_pair);}
        else{more_insert(new_pair);}
        balance();
    }
    float get(){
        if(l==0 && m==0){return -1;}
        if(l==0){return float(more[0].first);}
        if(m==0){return float(less[0].first);}
        if(l==m){return float(less[0].first+more[0].first)/float(2);}
        if(l>m){return float(less[0].first);}
        if(m>l){return float(more[0].first);}
        return float(0);
    }
};