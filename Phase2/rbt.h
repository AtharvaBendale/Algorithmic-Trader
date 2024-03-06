struct RBT_Tree;
struct Chain_Node{
    int price, in_time, expiring_time, quantity; 
    Chain_Node* next;
    std::string client;
    RBT_Tree* parent_tree;
    Chain_Node(int price, int quantity, int in_time, int expiring_time, std::string client):price(price),quantity(quantity),in_time(in_time),expiring_time(expiring_time),client(client),next(NULL){}
};
struct RBT_Node{
    int price, color;//1-red 0-black
    RBT_Node *parent, *left, *right;
    Chain_Node* head;
    RBT_Node():color(1),parent(NULL),left(NULL),right(NULL),head(NULL){}
    RBT_Node(int price):price(price),color(1),parent(NULL),left(NULL),right(NULL),head(NULL){}

    bool isOnLeft() { return this == parent->left; }
    RBT_Node *uncle() {
        if (!parent || !parent->parent) return NULL;
        if (parent->isOnLeft()) return parent->parent->right;
        else return parent->parent->left;
    }
    RBT_Node *sibling() {
        if (parent == NULL) return NULL;
        if (isOnLeft()) return parent->right;
        return parent->left;
    }
    void moveDown(RBT_Node *nParent) {
        if (!parent) {
        if (isOnLeft()) parent->left = nParent;
        else parent->right = nParent;
        }
        nParent->parent = parent;
        parent = nParent;
    }
    bool hasRedChild() {
        return (left != NULL && left->color) || (right != NULL && right->color);
    }
};

struct RBT_Tree{
    RBT_Node* root;
    RBT_Tree():root(NULL){};
    
    void swapColors(RBT_Node *x1, RBT_Node *x2) {
        int temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }
 
    void swapValues(RBT_Node *u, RBT_Node *v) {
        int temp;
        temp = u->price;
        u->price = v->price;
        v->price = temp;
    }

