//
//  CNALUnit.hpp
//  H264Codec
//
//  Created by wentilin on 2020/10/18.
//

#ifndef CNALUnit_hpp
#define CNALUnit_hpp

#include <stdio.h>
#include "Global.h"

class CNALUnit {
public:
    CNALUnit(uint8 *pSODB, uint32 SODBLength);
    ~CNALUnit();

private:
    uint8 *m_pSODB;
    uint32 m_SODBLength;
};

#endif /* CNALUnit_hpp */
