#include<sstream>

std::vector<std::string> splitString(std::string input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token="";
    for(int i=0;i<input.length();i++)
    {
        if(input[i]=='$') {return tokens;}
        if(input[i]=='#')
        {
            tokens.push_back(token);
            token="";
            continue;
        }
        token+=input[i];
    }    
    return tokens;
}
std::vector<std::string> get_info(std::string s){
    std::vector<std::string> words;
    std::istringstream iss(s);
    std::string word;
    while(iss>>word){
        words.push_back(word);
    }
    return words;
}