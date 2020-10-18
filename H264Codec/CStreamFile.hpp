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
