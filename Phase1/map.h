#include<vector>
#include<string>

struct MapNode{
    std::string key;
    int value;
    MapNode* next;
    MapNode(std::string key, int value):key(key), value(value), next(NULL){}
};
class Map{
    public:
    int MAP_SIZE;
    MapNode** Map_table;
    std::vector<std::string> stored; 
    Map(int NEW_SIZE = 50000){
        MAP_SIZE = NEW_SIZE;
        Map_table = new MapNode*[MAP_SIZE];
        for(int i=0; i<MAP_SIZE; i++) { Map_table[i]=NULL; }
    }
    int hash_function(std::string key) {
        int bucketIndex;
        int sum = 0, factor = 31;
        for (int i = 0; i < key.length(); i++) {
            sum = ((sum % MAP_SIZE) +((abs(abs((int)key[i]) * factor)) % MAP_SIZE)) % MAP_SIZE;
            factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
        }
        bucketIndex = sum;
        return bucketIndex;
    }
    int& operator[](std::string key) {
        int index = hash_function(key);
        MapNode* curr = Map_table[index];
        if(!curr) {
            Map_table[index] = new MapNode(key, 0);
            stored.push_back(key);
            return Map_table[index]->value;
        }
        while(key != curr->key){
            curr = curr->next;
            if(!curr){
                curr = new MapNode(key, 0);
                stored.push_back(key);
                return curr->value;
            }
        }
        return curr->value;
    }
    bool has(std::string key){
        int index = hash_function(key);
        MapNode *curr = Map_table[index];
        if(!curr) {return false;}
        while(curr->next && curr->key!=key){curr = curr->next;}
        if(curr->key!=key) {return false;}
        else{return true;}
    }
    bool all_zero(){
        for(std::string key : stored){
            if((*this)[key]!=0) {return false;}
        }
        return true;
    }
};