//
//  HuffmanCode.cpp
//  H264Codec
//
//  Created by linwenhu on 2020/10/19.
//

#include "HuffmanCode.hpp"

using namespace std;

struct compare {
    bool operator()(MinHeapNode *l, MinHeapNode *r) {
        return (l->freq > r->freq);
    }
};

HuffmanCodec::HuffmanCodec(char *inputFileName) {
    m_inputFileName = inputFileName;
    m_inputFile = std::ifstream();
    
    open_input_file();
    build_huffman_tree();
}

HuffmanCodec::~HuffmanCodec() {
    if (m_inputFile.is_open()) {
        m_inputFile.close();
    }
}

bool HuffmanCodec::open_input_file() {
    m_inputFile.open(m_inputFileName);
    if (!m_inputFile.is_open()) {
        return false;
    }
    
    return true;
}

void HuffmanCodec::build_huffman_tree() {
    char buf = m_inputFile.get();
    CharNode nodeArr[256] = { { 0, 0} };
    while (m_inputFile.good()) {
        cout << buf;
        nodeArr[buf].frequency++;
        nodeArr[buf].character = buf;
        buf = m_inputFile.get();
    }
    
    cout << endl;
    
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;
    
    for (int i = 0; i < 256; i++) {
        if (nodeArr[i].frequency > 0) {
            cout << "Node " << i << ": [" << nodeArr[i].character << ", " << nodeArr[i].frequency << "]" << endl;
            
            minHeap.push(new MinHeapNode(nodeArr[i].character, nodeArr[i].frequency));
        }
    }
    
    MinHeapNode *leftNode = NULL, *rightNode = NULL, *topNode = NULL;
    while (minHeap.size() != 1) {
        leftNode = minHeap.top();
        minHeap.pop();
        
        rightNode = minHeap.top();
        minHeap.pop();
        
        topNode = new MinHeapNode(-1, leftNode->freq + rightNode->freq);
        topNode->left = leftNode;
        topNode->right = rightNode;
        minHeap.push(topNode);
    }
    
    m_root = topNode;
}

void HuffmanCodec::get_huffman_code() {
    get_huffman_code(m_root, "");
}

void HuffmanCodec::get_huffman_code(MinHeapNode *root, std::string code) {
    if (!root) {
        return;
    }
    
    if (root->data != -1) {
        cout << root->data << " : " << code << endl;
    }
    
    get_huffman_code(root->left, code + "0");
    get_huffman_code(root->right, code + "1");
}
