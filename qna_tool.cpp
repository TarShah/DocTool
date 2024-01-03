#include <assert.h>
#include <sstream>
#include <bits/stdc++.h>
#include "qna_tool.h"
#define file "we_ball.csv"
#define len(v) (int)v.size()
#define API "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"
using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"



struct node {
    long double score;
    int book_code;
    int page_num;
    int para_idx;
    bool operator>(const node& other)const{
        return score > other.score;
    }
    bool operator<(const node& other)const{
        return score < other.score;
    }
};

class MinHeap{
public:
    vector<node> v;
    MinHeap(){
        v ={};
    }
    int get_p(int id){
        return (id-1)/2;
    }
    int get_l(int id){
        return 2*id + 1;
    }
    int get_r(int id){
        return 2*id +2;
    }
    void heapifyup(int i){
        int par = get_p(i);
        if(v[par]>v[i]){
            swap(v[par],v[i]);
            heapifyup(par);
        }
    }
    void heapifydown(int i){
        int l = get_l(i);
        if(l>v.size()-1){
            return;
        }
        int temp = i;
        if(v[l]<v[i]){
            temp = l;
        }
        int r =get_r(i);
        if(r<v.size() && v[r]<v[temp]){
            temp =r;
        }
        if(temp!=i){
            swap(v[i],v[temp]);
            heapifydown(temp);
        }
    }
    void push(node n){
        v.push_back(n);
        heapifyup(v.size()-1);
    }
    void pop(){
        swap(v[0],v[v.size()-1]);
        v.pop_back();
        if(v.size()!=0){
            heapifydown(0);
        }
    }
    node get_min(){
        return v[0];
    }
    int size(){
        return v.size();
    }
    bool empty(){
        if(v.size()==0){
            return true;
        }
        return false;
    }
};

QNA_tool::QNA_tool(){
    // Implement your function here
    para_head = 0;
    para_tail = para_head;
    
    
    // Implement your function here

    csv = new Dict_hash();
    word_count_dict = new Dict_hash();
    ifstream write(file);
    string s;
    write>>s;
    while(write>>s){
        string id ="";
        string freq = "";
        bool st = 0;
        if((int)s[s.size()-1]==13 or (int)s[s.size()-1]==10){
            s.pop_back();
        }
        for(int i = 0;i<s.size();i++){
            if(s[i]==','){
                st = 1;
            }
            else{
                if(!st){
                    id.push_back(s[i]);
                }
                else{
                    freq.push_back(s[i]);
                }
            }
        }

        csv->insert(id, stold(freq));
        
    }
    
    write.close();
}

QNA_tool::~QNA_tool(){
    // Implement your function here
    delete csv;
    para_head->damn();
    delete word_count_dict;

 
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    word_count_dict->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    if(para_tail==0){
        para_head = new para_node();
        para_tail = para_head;
        para_tail->book_code = book_code;
        para_tail->page_number = page;
        para_tail->paragraph_number= paragraph;
        para_tail->trie->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    }
    else{
        if(para_tail->book_code==book_code and para_tail->paragraph_number==paragraph and para_tail->page_number==page){
            if(book_code==25 and paragraph==3 and page==443)
            {
                
            }
            para_tail->trie->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
        }
        else{
            para_tail->right = new para_node();
            para_tail->right->left = para_tail;
            para_tail = para_tail->right;
            para_tail->book_code = book_code;
            para_tail->page_number = page;
            para_tail->paragraph_number= paragraph;
            para_tail->trie->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
        }
        
    }
}


Node* QNA_tool::get_top_k_para(string question, int k) {
        ofstream outfile("real_query.txt");
        outfile << question;
        outfile.close();
//        
        vector<string> res;
        string temp = "";
        string command = "python3 ini_call.py ";
        system(command.c_str());
//        
        string sentence = "";
        ifstream infile("filtered_query.txt");
        string newtxt;
        while(getline(infile,newtxt)){
            sentence = sentence + newtxt;
            sentence = sentence + " ";
        }
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
                            res.push_back(temp);
                            temp = "";
                        }
                        break;
                    case '\n' :
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
    //--- update --//
    para_node* wor = para_head;
    while(wor!=0){
        for(string & a: res){
            
            long double den = (csv->get_word_count(a))+1;
            long double num = (2*wor->trie->get_word_count(a)+1);
            if(num == 1){
				num = 1;
            }
            else{
				num = (10 + log2(num));
            }
            long double ans = (num/den);
            wor->score *= ans;
        }
        wor = wor->right;
    }
    // --------- //
    
    // -----get top k starts---- //
    MinHeap pq;
    wor = para_head;
    for(int j = 0;j<k;j++){
        pq.push({wor->score,wor->book_code,wor->page_number,wor->paragraph_number});
        wor = wor->right;
    }
    for(;wor!=0;wor=wor->right){
        long double a = pq.get_min().score;
        if((wor->score)>a){
            pq.pop();
            pq.push({wor->score,wor->book_code,wor->page_number,wor->paragraph_number});
        }
    }
    Node * head = new Node();
    head->left = 0;
    head->right = 0;
    Node* work = head;
    work->paragraph = pq.get_min().para_idx;
    work->page = pq.get_min().page_num;
    work->book_code = pq.get_min().book_code;
    pq.pop();
    for(int j = 1;j<k;j++)
    {
        work->left = new Node();
        work->left->paragraph = pq.get_min().para_idx;
        work->left->page = pq.get_min().page_num;
        work->left->book_code = pq.get_min().book_code;
        pq.pop();
        work->left->right = work;
        work = work->left;
    }
    work->left = 0;
    if(k==0){
        delete head;
        head = 0;
    }
    para_node* modify = para_head;
    
    for(;modify!=0;modify = modify->right){
        modify->score = 0;
        
    }
    return work;
}

void QNA_tool::query(string question, string filename){
    Node* ans = get_top_k_para(question,10);
    std::cout << "Q: " << question << std::endl;
    query_llm(filename,ans,10,"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",question);
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }
    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
    // you do not need to necessarily provide k paragraphs - can configure yourself
    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}
