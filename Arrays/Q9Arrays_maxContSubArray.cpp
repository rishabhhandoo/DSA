class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum=nums[0];
        int sum=nums[0];
        
        
        for(int i=1;i<nums.size();i++)
        {
            if(sum<0)   sum=0;
            sum+=nums[i];
            if(sum>maxSum) maxSum=sum;
        }
        return maxSum;
        
    }
};