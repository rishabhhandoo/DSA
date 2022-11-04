//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
class Solution {
  public:
    string baseEquiv(int n, int m){
        int l = 2;
        int r = 32;
        
        while(l<=r)
        {
            int mid = l+(r-l)/2;
            // cout<<"mid: "<<mid<<endl;
            int value = floor(log(n)/log(mid));
            // cout<<"value :"<<value<<endl;
            if( value + 1 == m )
            {
                return "Yes";
            }else if(value + 1<m)
            {
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return "No";
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        Solution ob;
        cout<<ob.baseEquiv(n,m)<<endl;
    }
    return 0;
}

// } Driver Code Ends