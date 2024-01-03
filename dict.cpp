// Do NOT add any other includes
#include "dict.h"
#define pb push_back
#define ll long long
#define len(v) (int)v.size()

Chaining::Chaining(){
}

void Chaining::createAccount(std::string id) {
    Word p ;
    p.id = id ;
    p.reps = 1;
    int i = hash(id);
    bankStorage2d[i].push_back(p);
}

void Chaining::createAccount_freq(std::string id,long double freq) {
    Word p ;
    p.id = id ;
    p.reps = freq;
    int i = hash(id);
    bankStorage2d[i].push_back(p);
}

long double Chaining::getBalance(std::string id) {
    int j = hash(id);
    if(bankStorage2d[j].size()==0){
        return 0;
    }
    else{
        for(int c=0;c<bankStorage2d[j].size();c++){
            if(bankStorage2d[j][c].id == id){
                return bankStorage2d[j][c].reps;
                break;
            }
        }
        return 0;
    }
}

void Chaining::addTransaction(std::string id) {
    int j = hash(id);
    bool found = false;
    if(bankStorage2d[j].size()==0){
        createAccount(id);
    }
    else{
        for(int c=0;c<bankStorage2d[j].size();c++){
            if(bankStorage2d[j][c].id == id){
                bankStorage2d[j][c].reps += 1;
                found = true;
                break;
            }
        }
        if(found==false){
            createAccount(id);
        }
    }
}

int Chaining::hash(std::string id) {
    int m = 1000003;
    int k = 131;
    int s  = 37;
    long long hsh1=0;
    long long mul = s;
    for(int i=0;i<id.size();i++){
            char c = id[i];
            hsh1 = (((hsh1*k) +  int(c))*mul)%m ;
            mul = (mul*s)%m;
    }
    return (int)hsh1;  
}


vector<string> break_string (string sentence){

    vector<string>res;
    string temp = "";

    int n = int(sentence.size());
    for(int i = 0;i<n;i++){
        char curr = sentence[i];
        if(('a'<=curr && curr<='z') || ('A'<=curr && curr<='Z') || ('0'<=curr && curr<='9')){
        	curr = (char)tolower(curr);
        	temp.push_back(curr);
        }
        else{
		    switch(curr){
		        case '.':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case ',':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '-':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case ':':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '!':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '"':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '\'':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '(':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case ')':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '?':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '[':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case ']':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case ';':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case '@':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;
		        case ' ':
		            if(temp.size()>0){
		                res.push_back(temp);
		                temp = "";
		            }
		            break;

		        default:
		        	curr = (char)tolower(curr);
		            temp.push_back(curr);
		    }
		}
	}	
    if(temp.size()>0){
        res.push_back(temp);
        temp = "";
    }
    return res;
}

Dict_hash::Dict_hash(){
    Hashtable = new Chaining();
}

Dict_hash::~Dict_hash(){
    delete Hashtable;    
}

void Dict_hash::insert(string word , long double freq){
    Hashtable->createAccount_freq(word,freq);
    return;
}


void Dict_hash::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    vector<string> in = break_string(sentence) ;
    for(int i =0; i<in.size();i++){
        Hashtable->addTransaction(in[i]);
    }
    return;
}

long double Dict_hash::get_word_count(string word){
    return Hashtable->getBalance(word);
}

// AVL tree node definitions

