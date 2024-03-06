#include<vector>
using namespace std;

struct DealNode{
    string dealer;
    int price, quantity;
    int start_time, exp_time;
    int price_index, time_index; // price_time is index of this DealNode in the price_heap's vector, time_index is index of this DealNode in the time_heap's vector

    operator >(const DealNode &deal1, const DealNode &deal2){
        return (deal1.price>deal2.price) || ((deal1.price==deal2.price) && (deal1.start_time<deal2.start_time || (deal1.start_time==deal2.start_time && (deal1.dealer.compare(deal2.dealer)<0))));
    }
    operator ==(const DealNode &deal1, const DealNode &deal2){
        return (deal1.price==deal2.price) && (deal1.start_time==deal2.start_time) && (deal1.dealer.compare(deal2.dealer)==0);
    }
    operator <(const DealNode &deal1, const DealNode &deal2){
        return deal2 > deal1;
    }
};


// A heap which uses price of deals to maintain order
class price_max_heap{
    private:
    vector<DealNode*> arr;
    int n;

    public:
    price_max_heap(){
        n=0;
    }
    int parent(int i){
        if(i>=n || i==0) return -1; 
        return (i-1)/2;
    }
    int left(int i){
        return (2*i+1 >=n)? -1 : 2*i+1;
    }
    int right(int i){
        return (2*i+2 >= n)? -1 : 2*i+2;
    }
    void swap(int i,int j){
        arr[i]->price_index=j;
        arr[j]->price_index=i;
        DealNode* temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    void heapify(int i){
        while(parent(i)!=-1 && arr[i]>arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
        }
        if(left(i)==-1) return;
        if(right(i)==-1 && arr[i] < arr[left(i)]){ swap(i, left(i)); return; }
        else{
            if(arr[i]<arr[left(i)]&& arr[i]<arr[right(i)])
            {
                if(arr[left(i)]>arr[right(i)]){swap(i,left(i));heapify(left(i));}
                else{swap(i,right(i));heapify(right(i));}
            }
            else if(arr[i]<arr[left(i)] && arr[i]>arr[right(i)]){swap(i,left(i));heapify(left(i));}
            else if(arr[i]>arr[left(i)] && arr[i]<arr[right(i)]){swap(i,right(i));heapify(right(i));}
            else return;
        } 
    }
    void insert(DealNode* node){
        arr.push_back(node);
        node->price_index=n;
        int i=n;
        while(parent(i)!=-1 && arr[i]>arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
        }
        n++;
    }
    void delete_element(int index){
        if(n){
            if(left(index)==-1 && right(index)==-1) n--;
            else{
                heapify(index);
                n--;
            }
            arr.pop_back();
        }
    }
    DealNode* top(){
        return (n>0)?arr[0]:nullptr;
    }
    int size_of_heap(){
        return n;
    }
};

class price_min_heap{
    private:
    vector<DealNode*> arr;
    int n;

    public:
    price_min_heap(){
        n=0;
    }
    int parent(int i){
        if(i>=n || i==0) return -1; 
        return (i-1)/2;
    }
    int left(int i){
        return (2*i+1 >=n)? -1 : 2*i+1;
    }
    int right(int i){
        return (2*i+2 >= n)? -1 : 2*i+2;
    }
    void swap(int i,int j){
        arr[i]->price_index=j;
        arr[j]->price_index=i;
        DealNode* temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    void heapify(int i){
        while(parent(i)!=-1 && arr[i]<arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
        }
        if(left(i)==-1) return;
        if(right(i)==-1 && arr[i] > arr[left(i)]){ swap(i, left(i)); return; }
        else{
            if(arr[i]>arr[left(i)]&& arr[i]>arr[right(i)])
            {
                if(arr[left(i)]<arr[right(i)]){swap(i,left(i));heapify(left(i));}
                else{swap(i,right(i));heapify(right(i));}
            }
            else if(arr[i]>arr[left(i)] && arr[i]<arr[right(i)]){swap(i,left(i));heapify(left(i));}
            else if(arr[i]<arr[left(i)] && arr[i]>arr[right(i)]){swap(i,right(i));heapify(right(i));}
            else return;
        } 
    }
    void insert(DealNode* node){
        arr.push_back(node);
        node->price_index=n;
        int i=n;
        while(parent(i)!=-1 && arr[i]<arr[parent(i)]){
            swap(i,parent(i));
            i=parent(i);
        }
        n++;
    }
    void delete_element(int index){
        if(n){
            if(left(index)==-1 && right(index)==-1) n--;
            else{
                heapify(index);
                n--;
            }
            arr.pop_back();
        }
    }
    DealNode* top(){
        return (n>0)?arr[0]:nullptr;
    }
    int size_of_heap(){
        return n;
    }
};

// A heap which uses price of deals to maintain order
class time_heap{
    private:
    vector<DealNode*> arr;
    int n;

    public:
    time_heap(){
        n=0;
    }
    int parent(int i){
        if(i>=n || i==0) return -1; 
        return (i-1)/2;
    }
    int left(int i){
        return (2*i+1 >=n)? -1 : 2*i+1;
    }
    int right(int i){
        return (2*i+2 >= n)? -1 : 2*i+2;
    }
    void swap(int i,int j){
        arr[i]->time_index=j;
        arr[j]->time_index=i;
        DealNode* temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    void heapify(int i){
        while(parent(i)!=-1 && arr[i]->exp_time<arr[parent(i)]->exp_time){
            swap(i,parent(i));
            i=parent(i);
        }
        if(left(i)==-1) return;
        if(right(i)==-1 && arr[i]->exp_time > arr[left(i)]->exp_time){ swap(i, left(i)); return; }
        else{
            if(arr[i]->exp_time>arr[left(i)]->exp_time&& arr[i]->exp_time>arr[right(i)]->exp_time)
            {
                if(arr[left(i)]->exp_time<arr[right(i)]->exp_time){swap(i,left(i));heapify(left(i));}
                else{swap(i,right(i));heapify(right(i));}
            }
            else if(arr[i]->exp_time>arr[left(i)]->exp_time && arr[i]->exp_time<arr[right(i)]->exp_time){swap(i,left(i));heapify(left(i));}
            else if(arr[i]->exp_time<arr[left(i)]->exp_time && arr[i]->exp_time>arr[right(i)]->exp_time){swap(i,right(i));heapify(right(i));}
            else return;
        } 
    }
    void insert(DealNode* node){
        arr.push_back(node);
        node->time_index=n;
        int i=n;
        while(parent(i)!=-1 && arr[i]->exp_time<arr[parent(i)]->exp_time){
            swap(i,parent(i));
            i=parent(i);
        }
        n++;
    }
    void delete_element(int index){
        if(n){
            if(left(index)==-1 && right(index)==-1) n--;
            else{
                heapify(index);
                n--;
            }
            arr.pop_back();
        }
    }
    DealNode* top(){
        return (n>0)?arr[0]:nullptr;
    }
    void flush(int timestamp, price_max_heap &pr_heap){
        while(top() && top()->exp_time < timestamp){
            DealNode* temp = top();
            delete_element(temp->time_index);
            pr_heap.delete_element(temp->price_index);
            delete temp;
        }
    } // deletes all the elements from this time_heap and given price_heap having exp_time < timestamp
    void flush(int timestamp, price_min_heap &pr_heap){
        while(top() && top()->exp_time < timestamp){
            DealNode* temp = top();
            delete_element(temp->time_index);
            pr_heap.delete_element(temp->price_index);
            delete temp;
        }
    }
    int size_of_heap(){
        return n;
    }
};