//{ Driver Code Starts
//Initial Template for C++

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function Template for C++

class Solution{
	public:
	int MinSquares(int n)
	{
	    vector<int> dp(n+1,INT_MAX);
	    dp[0]=0;
	    for(int i=0;i<=n;i++)
	    {
	        for(int j=1;j*j<=n;j++)
	        {
	            int temp = j*j;
	            if(i-temp>=0)
	            dp[i] = min(dp[i],1+dp[i-temp]);
	            
	        }
	    }
	    return dp[n];
	}
};

//{ Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		Solution ob;
		int ans = ob.MinSquares(n);
		cout << ans <<"\n";
	}
	return 0;
}
// } Driver Code Ends