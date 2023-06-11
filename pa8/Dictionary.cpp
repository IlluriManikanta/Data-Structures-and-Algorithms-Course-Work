// // ========== Name ========== //
// // Manikantanagasai H. Illuri //
// // milluri@ucsc.edu           //
// // 2023 Spring CSE101         //
// // PA 8                       //
// // Dictionary ADT             //
// // ========================== //


#include <iostream>
#include "Dictionary.h"
#include <fstream>

#define RED 1
#define BLACK 0

//All functions in this file were written reffering to TA Mike's sudo code for pa7 which is provided in his google drive.
//Link to Sudo code "https://drive.google.com/file/d/1hNyVUto4a8gs0K4TkEyBX9tWmy_tyfOY/view?usp=share_link" (unsure if link works for everyone)


// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Node::Node(keyType k, valType v) {
  this->key = k;
  this->val = v;
  this->left = nullptr;
  this->right = nullptr;
  this->parent = nullptr;
  color = BLACK;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new Dictionary in the empty state.
Dictionary::Dictionary(){
    nil = new Node(" ", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node(" ", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
	postOrderDelete(this->root);
	delete nil;
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + '\n';
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s.append(R->key);
        if(R->color == RED){
            s.append(" (RED)");
        }
        s.append("\n");
        preOrderString(s, R->left);
	    preOrderString(s, R->right);

    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }

}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R != nil){
        postOrderDelete(R->right);
        postOrderDelete(R->left);
        //num_pairs -= 1;
        delete R;
    }
    //R = nil;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if (k == R->key || R == nil){
        return R;		
    } else if (k < R->key){
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    Node *temp = R;
    if(temp != nil){
        while (temp->left != nil){
            temp = temp->left;
        } 
    }
    return temp;
}


// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    Node* max = R;
	if (max != nil) {
		while (max->right != nil) {
			max = max->right;
		}
	}
	return max;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if (N == nil){
        return nil;
    } else if (N->right != nil){
        return findMin(N->right);
    } else {
        Node* y = N->parent;
        while (y != nil && N == y->right){
            N = y;
            y = y->parent;
        }
        return y;
    }
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N == nil){
        return nil;
    } else if (N->left != nil){
        return findMax(N->left);
    } else {
        Node* temp = N->parent;
        while(temp != nil && N == temp->left){
            N = temp;
            temp = temp->parent;
        }
        return temp;
    }
}


//Additional Functions-----------------------------------------------------------------------------

