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

#ifndef __HDMI_EDID_DATA_BLOCK_HPP__
#define __HDMI_EDID_DATA_BLOCK_HPP__

#include <stdint.h>
#include "Buffer.hpp"

class HdmiEdidDataBlock
{
public:
  enum BlockType
  {
    RESERVED = 0,
    AUDIO,
    VIDEO,
    VENDOR_SPECIFIC,
    SPEAKER_ALLOCATION,
    VESA_DISPLAY_TRANSFER_CHARACTERISTIC,
  };

  bool parseHeader(uint8_t header, BlockType& blockType, int& nLength);
  bool trimHeader(ByteBuffer& dataBlockInclHeader);
};

#endif /* __HDMI_EDID_DATA_BLOCK_HPP__ */
