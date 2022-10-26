class Solution {
private:
    void solve(string up,string p,int index,vector<string> &ans,string mapping[]){
        if(index>=up.size()){
            ans.push_back(p);
            return;
        }
        
        int current = up[index] - '0';
        string val = mapping[current];
        
        for(int i=0;i<val.size();i++){
            p.push_back(val[i]);
            solve(up,p,index+1,ans,mapping);
            p.pop_back();
        }    
    }
public:
    vector<string> letterCombinations(string digits) {
               vector<string> ans; 

        if(digits.size()==0) return ans;
        string mapping[10] ={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        string p;
        int index=0;
        solve(digits,p,index,ans,mapping);
        return ans;
    }
};