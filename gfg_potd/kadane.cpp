//{ Driver Code Starts
//Initial Template for C++

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function Template for C++

class Solution{
public:
    bool found(char arr[],char ele,int &ind,int n)
    {
        for(int i=0;i<n;i++)
        {
            if(arr[i]==ele)
            {
                ind = i;
                return true;
            }
        }
        return false;
    }

      string maxSum(string w,char x[], int b[],int n){

          unordered_map<char,int>mp;

          for(int i=0;i<w.size();i++){

              mp[w[i]]=w[i];

          }

         for(int i=0;i<n;i++){

             if(mp.find(x[i]) != mp.end())

                mp[x[i]]=b[i];

         }

         int j=0;

         string temp="";int curr=0;

         string ans="";

         int mxValue=INT_MIN;

         while(j<w.size()){

             curr+=mp[w[j]];

             temp+=w[j];

             if(curr>mxValue){

                 ans=temp;

                 mxValue=curr;

             }

             if(curr<0){

                 curr=0; temp="";

             }

             j++;

         }

         return ans;

      }


};

//{ Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        string w;
        cin>>w;
        int n;
        cin>>n;
        char x[n];
        int b[n];
        for(int i = 0;i<n;i++)
            cin>>x[i];
        for(int i = 0;i<n;i++)
            cin>>b[i];
        Solution ob;
        cout << ob.maxSum(w,x,b,n) << endl;
    }
    return 0; 
}
// } Driver Code Ends