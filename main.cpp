#include <iostream>
#include <fstream>

using namespace std;
struct RB {
    int d; //salary
    char c; //color
    int count = 0; //count
    RB *left;
    RB *right;
    RB *parent;
};

//left Rotation
void lR(struct RB *&root, struct RB *&x) {
    struct RB *y = x->right; // set y
    x->right = y->left; //turn y's left subtree into x's right subtree
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent; //link x's parent to y
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; //put x on y's left
    x->parent = y;
}

//right Rotation
void rR(struct RB *&root, struct RB *&y) {
    struct RB *x = y->left; //set x
    y->left = x->right; //turn x's right subtree into y's left subtree
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent; //link y's parent to x
    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->left)
        y->parent->left = x; //
    else
        y->parent->right = x;
    x->right = y; //put y on x's right
    y->parent = x;
}

void fixDoubleRed(struct RB *&root, struct RB *&z) {
    while (z->parent && z->parent->c == 'r') {
        if (z->parent == z->parent->parent->left) {
            struct RB *y = z->parent->parent->right; //uncle of z
            if (y->c == 'r') {
                //the case when uncle is colored red, simply swap the colors
                z->parent->c = 'b';
                y->c = 'b';
                z->parent->parent->c = 'r';
                z = z->parent->parent; //its parent now might have a double RED problem
            }
                //the case when the uncle is colored black , rotations to be done
            else if (z == z->parent->right) {
                //the case when left rotation is required
                lR(root, z);
            }
            z->parent->c = 'b';
            z->parent->parent->c = 'r';
            rR(root, z->parent->parent);
        } else {
            struct RB *y = z->parent->parent->left; //uncle of z
            if (y->c == 'r') {
                //the case when uncle is colored red, simply swap the colors
                z->parent->c = 'b';
                y->c = 'b';
                z->parent->parent->c = 'r';
                z = z->parent->parent; //its parent now might have a double RED problem
            }
                //the case when the uncle is colored black , rotations to be done
            else if (z == z->parent->left) {
                //the case when left rotation is required
                rR(root, z);
            }
            z->parent->c = 'b';
            z->parent->parent->c = 'r';
            lR(root, z->parent->parent);
        }
    }
    root->c = 'b';
}

void insert(RB *&root, int data) {
    struct RB *z = new RB;
    z->d = data;
    z->c = 'r';
    z->parent = z->right = z->left = NULL;
    z->count = 1;
    struct RB *x = root; //used to traverse to the right position to insert
    struct RB *y = NULL; //to store the parent of node to be inserted (z)
    while (x != NULL && x->d != data) {
        y = x;
        if (data < x->d) {
            x = x->left;
        } else
            x = x->right;
    }
    if (x == NULL) {
        //the case when we need to insert a new node in the tree
        z->parent = y;
        if (y == NULL) {
            root = z;
        } else if (z->d < y->d) { //if z is to be on left of y
            y->left = z;
        } else //if z is to be on right of y
            y->right = z;
        fixDoubleRed(root, z); //since z's parent has double red problem
    } else { //the case when data is already present in the tree
        x->count++;
    }
}

int main() {
    //ifstream fin;
    //fin.open("input.txt");
    //read file and insert n elements into the RB Tree

    RB *rb = NULL;
    insert(rb, 15);
    cout << rb->d;

    //make a menu for user to easily insert/delete elements and make queries


    return 0;
}