int hei(SymNode* A){
    if(A)
    {
        return A->height;
    }
    else{
        return 0;
    }
}
void he(SymNode* A){
  
    A->height = 1 + max(hei(A->left),hei(A->right));
    
}
SymNode::SymNode()
{
    key = "";
    height = 1;
    par = 0;
    left = 0;
    right = 0;
    
    
}
SymNode::SymNode(string k){
    key = k;
    height = 1;
    par = 0;
    left = 0;
    right = 0;
    count = 1;
}
SymNode* SymNode::LeftLeftRotation(){
    SymNode* A = this;
    SymNode* B = A->left;
    if(B->right)
    {
        B->right->par = A;
        A->left = B->right;
    }
    else{
        A->left = B->right;
    }
    B->par = A->par;
    A->par = B;
    B->right = A;
    
    he(A);
    he(B);
    
    
    
    
    return B;
    
}
SymNode* SymNode::RightRightRotation(){
    SymNode* A = this;
    SymNode* B = A->right;
    if(B->left)
    {
        B->left->par = A;
        A->right = B->left;
    }
    else{
        A->right = B->left;
    }
    B->par = A->par;
    A->par = B;
    B->left = A;
    he(A);
    he(B);
    
    
    
    
    return B;
    
    
}

                   
                   
SymNode* SymNode::LeftRightRotation(){
    SymNode* z = this;
    SymNode* y = z->left;
    SymNode* x = y->right;
    x->par = z->par;
    y->par = x;
    z->par = x;
    if(x->left)
    {
        x->left->par = y;
    }
    if(x->right)
    {
        x->right->par = z;
    }
    y->right = x->left;
    z->left = x->right;
    x->left = y;
    x->right = z;
    he(y);
    he(z);
    he(x);
    
    
    
    
    
    
    
    return x;
    
}
SymNode* SymNode::RightLeftRotation(){
    SymNode* z = this;
    SymNode* y = z->right;
    SymNode* x = y->left;
    x->par = z->par;
    y->par = x;
    z->par = x;
    if(x->left)
    {
        x->left->par = z;
    }
    if(x->right)
    {
        x->right->par = y;
    }
    y->left = x->right;
    z->right = x->left;
    x->left = z;
    x->right = y;
    he(y);
    he(z);
    he(x);

    return x;
    
}

SymNode::~SymNode(){
    left = 0;
    right = 0;
    // delete complete tree rooted at this node
//    if(left){
//        if(left->key=="1"){
//            
//        }
//        delete left;
//        left = 0;
//        
//    }
//    if(right){
//        if(right->key=="1"){
//            
//        }
//        delete right;
//        right = 0;
//        
//    }
    
}

int hei_giv(SymNode* a){
    if(a){
        return a->height;
    }
    else {
        return 0;
    }
}

int finder(SymNode* a){ // 0 when nothing else 1,2,3,4 for ll,lr,rl,rr
    int l = hei_giv(a->left);
    int u = hei_giv(a->right);
    if(l-u>=2){
        int l1 = hei_giv(a->left->left);
        int l2 = hei_giv(a->left->right);
        if(l1>=l2){
            return 1;
        }
        else{
            return 2;
        }
        
    }
    else if (l-u<=-2){
        int l1 = hei_giv(a->right->left);
        int l2 = hei_giv(a->right->right);
        if(l1>l2){
            return 3;
        }
        else{
            return 4;
        }
        
    }
    else{
        return 0;
    }
    
}
void balance_height_update(SymNode* & prev, SymNode* & root){
    
    while(prev!=0){
        
        if(prev->right){
            
            int l = finder(prev->right);
            if(l==1){
                prev->right = prev->right->LeftLeftRotation();
            }
            else if(l==2){
                prev->right = prev->right->LeftRightRotation();
            }
            else if (l==3){
                prev->right = prev->right->RightLeftRotation();
            }
            else if (l==4){
                prev->right = prev->right->RightRightRotation();
            }
            
        }
        if(prev->left){
            int l = finder(prev->left);
            if(l==1){
                prev->left = prev->left->LeftLeftRotation();
            }
            else if(l==2){
                prev->left = prev->left->LeftRightRotation();
            }
            else if (l==3){
                prev->left = prev->left->RightLeftRotation();
            }
            else if (l==4){
                prev->left = prev->left->RightRightRotation();
            }
            
            
        }
        prev->height = 1+ max(hei_giv(prev->left),hei_giv(prev->right));
        prev = prev->par;
        
        
    }
    // prev = 0 means check at root SymNode
    int l = finder(root);
    root->height = 1+ max(hei_giv(root->left),hei_giv(root->right));
    if(l==1){
        root = root->LeftLeftRotation();
    }
    else if(l==2){
        root = root->LeftRightRotation();
    }
    else if (l==3){
        root = root->RightLeftRotation();
    }
    else if (l==4){
        root = root->RightRightRotation();
    }
    root->height = 1+ max(hei_giv(root->left),hei_giv(root->right));
}