// LeftRotate()
   void Dictionary::LeftRotate(Node* N){
        Node* M = N->right;
        N->right = M->left;

        if (M->left != nil) { 
            M->left->parent = N;
        }

        M->parent = N->parent;

        if (N->parent == nil) { 
            root = M;
        }
        else if (N == N->parent->left) {
            N->parent->left = M;
        } else {
            N->parent->right = M;
        }
        M->left = N;
        N->parent = M;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N){
        Node* M = N->left;

        N->left = M->right;

        if (M->right != nil) {
            M->right->parent = N;
        }

        M->parent = N->parent;

        if (N->parent == nil) {
            root = M;
        } else if (N == N->parent->right) {
                N->parent->right = M;
        } else {
                N->parent->left = M;
        }
        M->right = N;
        N->parent = M;
   }

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N){
        while (N->parent->color == RED) {
            if (N->parent == N->parent->parent->left) {
                Node* y = N->parent->parent->right;
                if (y->color == RED) {
                    N->parent->color = BLACK;                   
                    y->color = BLACK;                             
                    N->parent->parent->color = RED;               
                    N = N->parent->parent;                        
                }
                else {
                    if (N == N->parent->right) {
                        N = N->parent;                           
                        LeftRotate(N);                         
                    }
                    N->parent->color = BLACK;                     
                    N->parent->parent->color = RED;                
                    RightRotate(N->parent->parent);             
                }
            }
            else {
                Node* y = N->parent->parent->left;
                if (y->color == RED) {
                    N->parent->color = BLACK;                    
                    y->color = BLACK;                             
                    N->parent->parent->color = RED;               
                    N = N->parent->parent;                        
                }
                else {
                    if (N == N->parent->left) {
                        N = N->parent;                            
                        RightRotate(N);                        
                    }
                    N->parent->color = BLACK;                     
                    N->parent->parent->color = RED;                
                    LeftRotate(N->parent->parent);              
                }
            }
        }
        root->color = BLACK;
   }

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v){
        if (u->parent == nil) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }

        v->parent = u->parent;
   }

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N){
        while (N != root && N->color == BLACK) {
            if (N == N->parent->left) {
                Node* w = N->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    N->parent->color = RED;
                    LeftRotate(N->parent);
                    w = N->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    N = N->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w = N->parent->right;
                    }
                    w->color = N->parent->color;
                    N->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(N->parent);
                    N = root;
                }
            }
            else {
                Node* w = N->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    N->parent->color = RED;
                    RightRotate(N->parent);
                    w = N->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    N = N->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = N->parent->left;
                    }
                    w->color = N->parent->color;
                    N->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(N->parent);
                    N = root;
                }
            }
        }
        N->color = BLACK;
   }

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N){
    Node* y = N;
    Node* x;
    int y_color = y->color;

    if (y->left == nil) {
        x = N->right;
        RB_Transplant( y, y->right);
    }
    else if (y->right == nil) {
        x = y->left;
        RB_Transplant(y, y->left);
    }
    else {
        y = findMin(y->right);
        y_color = y->color;
        x = y->right;

        if (x == nil) { // To pdate x pointer when y->right is nil
            x = y->parent; // To update x to y's parent
        }
       
        RB_Transplant(y, y->right);
        y->right = N->right;
        y->right->parent = y;
        
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }

    if (y_color == BLACK) {
        RB_DeleteFixUp(x);
    }
    delete N;
   }



// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if((search(root, k)) != nil){
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node *N = search(root, k);
    if(N == nil){
        throw std::logic_error("Dictionary ADT: ERROR in getValue(): key \""+k+"\" does not exist");
    }
    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (current == nil){
        throw std::logic_error("Dictionary ADT: ERROR in currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (current == nil){
        throw std::logic_error("Dictionary ADT: ERROR in currentVal(): current undefined");
    } 
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    current = nil;
    root = nil;
    num_pairs = 0;
}


// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
//Had to rewrite setvalue. This implementation was creating with the help of numerous TA's and 
//sudo code provided by them from previous asgn. 
void Dictionary::setValue(keyType k, valType v) {
    Node* cNode = root;
    Node* pNode = nil;

    while (cNode != nil) {
        if (k < cNode->key) {
            pNode = cNode;
            cNode = cNode->left;
        } else if (k > cNode->key) {
            pNode = cNode;
            cNode = cNode->right;
        } else {
            cNode->val = v;
            return;
        }
    }

    Node* node = new Node(k, v);
    node->color = 1;
    node->left = nil;
    node->right = nil;
    node->parent = pNode;

    if (pNode == nil)
        root = node;
    else if (k < pNode->key)
        pNode->left = node;
    else
        pNode->right = node;

    num_pairs++;
    RB_InsertFixUp(node);
}

//remove()
void Dictionary::remove(keyType k){
    Node *t = search(root, k);
    if(t == nil){
      throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
   }
   if(current->key == k){
        current = nil;
   }
   if(t != nil){
        RB_Delete(t);
        num_pairs--;
   }

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if (num_pairs <= 0){
        throw std::length_error("Dictionary ADT: ERROR in begin(): Dictionary is empty");
    } 
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if (num_pairs <= 0){
        throw std::length_error("Dictionary ADT: ERROR in end(): Dictionary is empty");
    }
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (current == nil){
        throw std::logic_error("Dictionary ADT: ERROR in next(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(current == nil){
        throw std::logic_error("Dictionary ADT: ERROR in prev(): current undefined");
    }
    current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    return (to_string() == D.to_string()) && (num_pairs == D.num_pairs);
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;

}