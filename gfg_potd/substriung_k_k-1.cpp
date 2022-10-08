//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

class Solution {
  public:
    int countOfSubstrings(string S, int k) {
        
        unordered_map <char,int>umap;
        int ndist=0;
        int ans=0;
        for(int i=0;i<S.size();i++)
        {
            umap[S[i]]++;
            if(i>=k-1)       
            {
                if(umap.size()==k-1)    ans++;
                umap[S[i-k+1]]--;
                if(umap[S[i-k+1]]==0)
                {
                    umap.erase(S[i-k+1]);
                }
            }
        }
        return ans;
        
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        string S;
        int K;
        cin>>S;
        cin>>K;

        Solution ob;
        cout << ob.countOfSubstrings(S,K) << endl;
    }
    return 0;
}
// } Driver Code Ends