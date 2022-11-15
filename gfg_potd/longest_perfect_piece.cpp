//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
    int longestPerfectPiece(int a[], int N) {
        map<int,int> m;
        int ans=0;
        
        int lo=0;
        for(int i=0;i<N;i++)
        {
            m[a[i]]++;
                while((--m.end())->first - m.begin()->first > 1)
                {
                    m[a[lo]]--;
                    if(m[a[lo]]==0){
                        m.erase(a[lo]);
                        
                    }
                    lo++;
                }
            
            ans = max(ans,i-lo+1);
            
            
        }
        
        return ans;
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;
        
        cin>>N;
        int arr[N];
        for(int i=0; i<N; i++)
            cin>>arr[i];

        Solution ob;
        cout << ob.longestPerfectPiece(arr,N) << endl;
    }
    return 0;
}
// } Driver Code Ends