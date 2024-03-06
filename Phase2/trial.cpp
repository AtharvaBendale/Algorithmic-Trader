#include <iostream>
#include <queue>
#include <vector>
#include <map>
#define MAP_SIZE 50000
using namespace std;

class MedianFinder {
public:
    // Constructor
    MedianFinder() {}

    // Function to add a number and its frequency to the sequence
    void addNumber(int num, int freq) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
            maxFrequency[num] += freq;
        } else {
            minHeap.push(num);
            minFrequency[num] += freq;
        }

        balanceHeaps();
    }

    // Function to get the current median
    double getMedian() {
        if (maxHeap.empty() && minHeap.empty()) {
            // No elements in the sequence
            return 0.0;
        }

        if (maxHeap.size() == minHeap.size()) {
            // Even number of elements, median is the average of the roots of both heaps
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            // Odd number of elements, median is the root of the max heap
            return maxHeap.top();
        }
    }

private:
    // Helper function to balance the heaps
    void balanceHeaps() {
        while (maxHeap.size() > minHeap.size() + 1) {
            int num = maxHeap.top();
            maxHeap.pop();
            maxFrequency[num]--;
            if (maxFrequency[num] == 0) {
                maxFrequency.erase(num);
            }

            minHeap.push(num);
            minFrequency[num]++;
        }

        while (minHeap.size() > maxHeap.size()) {
            int num = minHeap.top();
            minHeap.pop();
            minFrequency[num]--;
            if (minFrequency[num] == 0) {
                minFrequency.erase(num);
            }

            maxHeap.push(num);
            maxFrequency[num]++;
        }
    }

    // Max heap for the left half of the numbers
    priority_queue<int> maxHeap;

    // Min heap for the right half of the numbers
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Frequency maps for each heap
    map<int, int> maxFrequency;
    map<int, int> minFrequency;
};

int main() {
    vector<int> key = {0, 0, 10, 0, 12, 3, 2};
    int sum = 0, factor = 31;
    auto i = key.begin();
    auto end = key.end();
    while(i != end) {
        sum = ((sum % MAP_SIZE) +(abs)( ((abs((int)(*i))) * factor) % MAP_SIZE) % MAP_SIZE)%MAP_SIZE;
        factor = ((factor % __INT32_MAX__) * (31 % __INT32_MAX__)) % __INT32_MAX__;
        i = next(i);
    }
    cout << sum << endl;
}
