#include<vector>
#include<string>
using namespace std;
struct Dealer
{
    std::string key;
    long long int bought, sold, net;
    struct Dealer* next;
    Dealer():key(NULL),bought(0),sold(0),net(0){};
    Dealer(std::string key):key(key),bought(0),sold(0),net(0){}  //constructor
};
class DealerMap{
    int numOfElements, capacity;                //number of elements and capacity of the hash map
    struct Dealer** arr;                          //base address array of the linked list

    public:
    vector<Dealer*> dealer_list;
    DealerMap(){
        numOfElements=0;
        capacity=50000;
        arr=new Dealer*[50000];
        for(int i=0;i<50000;i++)arr[i]=NULL;
    }
    int hashFunction(std::string key) {
        int bucketIndex;
        int sum = 0, factor = 31;
        for (int i = 0; i < key.length(); i++) {
            sum = ((sum % capacity) +((abs(abs((int)key[i]) * factor)) % capacity)) % capacity;
            factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
        }
        bucketIndex = sum;
        return bucketIndex;
    }
    void insert( std::string key) {
        int bucketIndex = hashFunction(key);
        Dealer* newDealer=new Dealer(key);
        dealer_list.push_back(newDealer);
        if (arr[bucketIndex] == NULL) {
            arr[bucketIndex] = newDealer;
        }
        // Collision
        else {
            newDealer->next = arr[bucketIndex];
            arr[bucketIndex] = newDealer;
        }
    }
    Dealer* search( std::string key) {
        int bucketIndex = hashFunction(key);
        struct Dealer* bucketHead = arr[bucketIndex]; 
        while (bucketHead != NULL) {       
            // Key is found in the hashMap
            if (bucketHead->key==key) {
                return bucketHead;
            }     
            bucketHead = bucketHead->next;
        }
        return NULL;
    }
};
