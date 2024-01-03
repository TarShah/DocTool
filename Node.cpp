#include "Node.h"

Node::Node() {
    right = 0;
    left = 0;
}

Node::Node(int b_code, int pg, int para, int s_no, int off){
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    offset = off;
}
Node:: ~Node(){
    if(right) delete right;
    
    
}
