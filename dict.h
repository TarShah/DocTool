// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//baseclass for hastable
struct Word {
    std::string id;
    long double reps;
};

class BaseClass {
public:
    virtual void createAccount(std::string id) = 0;
    virtual void createAccount_freq(std::string id,long double freq) = 0;    
    virtual long double getBalance(std::string id) = 0;
    virtual void addTransaction(std::string id) = 0;
    virtual int hash(std::string id) = 0;
    std::vector<Word>  bankStorage2d[1000003];
    
};

class Chaining : public BaseClass {
public:
    Chaining();
    void createAccount(std::string id) override;
    void createAccount_freq(std::string id,long double freq) override;    
    long double getBalance(std::string id) override;
    void addTransaction(std::string id) override;
    int hash(std::string id) override;
private:
    // Other data members and functions specific to Chaining
};

class Dict_hash {
private:
    Chaining* Hashtable;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict_hash();

    ~Dict_hash();

	void insert(string word , long double freq);

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long double get_word_count(string word);


    /* -----------------------------------------*/
};

class SymNode {
public:
    string key;
    int count;
    int height;
    
    SymNode* par = NULL;
    SymNode* left = NULL;
    SymNode* right = NULL;

    SymNode();
    SymNode(string k);

    SymNode* LeftLeftRotation(); // case 1
    SymNode* RightRightRotation(); // case 2
    SymNode* LeftRightRotation(); // case 3
    SymNode* RightLeftRotation(); // case 4

    ~SymNode();
    
};

class SymbolTable {

    

public:
    int size = 0;
    
    SymNode* root = NULL;
    
    SymbolTable();
    
    ~SymbolTable();

    void insert(string k);
    int search(string k);

   
};


class Dict_avl {

public:
    SymbolTable* data;
   
    Dict_avl();

    ~Dict_avl();
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    

};
