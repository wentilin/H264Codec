//
//  ExpColumCodec.hpp
//  H264Codec
//
//  Created by linwenhu on 2020/10/20.
//

#ifndef ExpColumCodec_hpp
#define ExpColumCodec_hpp

#include <vector>

typedef unsigned char UINT8;

class ExpColumCodec {
public:
    ExpColumCodec();
    ~ExpColumCodec();
    
    void decode(UINT8 *bytes, unsigned int length, std::vector<int> &result);
    
private:
    int get_bit_at_position(UINT8 *buf, UINT8 &bytePotion, UINT8 &bitPosition);
    int get_uev_code_num(UINT8 *buf, UINT8 &bytePotion, UINT8 &bitPosition);
};

void test();

#endif /* ExpColumCodec_hpp */
