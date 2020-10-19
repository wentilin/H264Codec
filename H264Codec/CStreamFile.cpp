//
//  CStreamFile.cpp
//  H264Codec
//
//  Created by wentilin on 2020/10/18.
//

#include "CStreamFile.hpp"
#include "CNALUnit.hpp"

#include <iostream>

using namespace std;

CStreamFile::CStreamFile(char *fileName) {
    m_fileName = fileName;
    m_inputFile = fopen(m_fileName, "rb");
    if (!m_inputFile) {
        file_error(0);
    }
}

CStreamFile::~CStreamFile() {
    if (m_inputFile) {
        fclose(m_inputFile);
    }
}

void CStreamFile::file_info() {
    if (m_fileName) {
        cout << L"File name:" << m_fileName << endl;
    }
}

void CStreamFile::file_error(int idx) {
    switch (idx) {
        case 0:
            cout << L"Error: opening input file failed." << endl;
            break;
        default:
            break;
    }
}

int CStreamFile::Parse_h264_bitstream() {
    int ret = 0;
    do {
        ret = find_nal_prefix();
        // 解析NAL unit
        if (m_nalVec.size()) {
            uint8 nalType = m_nalVec[0] & 0x1F;
            cout << "NAL Unit Type: " << +nalType << endl;
            
            ebsp_to_sodb();
            CNALUnit nalUnit(&m_nalVec[1], m_nalVec.size()-1);
            
        }
    } while (ret);
    
    return 0;
}

int CStreamFile::find_nal_prefix() {
    // 00 00 00 01 xxxxx 00 00 00 01
    uint8 prefix[3] = { 0 };
    uint8 fileByte;
    
    m_nalVec.clear();
    
    int pos = 0, getPrefx = 0;
    for (int i = 0; i < 3; i++) {
        prefix[i] = getc(m_inputFile);
        m_nalVec.push_back(prefix[i]);
    }
    
    while (!feof(m_inputFile)) {
        if (prefix[pos % 3] == 0 &&
            prefix[(pos + 1) % 3] == 0 &&
            prefix[(pos + 2) % 3] == 1) {
            getPrefx = 1;
            m_nalVec.pop_back();
            m_nalVec.pop_back();
            m_nalVec.pop_back();
            break;
        } else if (prefix[pos % 3] == 0 &&
                   prefix[(pos + 1) % 3] == 0 &&
                   prefix[(pos + 2) % 3] == 0) {
            if (1 == getc(m_inputFile)) {
                // 0x00 00 00 01
                getPrefx = 2;
                m_nalVec.pop_back();
                m_nalVec.pop_back();
                m_nalVec.pop_back();
                break;
            }
        } else {
            fileByte = getc(m_inputFile);
            prefix[pos++ % 3] = fileByte;
            m_nalVec.push_back(fileByte);
        }
    }
    
    return getPrefx;
}

void CStreamFile::ebsp_to_sodb() {
    // 00 00 xxx 03
    if (m_nalVec.size() < 3) {
        return;
    }
    
    for (vector<uint8>::iterator itor = m_nalVec.begin() + 2; itor != m_nalVec.end();) {
        if (3 == *itor && 0 == *(itor-1) && 0 == *(itor-2)) {
            vector<uint8>::iterator temp = m_nalVec.erase(itor);
            itor = temp;
        } else {
            itor++;
        }
    }
}
