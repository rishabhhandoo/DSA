//{ Driver Code Starts
#include<bits/stdc++.h> 
using namespace std; 

// } Driver Code Ends
class Solution{   
public:
        int swapBitGame(long long N){
      // check the number of one  in binary form  and if they are odd player 1 win or else 2 wins according to the test cases
         long long x=N;
         long long cnt=0;
         while(x)
         {
             ++cnt;
             x=x&(x-1);
         }

         return cnt%2==1?1:2;
    }

};

//{ Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        long long N;
        cin >> N;
        Solution ob;
        cout << ob.swapBitGame(N) << endl;
    }
    return 0; 
} 
// } Driver Code Ends