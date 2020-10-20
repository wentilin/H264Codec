#include <stdio.h>
#include <assert.h>

#include "ExpColumCodec.hpp"

using namespace std;

ExpColumCodec::ExpColumCodec() {
    
}

ExpColumCodec::~ExpColumCodec() {
    
}

void ExpColumCodec::decode(UINT8 *bytes, unsigned int length, std::vector<int> &result) {
    UINT8 bytePosition = 0, bitPosition = 0;

    int codeNum = 0;
    while ((bytePosition * 8 + bitPosition) < length)
    {
        codeNum = get_uev_code_num(bytes, bytePosition, bitPosition);
        result.push_back(codeNum);
    }
}

int ExpColumCodec::get_bit_at_position(UINT8 *buf, UINT8 &bytePotion, UINT8 &bitPosition) {
    UINT8 mask = 0, val = 0;

    mask = 1 << (7 - bitPosition);
    val = ((buf[bytePotion] & mask) != 0);
    if (++bitPosition > 7)
    {
        bytePotion++;
        bitPosition = 0;
    }

    return val;
}

int ExpColumCodec::get_uev_code_num(UINT8 *buf, UINT8 &bytePotion, UINT8 &bitPosition) {
    assert(bitPosition < 8);
    UINT8 val = 0, prefixZeroCount = 0;
    int prefix = 0, surfix = 0;

    while (true)
    {
        val = get_bit_at_position(buf, bytePotion, bitPosition);
        if (val == 0)
        {
            prefixZeroCount++;
        }
        else
        {
            break;
        }
    }
    
    // [prefix] 1 [surfix]
    // codeNum = 2^LeadingZeroBits - 1 + surfix
    prefix = (1 << prefixZeroCount) - 1;
    for (size_t i = 0; i < prefixZeroCount; i++)
    {
        val = get_bit_at_position(buf, bytePotion, bitPosition);
        surfix += val * (1 << (prefixZeroCount - i - 1));
    }

    prefix += surfix;

    return prefix;
}
