#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    
   
    int kthGrammar(int n, int k) 
    {
        if(n==1 && k==1) return 0;
        int mid=pow(2,n-1)/2;
        if(k>mid) return 1-kthGrammar(n-1,k-mid);
        return kthGrammar(n-1,k);
    }
};

int main()
{
    Solution sol;
    int res=sol.kthGrammar(4,3);
    cout<<res;

    return 0;
}
