//{ Driver Code Starts
//Initial template for C++
 
#include<bits/stdc++.h>
using namespace std; 

// } Driver Code Ends
//User function template for C++

class Solution{
public:
    int minLength(string str, int n) {
        stack<int> s;
        vector<int> comp = {9,2,1,4,3,6,5,8,7,0};
        for(int i=0;i<n;i++)
        {
            if(s.empty())   s.push(str[i]-'0');
            else if(s.top() == comp[str[i] - '0'])
            {
                s.pop();
            }else{
                s.push(str[i]-'0');
            }
            
        }
        return s.size();
    } 
};


//{ Driver Code Starts.

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        string s;
        cin >> s;

        Solution obj;
        cout << obj.minLength(s, n) << "\n";
    }
    return 0;
}
// } Driver Code Ends