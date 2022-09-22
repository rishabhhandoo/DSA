//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    vector<int> max_of_subarrays(vector<int> arr, int n, int k) {
        deque<int> q;
        
        q.push_back(arr[0]);
        vector<int> ans;
        if(k==1)    ans.push_back(q.front());
        
        for(int i=1;i<n;i++)
        {
            if(i<k)
            {
                if(!q.empty() && q.back()>arr[i])
                {
                    q.push_back(arr[i]);
                }else if(!q.empty() && q.back()<arr[i])
                {
                    while(!q.empty() && q.back()<arr[i])
                    {
                        q.pop_back();
                    }
                    q.push_back(arr[i]);
                }
                
                    
                    
                if(i==k-1)
                {
                    ans.push_back(q.front());
                }
            }else{
            if(arr[i-k]==q.front())
            {
                q.pop_front();
            }
            if(q.empty())
            {
                q.push_back(arr[i]);
            }else if(!q.empty() && q.back()>arr[i])
            {
                q.push_back(arr[i]);
            } else if(!q.empty() && q.back()<arr[i])
                {
                    while(!q.empty() && q.back()<arr[i])
                    {
                        q.pop_back();
                    }
                    q.push_back(arr[i]);
                }
            
            ans.push_back(q.front());
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

        int n, k;
        cin >> n >> k;

        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];
        Solution ob;
        vector<int> res = ob.max_of_subarrays(arr, n, k);
        for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
        cout << endl;
    }

    return 0;
}
// } Driver Code Ends