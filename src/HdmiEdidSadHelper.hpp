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

#ifndef __HDMI_EDID_SAD_HELPER_HPP__
#define __HDMI_EDID_SAD_HELPER_HPP__

#include "AudioFormat.hpp"
#include "Buffer.hpp"
#include <vector>

class HdmiEdidSadHelper
{
public:
  static std::vector<AudioFormat::ENCODING> getAudioEncodingsFromSad(ByteBuffer aSadPacket);
  static std::vector<AudioFormat::CHANNEL> getAudioChannelFromSad(ByteBuffer aSadPacket);
  static std::vector<int> getAudioSamplingRatesFromSad(ByteBuffer aSadPacket);
  static std::vector<AudioFormat> getAudioFormatsFromSad(ByteBuffer aSadPacket);
};

#endif /* __HDMI_EDID_SAD_HELPER_HPP__ */
