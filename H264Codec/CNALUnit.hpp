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

/* 主要unit type:
    0. Unspecified,
    1. Coded slice of non-IDR picture,
    2. Coded slice data partition A - slice_data_partition_a_layer_rbsp( )
    3. Coded slice data partition B - slice_data_partition_b_layer_rbsp( )
    4. Coded slice data partition C - slice_data_partition_c_layer_rbsp( )
    5. Coded slice of an IDR picture - slice_layer_without_partitioning_rbsp( )
    6. Supplemental enhancement information(SEI) - sei_rbsp( )
    7. Sequence parameter set(SPS) - seq_parameter_set_rbsp( )
    8. Picture parameter set(PPS) - pic_parameter_set_rbsp( )
    9. Access unit delimiter - access_unit_delimiter_rbsp( )
    10. End of sequence - end_of_seq_rbsp( )
    11. End of stream - end_of_stream_rbsp( )
    12. Filler data - filler_data_rbsp( )
    13. Sequence parameter set extension - seq_parameter_set_extension_rbsp( )
    14. Prefix NAL unit - prefix_nal_unit_rbsp( )
    15. Subset sequence parameter set - subset_seq_parameter_set_rbsp( )
    16. Depth parameter set - depth_parameter_set_rbsp( )
    ...
 */
class CNALUnit {
public:
    CNALUnit(uint8 *pSODB, uint32 SODBLength);
    ~CNALUnit();

private:
    uint8 *m_pSODB;
    uint32 m_SODBLength;
};

#endif /* CNALUnit_hpp */
