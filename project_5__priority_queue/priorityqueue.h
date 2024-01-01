// priorityqueue.h
//
// Author: David Miszczyk, UIN 661517423, UIC Spring 2021
#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
 private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    // Used for toString
    void inOrder(NODE* root, ostream& output) {
        NODE* cur = root;   // used to traverse

        if (cur == nullptr)
            return;

        inOrder(cur->left, output);

        output << cur->priority << " value: " << cur->value << endl;

        if (cur->dup) {
            NODE* front = cur;
            while (front != nullptr) {
                front = front->link;
                // we dont want to print the front node twice
                if (front != nullptr) {
                    output << front->priority << " value: " << front->value <<
                    endl;
                }
            }
        }

        inOrder(cur->right, output);
    }

    // Recursive helper function for clear
    void deleteTree(NODE* root) {
        if (root == nullptr)
            return;

        if (root != nullptr) {
            deleteTree(root->left);

            deleteTree(root->link);

            deleteTree(root->right);

            size--;

            delete root;
        }
    }

    // Used to check each node for equality of tree's
    bool equal(NODE* cur, NODE* other) const{
        if (cur == nullptr && other == nullptr) // base case for recursion
            return true;

        else if (cur == nullptr)
            return false;

        else if (other == nullptr)
            return false;
        else {
            if (cur->dup && other->dup) {
                if (!identical(cur, other))
                    return false;
            }

            if (equal(cur->left, other->left) && (cur->value == other->value) 
            && (identical(cur, other)) && (cur->priority == other->priority) 
            && (equal(cur->right, other->right))) {
                return true;
            }
            else
                return false;
        }
    }
    // Check's if two lists are identical
    bool identical(NODE* cur, NODE* other) const {
        if (cur->dup != other->dup)
            return false;

        while (cur != nullptr && other != nullptr) {
            if (cur->value != other->value)
                return false;

            cur = cur->link;

            other = other->link;
        }
        return (cur == nullptr && other == nullptr);
    }

    // Used for the copy operator
    void preOrder(NODE* otherNode){
        if (otherNode == nullptr)
            return;
        enqueue(otherNode->value, otherNode->priority);
        if (otherNode->dup)
            preOrder(otherNode->link);
        preOrder(otherNode->left);
        preOrder(otherNode->right);
    }
    // Used to search for the first Inorder node
    void search(int priority) {
        NODE* temp = root;
        while (temp->priority != priority) {
            if (temp->priority > curr->priority) {
                temp = temp->left;
            }

            else if (temp->priority < curr->priority) {
                temp = temp->right;
            }
        }
        curr = temp;
    }

    // Helper function for dq
    NODE* findMinNode(NODE* cur) {
        if (cur == nullptr)
            return nullptr;
        // iterate to the lowest priority
        while (cur->left != nullptr) {
            cur = cur->left;
        }

        // cout << "find min" << cur->value << cur->priority << endl;

        return cur;
    }
    // Helper function for next, returns maximum priority
    int findMax() {
        NODE* max = root;
        while (max->right != nullptr) {
            max = max->right;
        }
        return max->priority;
    }

 public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        if (this == &other)
            return *this;

        if (this != &other) {
            clear();

            preOrder(other.root);
        }
        size = other.size;

        return *this;
    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        deleteTree(root);
        root = nullptr;
        curr = nullptr;
    }
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        clear();
    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* newNode = new NODE();
        size++;
        newNode->value = value;     // intialize all fields
        newNode->priority = priority;
        newNode->dup = false;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;
        newNode->link = nullptr;

        NODE* prev = nullptr;
        NODE* cur = root;

        if (cur == nullptr) {
            root = newNode;
        }

        while (cur != nullptr) {
            if (newNode->priority == cur->priority) {
                newNode->dup = true;
                cur->dup = true;
                prev = cur;
                break;
            }

            else if (newNode->priority < cur->priority) {
                prev = cur;
                cur = cur->left;
            }

            else {
                prev = cur;
                cur = cur->right;
            }
        }

        newNode->parent = prev;

         if (newNode->dup) {
            // I have to built a list
            while (cur != nullptr) {
                prev = cur;

                cur = cur->link;
            }
            prev->link = newNode;

            newNode->parent = prev;
        }

        else {
            if (prev == nullptr) {
                root = newNode;
            }

            else if (newNode->priority < prev->priority) {
                prev->left = newNode;
                // newNode->parent = prev;
            }

            else {
                prev->right = newNode;
                // newNode->parent = prev;
            }
        }
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    // I need to fix the valgrind error.
    T dequeue() {
        T valueOut;
        if (size == 0)
            return valueOut;

        NODE* cur = root;

        if (size == 1) {
            valueOut = cur->value;
            // cout << valueOut << cur->priority << endl;
            clear();
            return valueOut;
        }
        // the minimum lies in the left subtree
        if (cur->left != nullptr) {
            NODE* min = nullptr;
            min = findMinNode(cur);

            if (min->dup) {
                if (!min->link->link) {
                    min->link->dup = false;
                }
                if (min->right) {
                    min->right->parent = min->link;
                    min->link->right = min->right;
                }
                min->parent->left = min->link;
                
                min->link->parent = min->parent;
                
                valueOut = min->value;
                // cout << valueOut << min->priority << endl;
                delete min;
                size--;
                return valueOut;
            }

            if (min->right) {
                min->right->parent = min->parent;
                min->parent->left = min->right;
            }

            else {
                min->parent->left = nullptr;
            }

            valueOut = min->value;

            // cout << min->value << min->priority << endl;

            delete min;
            size--;
            return valueOut;
        }
        // minimum lies in the root
        if (cur->left == nullptr) {
            NODE* min = root;
            // duplicate handling
            if (min->dup) {
                // end of the list
                if (!min->link->link) {
                    min->link->dup = false;
                    min->link->parent = nullptr;
                }
                if (min->right) {
                    min->link->right = min->right;
                    min->right->parent = min->link;
                }

                valueOut = min->value;
                root = min->link; 

                // cout << min->value << min->priority << endl;

                delete min;
                size--;
                return valueOut;
            }

            valueOut = min->value;
            min->right->parent = nullptr;
            root = min->right;

            // cout << min->value << min->priority << endl;

            delete min;
            size--;
            return valueOut;
        }

        return valueOut;
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;
    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        // Empty tree case
        if (root == nullptr)
            return;
        // Nonempty tree
        curr = root;
        // If there is no left child, then in order starts at the root.
        if (curr->left == nullptr) {
            // cout << "begin " << curr->value << curr->priority << endl;
            return;
        }
        // Otherwise, Inorder start's at the lowest priority.
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        // cout << "begin " << curr->value << curr->priority << endl;
    }
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
       if (curr == nullptr)
            return false;

        value = curr->value;
        priority = curr->priority;
        // Remove before submission
        // cout << value << priority << endl;

        if (curr->dup) {
            if (curr->link) {
                curr = curr->link;
                // Remove for submission
                // cout << curr->value << curr->priority << endl;
                return true;
            }
            else {
                // cout << "curr link is null" << endl;
                search(curr->priority);
                // if the node is the max node then don't let it get out.
                if (curr->priority == findMax()) {
                    // cout << "max node reached end" << endl;
                    curr = nullptr;
                    return false;
                }
            }
        }
        // Remove the print before submission
        // cout << curr->value << curr->priority << endl;
        // find the minimum in the right subtree
        if (curr->right != nullptr) {
            curr = curr->right;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            return true;
        }

        else {
            // if the node is the max node then don't let it get out.
            if (curr->priority == findMax()) {
                curr = nullptr;
                return false;
            }

            while (curr != curr->parent->left) {
                curr = curr->parent;
                if (curr->parent == nullptr)
                    return false;
            }
            if (curr->parent == nullptr) {
                return false;
            }
            curr = curr->parent;
            return true;

        }
        return true;
    }

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    string toString() {
        string str = "";

        NODE* cur = root;

        if (cur == nullptr)
            return str;

        stringstream ss;

        inOrder(cur, ss);   // helper function that stores to ss

        str = ss.str();

        // cout << str;    // I need to get rid of this before submitting

        return str;
    }
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
        NODE* min = root;
        min = findMinNode(min);
        T valueOut;
        valueOut = min->value;
        return valueOut;
    }
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        if (this == &other)
            return true;

        return equal(root, other.root);
    }
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
