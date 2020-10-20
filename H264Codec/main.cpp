//
//  main.cpp
//  H264Codec
//
//  Created by wentilin on 2020/10/18.
//

#include <iostream>
#include "CStreamFile.hpp"
#include "HuffmanCode.hpp"
#include "ExpColumCodec.hpp"

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
    
    // exp_colum_codec
    UINT8 strArray[6] = { 0xA6, 0x42, 0x98, 0xE2, 0x04, 0x8A };
    UINT8 dataLengthInBits = sizeof(strArray) * 8;

    ExpColumCodec codec;
    vector<int> result;
    codec.decode(strArray, dataLengthInBits, result);
    
    for (int i = 0; i < result.size(); i++) {
        printf("ExpoColumb codeNum = %d\n", result.at(i));
    }
    
    return 0;
}
