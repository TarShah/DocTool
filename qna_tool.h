#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;


//------------Trie implementation done ------------//

class para_node{
public:
    long double score;
    int book_code;
    int page_number;
    int paragraph_number;
    Dict_avl* trie;
    para_node* right;
    para_node* left;
    para_node(){
        
        left = 0;
        right = 0;
        score = 1;
        trie = new Dict_avl();
       
        
    }
    ~para_node(){

//        if(right){
//            delete right;
//        }
        delete trie;
        score = -2;
        book_code = -2;
        paragraph_number = -2;
        
    }
    void damn(){
        vector<para_node*> vec;
        vec.push_back(this);
        while(vec.size()!=0){
            para_node* a = vec.back();
            vec.pop_back();
            if(a){
                vec.push_back(a->right);
                delete a;
            }
        }
        
    }
};


class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY,string question);

    // You can add attributes/helper functions here
    Dict_hash* csv;
    Dict_hash* word_count_dict;
public:
    para_node* para_head;
    para_node* para_tail;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};
