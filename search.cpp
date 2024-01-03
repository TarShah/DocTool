// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    
}

SearchEngine::~SearchEngine(){
    while(data.size()!=0)
          {
              Nod* a = data.back();
              delete a;
              data.pop_back();
          }
          
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    for( char & x:sentence){
    x = tolower(x);
    }
    Nod * a = new Nod(book_code, page, paragraph, sentence_no, sentence);
    data.push_back(a);
}

Node* SearchEngine::search(string pattern, int& n_matches){

    Node* ans = new Node();
    ans->left = 0;
    ans->right=0;
    Node* dum = ans;
    int pre_process[pattern.size()];
    int j = 0;
    pre_process[0]=0;
    n_matches=0;
    pattern[0]=tolower(pattern[0]);
    for(int i = 1;i<pattern.size();i++){
    pattern[i]=tolower(pattern[i]);
        if(pattern[j]==pattern[i]){
            j++;
            
        }
        else{
            if(j!=0){
                j = pre_process[j-1];
            }
        }
        pre_process[i]=j;
    }
    
    for(Nod* x : data){
        string a = x->sentence;
        int j = 0;
        int l = (int)pattern.size();
        for(int i = 0;i<a.size();i++){
            if(j==l){
                ans->right = new Node(x->book_code,x->page,x->paragraph,x->sentence_no,i-l);
                ans->right->left = ans;
                ans = ans->right;
                n_matches++;
                j = pre_process[j-1];
                
            }
            if(a[i]!=(pattern[j])){
           
                if(j!=0){
                    j = pre_process[j-1];
                    i--;
                }
            }
            else
            {
                j++;
               
            }
        }
        if(j==l){
                ans->right = new Node(x->book_code,x->page,x->paragraph,x->sentence_no,a.size()-l);
                ans->right->left = ans;
                ans = ans->right;
                n_matches++;
                j = pre_process[j-1];
            }
        
        
    }
    if(n_matches==0){
        delete ans;
        dum = 0;
        return dum;
        
    }
    else{
        dum = dum->right;
        dum->left->right=0;
        delete dum->left;
        dum->left = 0;
        return dum;
    }
    
    
}



