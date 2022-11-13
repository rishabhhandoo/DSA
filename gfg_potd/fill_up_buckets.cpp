//{ Driver Code Starts
//Initial Template for C++

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function Template for C++
#define mod 1000000007

class Solution{
public:
    int totalWays(int n, vector<int>capacity) {
        
        sort(capacity.begin(),capacity.end());
    
        
        long long int ans=1;
        
        for(int i=0;i<n;i++)
        {
            // cout<<capacity[i]<<" "<<i+1<<endl;
            // if(capacity[i]-dec>0)
            ans = ((ans%mod) * (capacity[i]-(i))%mod)%mod;
            
            // if(ans == 0)     cout<<capacity[i]<<" "<<i+1<<endl;
        }
        return ans%1000000007;
    }
};

//{ Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		vector<int>capacity(n);
		for(int i = 0; i < n; i++)
			cin >> capacity[i];
		Solution ob;
		int ans = ob.totalWays(n, capacity);
		cout << ans << "\n";
	}  
	return 0;
}
// } Driver Code Ends