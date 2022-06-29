// { Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
// User function template for C++

class Solution{
    public:
    bool  isSafe(int x,int y,vector<vector<int>> visited,vector<vector<int>> m,int n){
        if((x>=0 && x<n) && (y>=0 && y<n) && visited[x][y]==0 && m[x][y]==1)
        {
            return true;
        }else{
            return false;
        }
    }
    
    void solve(int row,int col,string output,vector<vector<int>> visited , vector<string> &ans,int n,vector<vector<int>> m){
        if(row == n-1 && col == n-1){
            ans.push_back(output);
            return ;
        }
        
        visited[row][col]=1;
        
        //down
        int newx=row+1;
        int newy=col;
        if (isSafe(newx,newy,visited,m,n)){
            output.push_back('D');
            solve(newx,newy,output,visited,ans,n,m);
            output.pop_back();
        }
        
        //left
        newx=row;
        newy=col-1;
        if (isSafe(newx,newy,visited,m,n)){
            output.push_back('L');
            solve(newx,newy,output,visited,ans,n,m);
            output.pop_back();
        }
        
        //right
        newx=row;
        newy=col+1;
        if (isSafe(newx,newy,visited,m,n)){
            output.push_back('R');
            solve(newx,newy,output,visited,ans,n,m);
            output.pop_back();
        }
        
        
        //up
        newx=row-1;
        newy=col;
        if (isSafe(newx,newy,visited,m,n)){
            output.push_back('U');
            solve(newx,newy,output,visited,ans,n,m);
            output.pop_back();
        }
       
        visited[row][col]=0;
       
    }
    
    vector<string> findPath(vector<vector<int>> &m, int n) {
        // Your code goes here
        vector<string> ans;
        
        if(m[0][0] == 0) return ans;
        
        vector<vector<int>> visited;
        int row=0;
        int col=0;
        string output="";
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
            {
                visited[i][j]=0;
            }
        }
        
        
        solve(row,col,output,visited,ans,n,m);
        //answer is to be lexiographically sorted
        sort(ans.begin(),ans.end());
        
        
        
        return ans;
        
    }
};

    


// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> m(n, vector<int> (n,0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> m[i][j];
            }
        }
        Solution obj;
        vector<string> result = obj.findPath(m, n);
        sort(result.begin(), result.end());
        if (result.size() == 0)
            cout << -1;
        else
            for (int i = 0; i < result.size(); i++) cout << result[i] << " ";
        cout << endl;
    }
    return 0;
}  // } Driver Code Ends