//
//  HuffmanCode.hpp
//  H264Codec
//
//  Created by linwenhu on 2020/10/19.
//

#ifndef HuffmanCode_hpp
#define HuffmanCode_hpp

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

typedef struct {
    unsigned char character;
    unsigned int frequency;
} CharNode;

struct MinHeapNode {
    char data;
    unsigned int freq;
    MinHeapNode *left, *right;
    
    MinHeapNode(char data, unsigned freq) {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

typedef struct MinHeapNode MinHeapNode;

class HuffmanCodec {
public:
    HuffmanCodec(char *inputFileName);
    ~HuffmanCodec();
    void get_huffman_code();
    
private:
    char *m_inputFileName;
    std::ifstream m_inputFile;
    MinHeapNode *m_root;
    bool open_input_file();
    void build_huffman_tree();
    void get_huffman_code(MinHeapNode *root, std::string code);
};

#endif /* HuffmanCode_hpp */
