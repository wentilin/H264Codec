//
//  main.cpp
//  H264Codec
//
//  Created by wentilin on 2020/10/18.
//

#include <iostream>
#include "CStreamFile.hpp"
#include "HuffmanCode.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc < 3) {
        printf("Error: input h264 file and text file");
        return -1;
    }
    
    char h264File[strlen(argv[1])];
    strcpy(h264File, argv[1]);
    CStreamFile streamFile(h264File);
    streamFile.Parse_h264_bitstream();
    
    char inputTextFile[strlen(argv[2])];
    strcpy(inputTextFile, argv[2]);
    HuffmanCodec huffmanCodec(inputTextFile);
    huffmanCodec.get_huffman_code();
    
    return 0;
}
