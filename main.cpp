#include <iostream>

using namespace std;

class binarySearchTree {
private:
    int salary;
    binarySearchTree *left;
    binarySearchTree *right;
public:
    binarySearchTree() {
        return;
    }
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
        if (!this) //when the BST is null
            return;
        if (this->left)
            this->left->inOrder();
        cout << this->salary << " ";
        if (this->right)
            this->right->inOrder();
    }

    void remove(int data) {
        binarySearchTree *b = this;
        binarySearchTree *parent = this;
        while (b) {
            if (data == b->salary) {
                break;
            }
            parent = b;
            if (data < b->salary) {
                b = b->left;
            } else {
                b = b->right;
            }
        }
        if (!b) {
            cout << "\nElement not found.\n";
        } else {
            //case 1: the element has no children
            if (!b->left && !b->right) {
                if (parent->left == b) {
                    delete parent->left;
                    parent->left = NULL;
                } else if (parent->right == b) {
                    delete parent->right;
                    parent->right = NULL;
                }
                    //when parent and b are same
                else {
                    *b = NULL;
                }
            }
                //case 2: the element has only one child
            else if (b->left && !b->right) {
                if (parent->left == b) {
                    parent->left = b->left;
                } else if (parent->right == b) {
                    parent->right = b->left;
                }
                    //when parent and b are same
                else {
                    parent = parent->left;
                }
                delete b;
            } else if (b->right && !b->left) {
                if (parent->left == b) {
                    parent->left = b->right;
                } else if (parent->right == b) {
                    parent->right = b->right;
                } else {
                    parent = parent->right;
                }
                delete b;
            }
                //case 3: the element has two children
            else {
                //find the predecessor of the element and SWAP b's salary with its salary
                b->salary = b->predecessor()->salary;
                b->predecessor()->salary = data;
                //now we need to delete the predecessor
                b->predecessor()->remove(data);
            }
        }
    }

    binarySearchTree *predecessor() {
        binarySearchTree *b = this;
        b = b->left;
        while (b->right) {
            b = b->right;
        }
        return b;
    }
};

int main() {

    /* binarySearchTree b(5);
     b.insert(6);
     b.insert(6);
     b.insert(3);
     b.insert(9);
     cout<<"Inorder Traversal : ";
     b.inOrder();

     b.remove(9);
     cout<<"\nAfter removing 9 : ";
     b.inOrder();

     b.remove(6);
     cout<<"\nAfter removing 6 : ";
     b.inOrder();

     b.remove(5);
     cout<<"\nAfter removing 5 : ";
     b.inOrder();

     binarySearchTree *b_ptr = new binarySearchTree(10);
     b_ptr->insert(b_ptr, 5);
     b_ptr->insert(b_ptr, 15);
     cout << "\nUsing pointer method: ";
     b_ptr->inOrder();
     b_ptr->remove(15);
     cout << "\nAfter deleting 15: ";
     b_ptr->inOrder(); */

    binarySearchTree *c = new binarySearchTree(5);
    c->insert(8);
    c->insert(7);
    c->insert(9);
    c->inOrder();
    cout << endl;
    c->remove(8);
    c->inOrder();
    cout << endl;
    c->remove(7);
    c->inOrder();
    cout << endl;
    /*binarySearchTree* d = &c;
    d = new binarySearchTree(5);
    delete d;
    c.inOrder();*/
    return 0;
}