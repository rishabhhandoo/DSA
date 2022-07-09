#include<bits/stdc++.h>
using namespace std;

class Node{
    public:

    int data;
    Node* next;

    Node(int data=0)
    {
        this->data = data;
        this->next = NULL;
    }
};
 
 
Node* updateList(Node* &head,int k){
    Node * newHead;
    Node* newTail;
    Node* tail=head;
    Node* temp=head;
    int count=1;
    while(temp->next !=NULL)
    {
        count++;
        temp=temp->next;
    }
    cout<<" "<<count<<" "<<endl;

    int l=1;

    while(tail->next != NULL)
    {
        l++;
        tail=tail->next;
        if(l == count-k){
            newTail=tail;
        }
        if(l==count-k+1){
            newHead = tail;
        }
    }

    newTail->next=NULL;
    tail->next=head;
    return newHead;
}

void printList(Node* node)
{
    while (node != NULL) {
        cout << (node->data) << " -> ";
        node = node->next;
    }
    cout << "NULL";
}
 
int main()
{
 
    // Create the list  
    Node* head = new Node(4);
    head->next = new Node(5);
    head->next->next = new Node(6);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(2);
    head->next->next->next->next->next = new Node(3);
    int m = 3;
    // printList(head);
    Node* newHead = updateList(head, m);
    printList(newHead);

    return 0;
}