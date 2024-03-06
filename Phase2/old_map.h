#include<vector>
#include<string>
#include "uberheap.h"
using namespace std;
template<typename T>
struct MapNode{
    vector<int> key;
    T* value;
    MapNode<T>* next;
    MapNode(vector<int> key, T* value):key(key), value(value) {next=NULL;}
};
template<typename T>
class Map{
    public:
    int MAP_SIZE;
    MapNode<T>** Map_table;
    Map(){
        MAP_SIZE = 50000;
        Map_table = new MapNode<T>*[MAP_SIZE];
        for(int i=0; i<MAP_SIZE; i++) { Map_table[i]=NULL; }
    }
    int hash_function(vector<int> key){
        int sum = 0, factor = 31;
        auto i = key.begin();
        auto end = key.end();
        while(i != end) {
            sum = ((sum % MAP_SIZE) +(abs((abs((int)(*i))) * factor)) % MAP_SIZE) % MAP_SIZE;
            factor = ((factor % __INT32_MAX__) * (31 % __INT32_MAX__)) % __INT32_MAX__;
            i = next(i);
        }
        return sum;
    }
    void insert(vector<int> key, T* val){
        int index = hash_function(key);
        MapNode<T> *curr = Map_table[index];
        if(!curr)
        {
            Map_table[index] = new MapNode<T>(key, val);
            return;
        }
        else{
            MapNode<T>* new_node = new MapNode<T>(key, val);
            new_node->next = Map_table[index];
            Map_table[index] = new_node;
        }
    }
    T* getdata(vector<int> key){
        int index = hash_function(key);
        MapNode<T> *curr = Map_table[index];
        if(!curr) {return nullptr;}
        while(!isEqual(curr->key, key)) {curr = curr->next; if(!curr){return nullptr;} }
        return curr->value;
    }
    bool isEqual(vector<int> key, vector<int> given){
        bool check = true;
        int i;
        for(i=0; i<min(key.size(), given.size()); i++){
            if(key[i]!=given[i]){return false;}
        }
        while(i<key.size()){
            if(key[i++]!=0){return false;}
       }
        while(i<given.size()){
            if(given[i++]!=0){return false;}
        }
        return true;
    }
};