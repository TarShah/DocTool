// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class Nod{
public:
    int book_code,page,paragraph,  sentence_no;
    string sentence;
    Nod(int book, int pa, int para, int sentenc, string senten){
        book_code = book;
        page = pa;
        paragraph = para;
        sentence_no = sentenc;
        sentence = senten;
    
    }
};

class SearchEngine {

public: 
    vector<Nod*> data;
    
    
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};
