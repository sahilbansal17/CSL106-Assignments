#include <iostream>

using namespace std;

class binarySearchTree {
private:
    int salary;
    binarySearchTree *left;
    binarySearchTree *right;
public:
    binarySearchTree(int data) {
        salary = data;
        left = NULL;
        right = NULL;
    }

    void insert(int data) {
        binarySearchTree *b = this;
        while (b) {
            if (data <= b->salary) {
                if (b->left)
                    b = b->left;
                else {
                    b->left = new binarySearchTree(data);
                    break;
                }
            } else {
                if (b->right)
                    b = b->right;
                else {
                    b->right = new binarySearchTree(data);
                    break;
                }
            }
        }
    }

    binarySearchTree *insert(binarySearchTree *b, int data) {
        if (!b) {
            b = new binarySearchTree(data);
            return b;
        }
        if (data <= b->salary) {
            b->left = insert(b->left, data);
        } else {
            b->right = insert(b->right, data);
        }
        return b;
    }

    void inOrder() {
        if (this->left)
            this->left->inOrder();
        cout << this->salary << " ";
        if (this->right)
            this->right->inOrder();
    }
};

int main() {

    binarySearchTree b(5);
    b.insert(6);
    b.insert(6);
    b.insert(3);
    b.insert(9);
    b.inOrder();

    binarySearchTree *b_ptr = new binarySearchTree(10);
    b_ptr->insert(b_ptr, 5);
    b_ptr->insert(b_ptr, 15);
    cout << "\nUsing pointer method: ";
    b_ptr->inOrder();
    return 0;
}