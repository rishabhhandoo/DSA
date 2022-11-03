
#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> Subsets;

class Solution {
public:
    
   void helper(vector<int>&subset,int i,vector <int>&nums)
    {
        if(i==nums.size())
        {
            Subsets.push_back(subset);
            return;
        }
        
        
        helper(subset,i+1,nums);
        
        subset.push_back(nums[i]);
        helper(subset,i+1,nums);
        subset.pop_back();
        
    }
    vector<vector<int>> subsets(vector<int>& nums) 
    {
        vector <int>subset;
        helper(subset,0,nums);
        return Subsets;
    }
};

int main()
{
    Solution sol;
    vector<int>nums={1,2,3};
    sol.subsets(nums);
    for(auto val:Subsets)
    {
        for(auto el:val)
        {
            cout<<el<<" ";
        }
        cout<<endl;
    }

    return 0;
}
