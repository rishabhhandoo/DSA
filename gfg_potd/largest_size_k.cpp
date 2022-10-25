//{ Driver Code Starts
//Initial template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function template for C++

class Solution
{
  public:
    //Function to find maximum of each subarray of size k.
    vector <int> max_of_subarrays(int *arr, int n, int k)
    {
        vector<int> ans;
        multiset<int> s;
        
        int rem=0;
        int i=0;
        
        while(i<k)
        {
            s.insert(arr[i]);
            i++;
        }
        ans.push_back(*s.rbegin());
        // cout<<"what is the rbegin significance ->"<<*s.rbegin()<<" "<<*s.end()<<endl;
        while(i<n)
        {
            // cout<<"what is the rbegin significance ->"<<*s.rbegin()<<" "<<*s.end()<<endl;
        
            s.erase(s.find(arr[rem]));
            s.insert(arr[i]);
            rem++;
            i++;
            ans.push_back(*s.rbegin());
        }
        return ans;
    }
};

//{ Driver Code Starts.

int main() {
	
	int t;
	cin >> t;
	
	while(t--){
	    
	    int n, k;
	    cin >> n >> k;
	    
	    int arr[n];
	    for(int i = 0;i<n;i++) 
	        cin >> arr[i];
	    Solution ob;
	    vector <int> res = ob.max_of_subarrays(arr, n, k);
	    for (int i = 0; i < res.size (); i++) 
	        cout << res[i] << " ";
	    cout << endl;
	    
	}
	
	return 0;
}
// } Driver Code Ends