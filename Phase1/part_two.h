pair<std::vector<int>, int> detect_part_two(std::vector<std::vector<int>> deals, std::vector<int> state, std::vector<int> column_to_profit, int profit, int i){
    if(i<0) {return pair<std::vector<int>, int> (std::vector<int>(0), 0);}

    // If cycle present here
    bool cycle_here = true;
    for(int j=0; j<deals[0].size(); j++){
        if((state[j]+deals[i][j])!=0) {cycle_here = false;}
    }
    if(cycle_here) {return pair<std::vector<int>, int> (std::vector<int>(1, i), profit+column_to_profit[i]);}
    
    // i th deal is not taken
    pair<std::vector<int>, int> not_taken = detect_part_two(deals, state, column_to_profit, profit, i-1);
    
    // If i th deal taken
    for(int j=0; j<deals[0].size(); j++){
        state[j] += deals[i][j];
    }
    profit += column_to_profit[i];
    pair<std::vector<int>, int> taken = detect_part_two(deals, state, column_to_profit, profit, i-1);

    if(not_taken.first.size()!=0 && taken.first.size()!=0 && not_taken.second>0 && taken.second>0){
        if(not_taken.second > taken.second){
            return not_taken;
        }
        else{
            taken.first.push_back(i);
            return taken;
        }
    }
    else if(not_taken.first.size()!=0 && not_taken.second>0){return not_taken;}
    else if(taken.first.size()!=0 && taken.second>0){taken.first.push_back(i); return taken;}
    else{return pair<std::vector<int>, int> (std::vector<int>(0), 0); }
}

int arbritrages_part_two(std::vector<std::vector<int>> &deals, std::vector<std::string> &column_to_order, std::vector<int> &column_to_profit){
    pair<std::vector<int>, int> arbit = detect_part_two(deals, std::vector<int> (deals[0].size(), 0), column_to_profit, 0, deals.size()-1);
    if(arbit.first.size()==0 || arbit.second<=0){std::cout << "No Trade\n"; return 0;}
    for(int i=arbit.first.size()-1; i>=0; i--){
        for(int p = 0; p < column_to_order[arbit.first[i]].length()-1; p++){
            std::cout << column_to_order[arbit.first[i]][p];
        }
        column_to_order[arbit.first[i]][column_to_order[arbit.first[i]].length()-1]=='b'?std::cout<<"s\n":std::cout<<"b\n";
    }

    std::sort(arbit.first.begin(), arbit.first.end());
    for(int i = 0; i<arbit.first.size(); i++){
        deals.erase(deals.begin()+arbit.first[i]-i);
        column_to_order.erase(column_to_order.begin()+arbit.first[i]-i);
        column_to_profit.erase(column_to_profit.begin()+arbit.first[i]-i);
    }
    return arbit.second;
}
