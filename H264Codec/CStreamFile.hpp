//
//  CStreamFile.hpp
//  H264Codec
//
//  Created by wentilin on 2020/10/18.
//

#ifndef CStreamFile_hpp
#define CStreamFile_hpp

#include <stdio.h>
#include <vector>

#include "Global.h"

/**
 描述子(descriptor):
    – ae(v): context-adaptive arithmetic entropy-coded syntax element.
 
    – ce(v): context-adaptive variable-length entropy-coded syntax element with the left bit first.
 
    – me(v): mapped Exp-Golomb-coded syntax element with the left bit first.
 
    – se(v): signed integer Exp-Golomb-coded syntax element with the left bit first.
 
    – te(v): truncated Exp-Golomb-coded syntax element with left bit first.
 
    – b(8): byte having any pattern of bit string (8 bits). The parsing process for this descriptor is specified by the return value of the function    read_bits( 8 ).
    
    – f(n): fixed-pattern bit string using n bits written (from left to right) with the left bit first. The parsing process for this descriptor is specified by     the return value of the function read_bits( n ).
    
    – i(n): signed integer using n bits. When n is “v” in the syntax table, the number of bits varies in a manner dependent on the value of other   syntax elements. The parsing process for this descriptor is specified by the return value of the function read_bits( n ) interpreted as a two’s     complement integer representation with most significant bit written first.
    
    – u(n): unsigned integer using n bits. When n is “v” in the syntax table, the number of bits varies in a manner dependent on the value of   other syntax elements. The parsing process for this descriptor is specified by the return value of the function read_bits( n ) interpreted as a     binary representation of an unsigned integer with most significant bit written first.
    
    – ue(v): unsigned integer Exp-Golomb-coded syntax element with the left bit first.
 */
class CStreamFile {
public:
    CStreamFile(char *fileName);
    ~CStreamFile();
    
    int Parse_h264_bitstream();
    
private:
    FILE *m_inputFile;
    char *m_fileName;
    std::vector<uint8> m_nalVec;
    
    void file_info();
    void file_error(int idx);
    int find_nal_prefix();
    void ebsp_to_sodb();
};

#endif /* CStreamFile_hpp */
