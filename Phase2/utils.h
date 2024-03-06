inline std::vector<std::string> splitString(std::string input) {
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
inline std::vector<std::string> getInfo(std::string s){
    std::vector<std::string> v;
    std::string c="";
    int spaces=0;
    for(int i=0;i<s.length();i++){
        if(s[i]==' ') { 
            spaces++;
            v.push_back(c);
            c="";
            if(spaces>=4 && ((s[i-1]>='a'&& s[i-1]<='z')||(s[i-1]>='A'&& s[i-1]<='Z'))&& ((s[i+1]>='a'&& s[i+1]<='z')||(s[i+1]>='A'&& s[i+1]<='Z') || s[i+1]=='$')) v.push_back("1");
        }
        else if(s[i]=='#' || s[i]=='$')
        continue;
        else{ c+=s[i]; }
    }
    v.push_back(c);
    return v;
}