//{ Driver Code Starts
/* Driver program to test above function */

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//Back-end complete function Template for C++
//Back-end complete function Template for C++
class Solution
{
   public:
    string ReFormatString(string s, int k){
    	
    	string ans="";
    	int n=0;
    	string temp="";
    	for(int i=0;i<s.size();i++)
    	{
    	    if(s[i]!='-')
    	    {
                temp+=toupper(s[i]);
    	        n++;
    	    }
    	}
    	int sf = n%k;
    	if(sf==0)   sf=k;
    	for(int i=0;i<temp.size();i++)
    	{
    	    if(i<sf)
    	    {
    	        ans+=temp[i];
    	    }
	        else if(i==sf)
    	    {
    	       // cout<<"1"<<endl;
    	        ans+='-';
    	        ans+=temp[i];
    	        if(k==1 &&i!=temp.size()-1)    ans+='-';
    	    }else if( (i-sf+1 )%k!=0)
    	    {
    	        ans+=temp[i];
    	    }else {
    	       //  cout<<"2"<<endl;
    	        ans+=temp[i];
    	        if(i!=temp.size()-1)
    	            ans+='-';
    	    }
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
	    string S;
	    cin>>S;
	    int K;
	    cin >> K;
	    Solution ob;  
	    string ans=ob.ReFormatString(S, K);
	    cout<<ans;
	    cout<<"\n";
	}
	return 0;
}

// } Driver Code Ends