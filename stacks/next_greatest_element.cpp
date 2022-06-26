class Solution
{
    public:
    //Function to find the next greater element for each element of the array.
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        // Your code here
        vector<long long> nge(n);
        stack<long long> s;
        for(int i=0;i<n;i++)
        {
            while((!s.empty()) && arr[i]>arr[s.top()])
            {
                nge[s.top()]=arr[i];
                s.pop();
            }   s.push(i);
        }
        while(!s.empty()){
            nge[s.top()]=-1;
            s.pop();
        }
        return nge;
    }
};
