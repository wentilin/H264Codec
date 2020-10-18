//
//  CNALUnit.cpp
//  H264Codec
//
//  Created by wentilin on 2020/10/18.
//

#include "CNALUnit.hpp"

CNALUnit::CNALUnit(uint8 *pSODB, uint32 SODBLength) {
    m_pSODB = pSODB;
    m_SODBLength = SODBLength;
}

CNALUnit::~CNALUnit() {
    
}
