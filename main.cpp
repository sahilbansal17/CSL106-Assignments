//submitted by SAHIL 2016CSJ0008
//reference taken from CH-13 RED BLACK TREES of Intro to Algorithms (Thomas H. Cormen)

#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include <math.h>

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
RB *lR(struct RB *root, struct RB *x) {
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
RB *rR(struct RB *root, struct RB *y) {
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
    return root;
}

RB *fixDoubleRed(struct RB *root, struct RB *z) {
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
    return root;
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
    cout << "\nThe element " << data << " inserted successfully.\n\n";
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

void levelOrder(RB *root) {
    if (root == NULL)
        return;

    queue<RB *> q;
    q.push(root);

    while (!q.empty()) {
        RB *temp = q.front();
        cout << temp->d << "  ";
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}

void help(RB *rb) {
    inOrder(rb);
    cout << endl;
    levelOrder(rb);
    cout << endl;
}

void maxQuery(RB *rb) {
    while (rb->right) {
        rb = rb->right;
    }
    cout << "\nThe employee with maximum salary has salary: " << rb->d << "\n";
    cout << "The number of employee with same salary are: " << rb->count << "\n\n";
    return;
}


void minQuery(RB *rb) {
    while (rb->left) {
        rb = rb->left;
    }
    cout << "\nThe employee with minimum salary has salary: " << rb->d << "\n";
    cout << "The number of employee with same salary are: " << rb->count << "\n\n";
    return;
}

RB *treeMin(RB *rb) {
    while (rb->left) {
        rb = rb->left;
    }
    return rb;
}

int empInRange(RB *rb, int x, int y) {
    if (rb == NULL) {
        return 0;
    }
    if (rb->d >= x && rb->d <= y) {
        return rb->count + empInRange(rb->left, x, y) + empInRange(rb->right, x, y);
    }
    if (rb->d < x && rb->d < y) {
        return empInRange(rb->right, x, y);
    }
    if (rb->d > x && rb->d > y) {
        return empInRange(rb->left, x, y);
    }
    return 0;
}

RB *transplant(RB *rb, RB *u, RB *v) {
    if (u->parent == NULL) {
        rb = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
    return rb;
}

RB *fixBlackDepth(RB *rb, RB *x) {
    struct RB *w;
    while (x != rb && x->c == 'b') {
        //when x is the left child of its parent
        if (x->parent && x == x->parent->left) {
            w = x->parent->right;
            //case 1
            if (w) {
                if (w->c == 'r') {
                    w->c = 'b';
                    x->parent->c = 'r';
                    rb = lR(rb, x->parent);
                    w = x->parent->right;
                }
                //case 2
                if (w->left && w->left->c == 'b' && w->right && w->right->c == 'b') {
                    w->c = 'r';
                    x = x->parent;
                }//case 3
                else if (w->right && w->right->c == 'b') {
                    if (w->left) w->left->c = 'b';
                    w->c = 'r';
                    rb = rR(rb, w);
                    w = x->parent->right;
                }
                w->c = x->parent->c;
                x->parent->c = 'b';
                w->right->c = 'b';
                rb = lR(rb, x->parent);
                x = rb;
            }
        }
            //when x is the right child of its parent
        else {
            if (x->parent && x == x->parent->right) {
                w = x->parent->left;
                //case 1
                if (w) {
                    if (w->c == 'r') {
                        w->c = 'b';
                        x->parent->c = 'r';
                        rb = rR(rb, x->parent);
                        w = x->parent->left;
                    }
                    //case 2
                    if (w->right && w->right->c == 'b' && w->left && w->left->c == 'b') {
                        w->c = 'r';
                        x = x->parent;
                    }//case 3
                    else if (w->left && w->left->c == 'b') {
                        if (w->right) w->right->c = 'b';
                        w->c = 'r';
                        rb = lR(rb, w);
                        w = x->parent->left;
                    }
                    w->c = x->parent->c;
                    x->parent->c = 'b';
                    w->left->c = 'b';
                    rb = rR(rb, x->parent);
                    x = rb;
                }
            }

        }
        x->c = 'b';
    }
    return rb;
}

RB *deleteRB(RB *rb, int data) {
    struct RB *temp = rb;
    int min = INT_MAX; //to keep track of closest salary to the one to be deleted as we find it, it must be on same path
    struct RB *closest_sal_emp; //employee with closest salary to the employee to be deleted
    while (temp != NULL && temp->d != data) {
        if (abs(temp->d - data) < min) {  //if difference from data less than minimum diff so far change it
            min = abs(temp->d - data); //minimum difference seen so far
            closest_sal_emp = temp;
        }
        if (data < temp->d) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    if (temp == NULL) {
        //the case when we did not find the required employee, just print the closest salary to his/her salary
        cout << "\nThe salary not found in DB, closest salary is : " << closest_sal_emp->d
             << " & the no of such employee are : " << closest_sal_emp->count << "\n\n";
    } else if (temp->count > 1) {
        temp->count--;
        cout << "\nThe employee with same salary " << data << " are " << temp->count + 1
             << ". So, one employee deleted from DB.\n\n";
    } else {
        //the case when we acutally need to delete a node from RB Tree, temp is to be deleted
        struct RB *y = temp; //copy of node to be deleted, useful when swapping with predecessor
        struct RB *x; //node which moves into y's original position
        char y_org_color = y->c;
        if (temp->left == NULL) {
            //case 1: temp has only right child or temp has NO CHILD
            x = temp->right;
            rb = transplant(rb, temp, temp->right);
        } else if (temp->right == NULL) {
            //case 2: temp has only left child
            x = temp->left;
            rb = transplant(rb, temp, temp->left);
        } else {
            //case 3: temp has two children, replacing with successor and deleting the successor
            y_org_color = y->c;
            y = treeMin(temp->right);
            x = y->right;
            if (x && y->parent == temp) {
                x->parent = y;
            } else {
                rb = transplant(rb, y, y->right);
                if (y->right) {
                    y->right = temp->right;
                    y->right->parent = y;
                }
            }
            rb = transplant(rb, temp, y);
            y->left = temp->left;
            if (y->left) {
                y->left->parent = y;
            }
            y->c = temp->c;
            //the case when the black depth of external nodes doesn't remain the same
            //x is the node whose black depth could have been altered
            if (y_org_color == 'b')rb = fixBlackDepth(rb, x);
        }
        cout << "\nThe element " << data << " deleted successfully.\n\n";
    }

    return rb;
}

int main() {
    ifstream fin;
    fin.open("input.txt");
    //read file and insert n elements into the RB Tree

    RB *rb = NULL;

    int n, value;
    fin >> n;
    while (!fin.eof()) {
        fin >> value;
        rb = insert(rb, value);
    }

    /*RB *rb = NULL;
    rb = insert(rb, 7);
    rb = insert(rb, 6);
    rb = insert(rb, 5);
    rb = insert(rb, 4);
    rb = insert(rb, 4);
    rb = insert(rb, 9);
    rb = insert(rb, 12);
    rb = insert(rb, 15);
    rb = deleteRB(rb, 6);
    help(rb);
    minQuery(rb);
    maxQuery(rb);
    cout << "\n No of employee in the range 4 to 6 are: " << empInRange(rb, 4, 6) << "\n";*/

    string s;
    cout << "\n\n1. \"A x\" to add employee to database.\n";
    cout << "2. \"R x\" to delete employee from database.\n";
    cout << "3. \"Q x y\" to return the no of employees having salary in range [x y].\n";
    cout << "4. \"Max\" to return maximum salary.\n";
    cout << "5. \"Min\" to return minimum salary.\n";
    cout << "0. \"0\" to close the program.\n\n";
    cin >> s;
    while (s != "0") {
        if (s == "A" || s=="r") {
            int x;
            cin >> x;
            rb = insert(rb, x);
        }
        else if(s == "R" || s=="r"){
            int x;
            cin>>x;
            rb = deleteRB(rb, x);
        }
        else if(s== "Max" || s=="max"){
            maxQuery(rb);
        }
        else if(s=="Min" || s=="min"){
            minQuery(rb);
        }
        else if(s=="Q" || s=="q"){
            int x,y;
            cin>>x>>y;
            cout<<"\nQuery answer: "<<empInRange(rb,x,y)<<".\n\n";
        }
        cin>>s;
    }
    return 0;
}