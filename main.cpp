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

class RBTree {
public:
    int salary;
    RBTree *left;
    RBTree *right;
    RBTree *parent;
    int color; //0 for BLACK and 1 for RED
public:
    RBTree() {
        salary = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = 0;
    }

    RBTree(int data, int col) {
        //by default when we insert a node its color is RED
        salary = data;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = col;
    }

    RBTree *insert(RBTree *rb, int data) {
        if (!rb) {
            rb = new RBTree(data, 1);
            /*now it might create a double RED problem if its
              parent is RED  */
            return rb;

        }
        if (data <= rb->salary) {
            //no new node is created
            if (rb->left || rb->color == 0) {
                rb->left = insert(rb->left, data);
                rb->left->parent = rb;
            } else if (rb->color == 1) {
                //the case when a double RED problem occurs
                rb->left = insert(rb->left, data);
                rb->left->parent = rb;

                //parent of rb must be BLACK
                RBTree *otherChild; //otherChild of parent of rb
                if (rb->parent->left == rb)
                    otherChild = rb->parent->right;
                else
                    otherChild = rb->parent->left;
                fixDRed(rb, rb->parent, otherChild, 1);
                //1 refers that new element is inserted at left of rb
            }
        } else {
            if (rb->right || rb->color == 0) {
                rb->right = insert(rb->right, data);
                rb->right->parent = rb;
            } else if (rb->color == 1) {
                rb->right = insert(rb->right, data);
                rb->right->parent = rb;
                RBTree *otherChild;
                if (rb->parent->left == rb)
                    otherChild = rb->parent->right;
                else
                    otherChild = rb->parent->left;
                fixDRed(rb, rb->parent, otherChild, 2);
                //2 refers that new element is inserted at right of rb
            }
        }
        return rb;
    }

    void fixDRed(RBTree *rb, RBTree *par, RBTree *otherChild, int val) {
        //case 1: the other child of parent is RED

        if (otherChild && otherChild->color == 1) {
            //we just need to recolor rb,parent,otherChild
            rb->color = 0;
            rb->parent->color = 1;
            otherChild->color = 0;
            //we might now as well need to check for problem at parent
            if (par->parent) {
                if (par->parent->color == 1) {
                    if (par->parent->left == par)
                        fixDRed(par, par->parent, par->parent->right, val);
                    else
                        fixDRed(par, par->parent, par->parent->left, val);
                }
            } else {
                par->color = 0;
            }
        }
            //case 2: the other child of grandparent is BLACK
        else {
            //four cases possible

            //case 1: left left case
            if (par->left == rb && val == 1)
                par = rotateRight(par, rb);

                //case 2: right right case
            else if (par->right == rb && val == 2)
                par = rotateLeft(par, rb);

                //case 3: left right case
            else if (par->left == rb && val == 2) {
                rb = rotateLeft(rb, rb->right);
                par = rotateRight(par, rb);
            }

                //case 4: right left case
            else {
                rb = rotateRight(rb, rb->left);

                cout << par->right->salary << par->right->right->salary;
                par = rotateLeft(par, rb);
            }

            //common for all, swapping colors of rb and par
            par->color = !par->color;
            rb->color = !rb->color;

        }
    }

    RBTree *rotateRight(RBTree *par, RBTree *child) {
        par->left = child->right;
        if (par->left)
            par->left->parent = par;
        child->right = par;
        par->parent = child;
        return child;
    }

    RBTree *rotateLeft(RBTree *par, RBTree *child) {
        par->right = child->left;
        if (par->right)
            par->right->parent = par;
        child->left = par;
        par->parent = child;
        return child;
    }

    void inOrder(RBTree *rb) {
        if (!rb)
            return;
        inOrder(rb->left);
        cout << rb->salary << " ";
        inOrder(rb->right);
    }
};

int main() {

    /*int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
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
    bst->inOrder();*/

    RBTree *very_first_rb = new RBTree(5, 0);
    very_first_rb = very_first_rb->insert(very_first_rb, 6);
    very_first_rb = very_first_rb->insert(very_first_rb, 4);
    very_first_rb = very_first_rb->insert(very_first_rb, 3);
    very_first_rb = very_first_rb->insert(very_first_rb, 10);
    very_first_rb = very_first_rb->insert(very_first_rb, 7);
    very_first_rb->inOrder(very_first_rb);

    return 0;
}