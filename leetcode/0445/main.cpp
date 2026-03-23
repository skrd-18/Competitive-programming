#include <iostream>
#include <stack>
#include <vector>

using namespace std;

//  Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    void printStack(stack<int> s)
    {
        // Note: Passed by value to create a copy
        while (!s.empty())
        {
            std::cout << s.top() << " ";
            s.pop();
        }
        std::cout << std::endl;
    }

public:
    ListNode *buildLinkedList(vector<int> &nums)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *tail = dummyHead;

        for (int num : nums)
        {
            tail->next = new ListNode(num);
            tail = tail->next;
        }
        ListNode *result = dummyHead->next;
        delete dummyHead;
        return result;
    }

public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        stack<int> s1;
        stack<int> s2;

        while (l1 != nullptr)
        {
            s1.push(l1->val);
            l1 = l1->next;
        }

        while (l2 != nullptr)
        {
            s2.push(l2->val);
            l2 = l2->next;
        }

        printStack(s1);

        // Use a stack; Last In First Out
        ListNode *head = nullptr;
        int carry = 0;

        while (!s1.empty() || !s2.empty() || carry != 0)
        {
            int digit1 = 0, digit2 = 0;
            if (!s1.empty())
            {
                digit1 = s1.top();
                s1.pop();
            }
            else
            {
                digit1 = 0;
            }

            if (!s2.empty())
            {
                digit2 = s2.top();
                s2.pop();
            }
            else
            {
                digit2 = 0;
            }

            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10; // Integer division

            // Create the newNode;
            ListNode *newNode = new ListNode(digit);
            newNode->next = head;
            head = newNode;
        }
        return head;
    }
    void printLinkedList(ListNode *head)
    {
        ListNode *current = head;
        while (current != nullptr)
        {
            cout << current->val;
            if (current->next != nullptr)
            {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }
};
int main(int argc, char const *argv[])
{
    Solution sol;
    vector<int> numbers1 = {7, 2, 4, 3};
    vector<int> numbers2 = {5, 6, 4};
    sol.printLinkedList(sol.addTwoNumbers(sol.buildLinkedList(numbers1), sol.buildLinkedList(numbers2)));
    return 0;
}
