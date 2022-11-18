//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
    int noOfOpenDoors(long long N) {
        int ans =1;
        return sqrt(N);
        //base case is one is always open
        // for(long long i=2;i<=sqrt(N);i++)
        // {
        //     // cout<<i<<endl;
        //     // long long num1 = sqrt(i);
            
        //     // if(num1*num1==i)
        //     // {
        //     //     ans++;
        //     // }
        //     if(i*i <= N)    ans++;
        // }
        // return ans;
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long N;
        
        cin>>N;

        Solution ob;
        cout << ob.noOfOpenDoors(N) << endl;
    }
    return 0;
}
// } Driver Code Ends