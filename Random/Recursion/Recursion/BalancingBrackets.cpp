#include <bits/stdc++.h>
using namespace std;

vector<string>valid;
void generate(string &s,int open,int close)//passing &s so that time is not wasted in creating a copy i.e. O(n)
{
    
    if(open==0 && close==0)
    {
        valid.push_back(s);
        return;
    }
   if(open>0) {
       s.push_back('(');
       generate(s,open-1,close);
       s.pop_back();
   }
   if(close>0 )
   {
       if(open<close) //it means we have more open brackets in the og string 
       {
           s.push_back(')');
           generate(s,open,close-1);
           s.pop_back();
       }
   }
}

int main()
{
    string s;
    generate(s,2,2);
    for(string val:valid)
    {
        cout<<val<<endl;
    }

    return 0;
}