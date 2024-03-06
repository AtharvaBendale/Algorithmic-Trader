template<typename T, typename U>
class pair{
    public:
    T first;
    U second;
    pair(T a,U b): first(a),second(b){}
    pair(){}
    bool operator==(const pair& other) const {
        return (first == other.first) && (second == other.second);
    }

    // The less than operator (<)
    bool operator<(const pair& other) const {
        return (first < other.first) || ((first == other.first) && (second < other.second));
    }

    // The greater than operator (>)
    bool operator>(const pair& other) const {
        return other < *this;
    }
};
