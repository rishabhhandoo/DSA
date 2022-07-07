// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;



 // } Driver Code Ends

class Solution{
  public:
    vector <int> countDistinct (int A[], int n, int k)
    {
        vector<int> ans;
        
        unordered_map<int,int> umap;
        
        for(int i=0;i<k;i++)
        {
            umap[A[i]]++;
        }
        
        ans.push_back(umap.size());
        
        for(int i=k;i<n;i++)
        {
            if(umap[A[i - k]] == 1) umap.erase(A[i-k]);
            else umap[A[i - k]] --;
            umap[A[i]]++;
            ans.push_back(umap.size());
        }
        return ans;
        
    }
    
    
};

// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int n, k;
        cin >> n >> k;
        int a[n];
        for (int i = 0; i < n; i++) 
        	cin >> a[i];
        Solution obj;
        vector <int> result = obj.countDistinct(a, n, k);
        for (int i : result) 
        	cout << i << " ";
        cout << endl;
    }
    return 0;
}  // } Driver Code Ends