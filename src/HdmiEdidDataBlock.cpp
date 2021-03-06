/*
  Copyright (C) 2021 hidenorly

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "HdmiEdidDataBlock.hpp"
#include "HdmiEdidPrimitive.hpp"

bool HdmiEdidDataBlock::parseHeader(uint8_t header, HdmiEdidDataBlock::BlockType& blockType, int& nLength)
{
  blockType = (HdmiEdidDataBlock::BlockType)( ( header & HDMI_EDID_DATA_BLOCK_TYPE ) >> HDMI_EDID_DATA_BLOCK_TYPE_SHIFT );
  nLength = ( header & HDMI_EDID_DATA_BLOCK_SIZE );

  return blockType == HdmiEdidDataBlock::BlockType::RESERVED ? false : true;
}


bool HdmiEdidDataBlock::trimHeader(ByteBuffer& dataBlockInclHeader)
{
  bool result = false;

  if( !dataBlockInclHeader.empty() ){
    BlockType blockType = BlockType::RESERVED;
    int nDataLength = 0;

    result = parseHeader( dataBlockInclHeader[0], blockType, nDataLength );
    if( result ){
      if( dataBlockInclHeader.size() >= ( nDataLength + 1 ) ){ // header size is 1 byte
        dataBlockInclHeader.erase( dataBlockInclHeader.begin() + 0 ); // offset 0 is header
        dataBlockInclHeader.resize( nDataLength ); // data is removed from last if size exceed as C++17 spec.
      }
    }
  }

  return result;
}
