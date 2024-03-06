struct Order{
    std::vector<int> stocks;
    int price, quantity, sign;
    std::string line;
    Order(int price, int quantity, std::string line, int vec_size, int flag_sign):price(price),quantity(quantity),line(line),sign(flag_sign){stocks = std::vector<int> (vec_size, 0);}
};

pair<std::vector<pair<int, int>>, int> detect_part_three(std::vector<Order*> book, std::vector<int> state, int profit, int i);

int arbritrages_part_three(std::vector<Order*> &book){
    if(book.size()<=0) {return 0;}
    if(book.size()==1) {std::cout << "No Trade\n"; return 0;}

    std::vector<int> state (book[book.size()-1]->stocks.size(), 0);
    pair<std::vector<pair<int,int>>, int> result = detect_part_three(book, state, 0, book.size()-1);
    
    if(result.first.size()==0 || result.second<=0){std::cout << "No Trade\n"; return 0;}
    for(int i=result.first.size()-1; i>=0; i--){
        std::string line = book[result.first[i].first]->line;
        char buy_or_sell = line[line.length()-1]=='b'?'s':'b';
        line.pop_back(); line.pop_back();
        while(line[line.length()-1]!=' ') {line.pop_back();}
        std::cout << line << result.first[i].second << " " << buy_or_sell << "\n";
    }

    for(int i=0; i<result.first.size(); i++){
        if(book[result.first[i].first]->quantity < result.first[i].second){
            std::cerr << "Quantity demanded for order no. " << result.first[i].first << " : \"" << book[i]->line << "\" is " << result.first[i].second << " and available is " << book[result.first[i].first]->quantity << "\n";
        }
    }
    std::sort(result.first.begin(), result.first.end());
    int cnt = 0;
    for(int i=0; i<result.first.size(); i++){
        if(book[result.first[i].first]->quantity == result.first[i].second){
            book.erase(book.begin()+result.first[i].first-cnt++);
        } else{
            book[result.first[i].first]->quantity -= result.first[i].second;
        }
    }
    return result.second;
}

pair<std::vector<pair<int, int>>, int> detect_part_three(std::vector<Order*> book, std::vector<int> state, int profit, int i){
    if(i<0) {return pair<std::vector<pair<int,int>>, int> (std::vector<pair<int,int>>(0, pair<int,int>(0,0)), 0);}

    std::vector<pair<std::vector<pair<int, int>>, int>> poss;
    poss.push_back(detect_part_three(book, state, profit, i-1));

    for(int q = 1; q <= book[i]->quantity; q++){
        bool cycle_here = true;
        for(int j=0; j<state.size(); j++){
            state[j] += book[i]->stocks[j];
            if(cycle_here && state[j]!=0) {cycle_here = false;}
        }
        profit += book[i]->price;
        if(cycle_here){return pair<std::vector<pair<int, int>>, int> (std::vector<pair<int,int>> (1, pair<int, int> (i ,q)), profit);}
        poss.push_back(detect_part_three(book, state, profit, i-1));
    }

    int max_profit_index = -1, max_profit = -__INT32_MAX__;
    for(int j=0; j<poss.size(); j++){
        if(poss[j].second > max_profit){max_profit = poss[j].second;  max_profit_index = j;}
    }
    if(max_profit_index!=0){poss[max_profit_index].first.push_back(pair<int, int> (i, max_profit_index));}
    return poss[max_profit_index];
}
