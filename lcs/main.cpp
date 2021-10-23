//
//  main.cpp
//  lcs
//
//  Created by mndx on 23/10/2021.
//

#include <iostream>
#include <string>

typedef struct memo_table {
    bool is_set;
    std::string str;
} m_table;

std::string lcs(std::string x, std::string y, m_table** memo_table) {
    
    int length_x = (int) x.length();
    int length_y = (int) y.length();
    
    std::string result;
    
    //Get results from memo table if available
    if(memo_table[length_x - 1][length_y - 1].is_set) {
        return memo_table[length_x - 1][length_y - 1].str;
    }

    //Compute longest common subsequence of substring
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
        
        //Add results to memo table
        memo_table[length_x - 1][length_y - 1].is_set = true;
        memo_table[length_x - 1][length_y - 1].str = result;
    }
    
    return result;
}

std::string longest_common_subs(std::string x, std::string y) {
    int max_size = 0;
    int len1 = (int) x.length();
    int len2 = (int) y.length();
    
    //Compute max length input strings
    if(len1 < len2) {
        max_size = len2;
    }
    else {
        max_size = len1;
    }
    
    //Initialize memo table
    m_table** memo_table = new m_table*[max_size];
    for(int i = 0; i < max_size; ++i) {
        memo_table[i] = new m_table[max_size];
    }
    
    for(int i = 0; i < max_size; ++i) {
        for(int j = 0; j < max_size; ++j) {
            memo_table[i][j].is_set = false;
        }
    }
    
    //Compute longest common subsequence
    std::string longest_cs = lcs(x, y, memo_table);
    
    //Reverse results
    std::string l_c_s = "";
    int lcs_len = (int) longest_cs.length();
    
    for(int i = lcs_len - 1; i > -1; --i) {
        l_c_s = l_c_s + longest_cs[i];
    }
    
    return l_c_s;
}

int main(int argc, const char * argv[]) {
    
    std::string x = "ABCBDABABA";
    std::string y = "BDCABAABA";
    
    std::string lcs = longest_common_subs(x, y);
    
    std::cout << lcs << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}
