/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* len1n = headA;
        ListNode* len2n = headB;
        int len1=1;
        int len2=1;
                
        while(len1n->next!=NULL)
        {
            len1n=len1n->next;
            len1++;
        }
        while(len2n->next!=NULL)
        {
            len2n=len2n->next;
            len2++;
        }
        len1n = headA;
        len2n = headB;
            
        if(len1>=len2){
            int diff = abs(len1-len2);
            while(diff--)
            {
                len1n = len1n->next;
            }
            
            while(len1n != len2n && len1n!=NULL && len2n!=NULL){
                len1n=len1n->next;
                len2n=len2n->next;
            }
        }
            else{
                int diff = abs(len1-len2);
            while(diff--)
            {
                len2n = len2n->next;
            }
            
            while(len1n != len2n && len1n!=NULL && len2n!=NULL){
                len1n=len1n->next;
                len2n=len2n->next;
            }
            }
            
        
        
       return len1n;
    }
};