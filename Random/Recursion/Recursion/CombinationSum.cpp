// { Driver Code Starts
//Initial template for C++

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
//User function template for C++

class Solution {
  public:
    //Function to return a list of indexes denoting the required 
    //combinations whose sum is equal to given number.
    void generate(int index,vector<int>&a,int target,vector<vector<int>> &ans,vector<int> &ds)
    {
        if(index==a.size())
        {
            if(target==0)
            {
                sort(ds.begin(),ds.end());
                ans.push_back(ds);
            }
            return;
        }
        if(a[index]<=target)
        {
            ds.push_back(a[index]);
            generate(index,a,target-a[index],ans,ds);
            ds.pop_back();
        }
        
        generate(index+1,a,target,ans,ds);
    }
    
    vector<vector<int> > combinationSum(vector<int> &A, int target) {
        // Your code here
        
        unordered_set<int> s(A.begin(), A.end());
        vector<int> arr(s.begin(), s.end());
        sort(arr.begin(), arr.end());
        vector<vector<int>> ans;
        vector<int> ds;
        generate(0,arr,target,ans,ds);
        

        return ans;
    }
};

// { Driver Code Starts.
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> A;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            A.push_back(x);
        }   
        int sum;
        cin>>sum;
        Solution ob;
        vector<vector<int>> result = ob.combinationSum(A, sum);
   		if(result.size()==0){
   			cout<<"Empty";
   		}
        for(int i=0;i<result.size();i++){
            cout<<'(';
            for(int j=0;j<result[i].size();j++){
                cout<<result[i][j];
                if(j<result[i].size()-1)
                    cout<<" ";
            }
            cout<<")";
        }
        cout<<"\n";
    }
}	  // } Driver Code Ends