    void insert(RBT_Node* node){
        RBT_Node* found=search(root,node);
        if(!found){
            RBT_Node* p=root;
            if(!p) {p=node; return;}
            while(!p){
                if(p->price > node->price ) { if(!p->left) {p->left=node; node->parent=p; return;} else p=p->left; }
                else if(p->price < node->price ){ if(p->right) {p->right=node; node->parent=p; return;} else p=p->right; }
            }
            fixRedRed(p);
        }
    }
    RBT_Node* search(RBT_Node* root, RBT_Node* node){
        if(!root) {return NULL;}
        if(root->price==node->price) return root;

        if(root->price>node->price) {return search(root->left, node);}
        else {return search(root->right, node);}
        // return;
    }
    void rightRotate(RBT_Node* node){
        RBT_Node* g=node->parent;
        RBT_Node* y=node->left;
        node->left=y->right;
        y->right=node;
        if(node->left) node->left->parent=node;
        node->parent=y;
        if(g){
            y->parent=g;
            if(g->left==node) g->left=y;
            else g->right=y;
        }
        else y->parent=NULL;
    }
    void leftRotate(RBT_Node* node){
        RBT_Node* g=node->parent;
        RBT_Node* y=node->right;
        node->right=y->left;
        y->left=node;
        if(node->right) node->right->parent=node;
        node->parent=y;
        if(g){
            y->parent=g;
            if(g->right==node) g->right=y;
            else g->left=y;
        }
        else y->parent=NULL;
    }
    void fixRedRed(RBT_Node* node){
        if(!node->parent) node->color=0;

        else{
            if(node->parent->color){
                RBT_Node* p=node->parent;
                RBT_Node* g=p->parent;
                if(!g) { p->color=0; return; }
                
                RBT_Node* u=(g->left==p)? g->right: g->left; //uncle
                if(!u || !u->color){
                    bool flag=(g->left==p)?(p->left==node):(p->right==node);
                    if(!flag) { 
                        if(g->right==p ) rightRotate(p); 
                        else leftRotate(p);
                        RBT_Node* temp=p; p=node; node=temp;
                    }
                    g->color=1;
                    p->color=0;
                    if(g->left==p) rightRotate(g);
                    else leftRotate(g);
                }
                else{
                    u->color=0;
                    p->color=0;
                    g->color=1;
                    if(!g->parent) g->color=0;
                    else if(g->parent->color) fixRedRed(g);
                }
            }
        }
    }
    void fixDoubleBlack(RBT_Node *x) {
        if (x == root) return;
        RBT_Node *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL) {
        // No sibling, double black pushed up
        fixDoubleBlack(parent);
        } else {
        if (sibling->color) {
            // Sibling red
            parent->color = 1;
            sibling->color = 0;
            if (sibling->isOnLeft()) {
            // left case
            rightRotate(parent);
            } else {
            // right case
            leftRotate(parent);
            }
            fixDoubleBlack(x);
        } else {
            // Sibling black
            if (sibling->hasRedChild()) {
            // at least 1 red children
            if (sibling->left != NULL && sibling->left->color) {
                if (sibling->isOnLeft()) {
                // left left
                sibling->left->color = sibling->color;
                sibling->color = parent->color;
                rightRotate(parent);
                } else {
                // right left
                sibling->left->color = parent->color;
                rightRotate(sibling);
                leftRotate(parent);
                }
            } else {
                if (sibling->isOnLeft()) {
                // left right
                sibling->right->color = parent->color;
                leftRotate(sibling);
                rightRotate(parent);
                } else {
                // right right
                sibling->right->color = sibling->color;
                sibling->color = parent->color;
                leftRotate(parent);
                }
            }
            parent->color = 0;
            } else {
            // 2 black children
            sibling->color = 1;
            if (parent->color == 0)
                fixDoubleBlack(parent);
            else
                parent->color = 0;
            }
        }
        }
    }
    RBT_Node *successor(RBT_Node *x) {
        RBT_Node *temp = x;
    
        while (temp->left != NULL)
        temp = temp->left;
    
        return temp;
    }
    RBT_Node *BSTreplace(RBT_Node *x) {
        // when node have 2 children
        if (x->left != NULL && x->right != NULL) return successor(x->right);
        // when leaf
        if (x->left == NULL && x->right == NULL) return NULL;
        // when single child
        if (x->left != NULL) return x->left;
        else return x->right;
    }
    void deleteNode(RBT_Node *v) {
        RBT_Node *u = BSTreplace(v);
        // True when u and v are both black
        bool uvBlack = ((u == NULL || !u->color) && (!v->color ));
        RBT_Node *parent = v->parent;
    
        if (u == NULL) {
            // u is NULL therefore v is leaf
            if (v == root) {
                root = NULL; // v is root, making root null 
            } 
            else {
                if (uvBlack) {
                fixDoubleBlack(v); // u and v both black // v is leaf, fix double black at v
                } 
                else {  // u or v is red
                if (v->sibling() != NULL)
                    v->sibling()->color = 1; // sibling is not null, make it red"                    
                }
                // delete v from the tree
                if (v->isOnLeft()) parent->left = NULL;
                else parent->right = NULL;
            }
            delete v;
            return;
        }
    
        if (!v->left || !v->right) {
            // v has 1 child
            if (v == root) {
                // v is root, assign the value of u to v, and delete u
                v->price = u->price;
                v->left = v->right = NULL;
                delete u;
            }
            else {
                // Detach v from tree and move u up
                if (v->isOnLeft()) parent->left = u;
                else parent->right = u;
                delete v;
                u->parent = parent;
                if (uvBlack) fixDoubleBlack(u); // u and v both black, fix double black at u
                else u->color = 0; // u or v red, color u black
            }
            return;
        }   
        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteNode(u);
    }
    
    void deleteChainNode(Chain_Node* node){
        RBT_Node* p=root;
        while(p->price!=node->price){
            if(p->price>node->price) p=p->left;
            else p=p->right;
        }
        Chain_Node* n=p->head;
        if(n==node){delete n; delete p;}
        else{
            while(n->next!=node){
                n=n->next;
            }
            n->next=node->next;
            delete node;
        }
    }
    void chain_node_insert(Chain_Node* node)
    {
        RBT_Node* p=root;
        while(p && p->price!=node->price){
            if(p->price>node->price) p=p->left;
            else p=p->right;
        }
        if(!p){
            RBT_Node* new_rbt=new RBT_Node(node->price);
            insert(new_rbt);
        }
        Chain_Node* q=p->head;
        if(!q) { q=node; }
        else{ Chain_Node* r=q; p->head=node; node->next=r; }
    }
    Chain_Node* chain_min(Chain_Node* head){
        if(!head) return NULL;
        std::vector<Chain_Node*> min_elements;
        int min=head->price;
        Chain_Node* p=head;
        while(p){
            if(p->price<min){min_elements.clear();}
            if(p->price<=min){ min_elements.push_back(p);}
        }
        p=min_elements[0];
        for(auto i: min_elements){
            if(i->client < p->client) p=i;
        }
        return p;
    }
    Chain_Node* findmin(){
        RBT_Node* p=root;
        while(p && p->left){
            p=p->left;
        }
        return chain_min(p->head);
    }
    Chain_Node* findmax(){
        RBT_Node* p=root;
        while(p && p->right){
            p=p->right;
        }
        return chain_min(p->head);
    }
};