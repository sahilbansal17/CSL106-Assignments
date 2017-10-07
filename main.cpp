#include <iostream>
#include <fstream>
#include <queue>

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
RB* lR(struct RB *root, struct RB *x) {
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
    return root;
}

//right Rotation
RB* rR(struct RB *root, struct RB *y) {
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
    return root ;
}

RB* fixDoubleRed(struct RB *root, struct RB *z) {
    while (z->parent && z->parent->c == 'r') {
        if (z->parent == z->parent->parent->left) {
            struct RB *y = z->parent->parent->right; //uncle of z
            if (y && y->c == 'r') {
                //the case when uncle is colored red, simply swap the colors
                z->parent->c = 'b';
                y->c = 'b';
                z->parent->parent->c = 'r';
                z = z->parent->parent; //its parent now might have a double RED problem
            }
                //the case when the uncle is colored black , rotations to be done
            else if (z == z->parent->right) {
                //the case when left rotation is required
                root = lR(root, z);
            }
            if (z->parent) {
                z->parent->c = 'b';
                if (z->parent->parent) {
                    z->parent->parent->c = 'r';
                    root = rR(root, z->parent->parent);
                }
            }
        } else {
            if (z->parent->parent) {
                struct RB *y = z->parent->parent->left; //uncle of z
                if (y && y->c == 'r') {
                    //the case when uncle is colored red, simply swap the colors
                    z->parent->c = 'b';
                    y->c = 'b';
                    z->parent->parent->c = 'r';
                    z = z->parent->parent; //its parent now might have a double RED problem
                }
            }
                //the case when the uncle is colored black , rotations to be done
            else if (z == z->parent->left) {
                //the case when left rotation is required
                root = rR(root, z);
            }
            if (z->parent) {
                z->parent->c = 'b';
                if (z->parent->parent) {
                    z->parent->parent->c = 'r';
                    root = lR(root, z->parent->parent);
                }
            }
        }
    }
    root->c = 'b';
    return root ;
}

RB *insert(RB *root, int data) {
    struct RB *z = new RB;
    struct RB *copy = z;
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
        root = fixDoubleRed(root, z); //since z's parent has double red problem
    } else { //the case when data is already present in the tree
        x->count++;
    }
    return root;
}

void inOrder(struct RB *root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    cout << root->d << root->c << root->count << " ";
    inOrder(root->right);
}

void levelOrder(RB *root)
{
    if (root == NULL)
        return;

    queue<RB *> q;
    q.push(root);

    while (!q.empty())
    {
        RB *temp = q.front();
        cout << temp->d << "  ";
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}

void help(RB* rb){
    inOrder(rb);
    cout<<endl;
    levelOrder(rb);
    cout<<endl;
}

void maxQuery(RB* rb){
    while(rb->right){
        rb = rb->right;
    }
    cout<<"\nThe employee with maximum salary has salary: "<<rb->d<<"\n";
    cout<<"The number of employee with same salary are: "<<rb->count<<"\n";
    return;
}


void minQuery(RB* rb){
    while(rb->left){
        rb = rb->left;
    }
    cout<<"\nThe employee with minimum salary has salary: "<<rb->d<<"\n";
    cout<<"The number of employee with same salary are: "<<rb->count<<"\n";
    return;
}

int empInRange(RB* rb, int x, int y){
   if(rb == NULL){
       return 0;
   }
   if(rb->d>=x && rb->d<=y){
       return rb->count+empInRange(rb->left,x,y)+empInRange(rb->right,x,y);
   }
   if(rb->d<x && rb->d<y){
       return empInRange(rb->right,x,y);
   }
   if(rb->d>x && rb->d >y){
       return empInRange(rb->left,x,y);
   }
}
int main() {
    //ifstream fin;
    //fin.open("input.txt");
    //read file and insert n elements into the RB Tree

    RB *rb = NULL;
    rb = insert(rb,7);
    rb = insert(rb,6);
    rb = insert(rb,5);
    rb = insert(rb,4);
    rb = insert(rb,4);
    rb = insert(rb,9);
    rb = insert(rb,12);
    rb = insert(rb,15);
    help(rb);
    minQuery(rb);
    maxQuery(rb);
    cout<<"\n No of employee in the range 4 to 6 are: "<<empInRange(rb,4,6)<<"\n";
    //make a menu for user to easily insert/delete elements and make queries

    return 0;
}