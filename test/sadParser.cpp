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

#include "HdmiEdidSadHelper.hpp"
#include "OptParse.hpp"
#include "StringTokenizer.hpp"
#include <iostream>
#include <sstream>
#include <vector>

void dump(std::map<std::string, std::string> keyVals)
{
  for( auto& [aKey, aValue] : keyVals ){
    std::cout << aKey << " = " << aValue << std::endl;
  }
}

int main(int argc, char** argv)
{
  std::vector<OptParse::OptParseItem> options;
  options.push_back( OptParse::OptParseItem("-s", "--sad", true, "", "Specify SAD bytes (3 bytes)"));
  options.push_back( OptParse::OptParseItem("-v", "--vsdb", true, "", "Specify VSDBID,VSDB data bytes e.g. 000C03,data,data, ..."));

  OptParse optParser( argc, argv, options, std::string("Hdmi Edid Short Audio Descriptor (SAD) parser e.g. -s 00,00,00") );

  if( !optParser.values["-s"].empty() ){
    StringTokenizer token(optParser.values["-s"], ",");
    ByteBuffer aSadPacket;
    while( token.hasNext() ){
      std::stringstream ss( token.getNext() );
      int data = 0;
      ss >> std::hex >> data;
      aSadPacket.push_back( data );
    }
    std::vector<AudioFormat> formats = HdmiEdidSadHelper::getAudioFormatsFromSad( aSadPacket );
    for( auto& aFormat : formats ){
      std::cout << aFormat.toString() << std::endl;
    }
    if( ( formats.size() > 0 ) && !formats[0].isEncodingPcm() ){
      std::map<std::string, std::string> addionalCapabilities = HdmiEdidSadHelper::getAdditionalCapabilities( aSadPacket );
      dump( addionalCapabilities );
    }
  }

  if( !optParser.values["-v"].empty() ){
    StringTokenizer token(optParser.values["-v"], ",");
    ByteBuffer aVsdbPacket;
    uint32_t vsdbId = 0;
    if( token.hasNext() ){
      std::stringstream ss( token.getNext() );
      ss >> std::hex >> vsdbId;
    }
    while( token.hasNext() ){
      std::stringstream ss( token.getNext() );
      int data = 0;
      ss >> std::hex >> data;
      aVsdbPacket.push_back( data );
    }
    std::map<std::string, std::string> vsdbCapabilities = HdmiEdidSadHelper::getAdditionalCapabilitiesFromVsadb( vsdbId, aVsdbPacket );
    dump( vsdbCapabilities );
  }

  return 0;
}