SymbolTable::SymbolTable(){
    size = 0;
    root = 0;
}

int SymbolTable::search(string k){
    SymNode* cur  = root;
    while(cur!=0){
        if(cur->key==k){
            return cur->count;
          
        }
        else if (cur->key<k){
            cur = cur->right;
        }
        else if (cur->key>k){
            cur = cur->left;
        }
        
    }
    return 0;
    
}
void SymbolTable::insert(string k)
{
       if(root==0)
       {
        root = new SymNode(k);
        size++;
        
       }
    else
    {
        SymNode * work = root;
        SymNode* prev = root;
      
        int ct = 0;
        // ct = 1 then left if ct = 2 then right
        // to start balancing from the SymNode prev
        bool state = true;
        while(work!=0)
        {
            if(work->key < k)
            {
                work=work->right;
                ct = 2;
                if(work==0){
                    prev->right = new SymNode(k);
                    prev->right->par = prev;
                    prev->height = 1+ max(hei_giv(prev->left),hei_giv(prev->right));
                    size++;
                    break;
                }
            }
            else if (work->key > k)
            {
                work = work->left;
                ct = 1;
                if(work==0){
                    prev->left = new SymNode(k);
                    prev->left->par = prev;
                    prev->height = 1+ max(hei_giv(prev->left),hei_giv(prev->right));
                    size++;
                    break;
                }
            }
            else
            {
                work->count +=1 ;
                state = false;
                break;
                
            }
            if(ct==1){
                prev = prev->left;
            }
            if(ct==2){
                prev = prev->right;
            }
            
        }
        
        // now the rebalancing starts
        if(state){ // i.e. if a new SymNode is inserted
           
            balance_height_update(prev, root);
            
        }
        
        
    }
}

SymbolTable::~SymbolTable(){
    vector<SymNode*> vec;
    vec.push_back(root);
    while(vec.size()!=0){
        SymNode* a = vec.back();
        vec.pop_back();
        if(a){
            vec.push_back(a->left);
            vec.push_back(a->right);
            delete a;
        }
        
    }
   
    
}


void Dict_avl::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
 
    string temp = "";
    
    int n = int(sentence.size());
    for(int i = 0;i<n;i++){
        char curr = sentence[i];
        if(('a'<=curr && curr<='z') || ('A'<=curr && curr<='Z') || ('0'<=curr && curr<='9'))
        {
            curr = (char)tolower(curr);
            temp.push_back(curr);
        }
        else{
            switch(curr){
                case '.':
                    if(temp.size()>0){
                        data->insert(temp);
                        
                        temp = "";
                    }
                    break;
                case ',':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '-':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case ':':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '!':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '"':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '\'':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '(':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case ')':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '?':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '[':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case ']':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case ';':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case '@':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                case ' ':
                    if(temp.size()>0){
                        data->insert(temp);
                        temp = "";
                    }
                    break;
                    
                default:
                    curr = (char)tolower(curr);
                    temp.push_back(curr);
            }
        }
        
       
        
        
    }
if(temp.size()>0){
    data->insert(temp);
    temp = "";
}
    
   
 
}

int Dict_avl::get_word_count(string word)
{
    return data->search(word);
}



Dict_avl::Dict_avl()
{
    data = new SymbolTable();
}

Dict_avl::~Dict_avl()
{
    delete data;
}


