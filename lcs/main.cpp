//
//  main.cpp
//  lcs
//
//  Created by Derek Harrison on 23/10/2021.
//

#include <iostream>
#include <string>

typedef struct memo_table {
    bool is_set;
    std::string str;
} m_table;

int tot_num_ops = 0;
int num_ops_saved = 0;

std::string lcs(std::string x, std::string y, m_table** memo_table) {
    
    tot_num_ops++;
    
    int length_x = (int) x.length();
    int length_y = (int) y.length();
    
    std::string result;
    
    //Get results from memo table if available
    if(memo_table[length_x - 1][length_y - 1].is_set) {
        num_ops_saved++;
        return memo_table[length_x - 1][length_y - 1].str;
    }

    if(length_x > 0 && length_y > 0) {
        if(x[length_x - 1] != y[length_y - 1]) {
            std::string x_substr = x.substr(0, length_x - 1);
            std::string y_substr = y.substr(0, length_y - 1);
            
            std::string str1 = lcs(x_substr, y, memo_table);
            std::string str2 = lcs(x, y_substr, memo_table);
            
            int length_str1 = (int) str1.length();
            int length_str2 = (int) str2.length();
            
            if(length_str1 > length_str2) {
                result = result + str1;
            }
            else {
                result = result + str2;
            }
        }
        
        if(x[length_x - 1] == y[length_y - 1]) {
            std::string x_substr = x.substr(0, length_x - 1);
            std::string y_substr = y.substr(0, length_y - 1);
            result = result + x[length_x - 1];
            result = result + lcs(x_substr, y_substr, memo_table);
        }
        
        memo_table[length_x - 1][length_y - 1].is_set = true;
        memo_table[length_x - 1][length_y - 1].str = result;
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    
    std::string x = "ABCBDAB";
    std::string y = "BDCABA";
    std::string longest_cs;
    
    int max_size = 0;
    int len1 = (int) x.length();
    int len2 = (int) y.length();
    
    if(len1 < len2) {
        max_size = len2;
    }
    else {
        max_size = len1;
    }
    
    m_table** memo_table = new m_table*[max_size];
    for(int i = 0; i < max_size; ++i) {
        memo_table[i] = new m_table[max_size];
    }
    
    for(int i = 0; i < max_size; ++i) {
        for(int j = 0; j < max_size; ++j) {
            memo_table[i][j].is_set = false;
        }
    }
    
    longest_cs = lcs(x, y, memo_table);
    
    std::cout << longest_cs << std::endl;
    std::cout << "tot_num_ops: " << tot_num_ops << std::endl;
    std::cout << "num_ops_saved: " << num_ops_saved << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}
