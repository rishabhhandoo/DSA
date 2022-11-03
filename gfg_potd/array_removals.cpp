//{ Driver Code Starts
//Initial Template for C++

#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

class Solution{
    public:
    int dp[105][105];
    int helper(int strt , int end , vector<int>& arr ,int k)
    {
        if(strt>end){
            return 1000000;
        }
        if(arr[end]-arr[strt]<=k)   return 0;
        if(dp[strt][end]!=-1)   return dp[strt][end];
        
        int first = 1+helper(strt+1,end,arr,k);
        int last = 1+helper(strt,end-1,arr,k);
        
        return dp[strt][end]= min(first,last);
    }
    
    int removals(vector<int>& arr, int k){
        memset(dp,-1,sizeof(dp));
        int n = arr.size();
        sort(arr.begin(),arr.end());
        return helper(0,n-1,arr,k);
    }
};


//{ Driver Code Starts.


int main(){
    int t;
    cin>>t;
    
    while(t--){
        int n,k;
        cin>>n>>k;
        vector<int> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        
        Solution ob;
        int ans = ob.removals(arr,k);
        
        cout<<ans<<endl;
    }
}



// } Driver Code Ends