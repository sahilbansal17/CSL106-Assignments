#include <iostream>

using namespace std;

class binarySearchTree {
private:
    int salary;
    binarySearchTree *left;
    binarySearchTree *right;
public:
    binarySearchTree() {
        salary = -1;
        left = NULL;
        right = NULL;
        return;
    }

    binarySearchTree(int data) {
        salary = data;
        left = NULL;
        right = NULL;
    }

    void insert(int data) {
        binarySearchTree *b = this;
        if (b ==
            NULL) { //there's some mistake here since this can never be null, that's why unable to insert the first element
            b = new binarySearchTree(data);
        } else
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

    //still some bugs to be fixed in this
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

    binarySearchTree *remove(binarySearchTree *b, int data) {
        binarySearchTree *temp;
        if (b == NULL) {
            cout << "Element not present in the BST\n";
        } else if (data < b->salary) {
            b->left = remove(b->left, data);
        } else if (data > b->salary) {
            b->right = remove(b->right, data);
        } else {
            //the case when element is found
            //case 1: it has two children
            if (b->left && b->right) {
                //swap the element with the predecessor
                temp = b->predecessor();
                b->salary = temp->salary;
                //now delete the predecessor
                b->left = remove(b->left, b->salary);
            } else {
                //case 2: it has one child or even no child
                temp = b;
                if (b->left == NULL) {
                    b = b->right;
                } else if (b->right == NULL) {
                    b = b->left;
                }
                delete temp; //handles both cases
            }
        }
        return b;
    }

};

void insertUsingArr(binarySearchTree *&b, int a[], int start, int end) {
    if (start > end)
        return;
    int mid = (start + end) / 2;
    b = b->insert(b, a[mid]);
    insertUsingArr(b, a, start, mid - 1);
    insertUsingArr(b, a, mid + 1, end);
}

int main() {

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(a) / sizeof(int);
    binarySearchTree *bst = NULL; // to make sure it is not uninitialized
    insertUsingArr(bst, a, 0, n - 1);
    bst->inOrder();
    bst = bst->remove(bst, 5);
    cout << endl;
    bst->inOrder();
    bst = bst->remove(bst, 3);
    cout << endl;
    bst->inOrder();
    bst = bst->remove(bst, 2);
    cout << endl;
    bst->inOrder();

    return 0;
}