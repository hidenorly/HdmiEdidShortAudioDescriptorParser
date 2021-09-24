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
#include "HdmiEdidPrimitive.hpp"

struct SadEncodingConversionTable
{
public:
  int sadEncoding;
  AudioFormat::ENCODING afwEncoding;

  SadEncodingConversionTable(int sadEncoding, AudioFormat::ENCODING afwEncoding) : sadEncoding(sadEncoding), afwEncoding(afwEncoding){};
};

std::vector<AudioFormat::ENCODING> HdmiEdidSadHelper::getAudioEncodingsFromSad(ByteBuffer aSadPacket)
{
  std::vector<AudioFormat::ENCODING> result;

  if( aSadPacket.size() == HDMI_EDID_SAD_LENGTH ){
    AudioFormat::ENCODING encoding = AudioFormat::ENCODING::ENCODING_DEFAULT;

    const static SadEncodingConversionTable conversionTable[]=
    {
      SadEncodingConversionTable( 1, AudioFormat::ENCODING::PCM_UNKNOWN),
      SadEncodingConversionTable( 2, AudioFormat::ENCODING::COMPRESSED_AC3),
      SadEncodingConversionTable( 3, AudioFormat::ENCODING::COMPRESSED_MP2),
      SadEncodingConversionTable( 4, AudioFormat::ENCODING::COMPRESSED_MP3),
      SadEncodingConversionTable( 5, AudioFormat::ENCODING::COMPRESSED_MP2),
      SadEncodingConversionTable( 6, AudioFormat::ENCODING::COMPRESSED_AAC),
      SadEncodingConversionTable( 7, AudioFormat::ENCODING::COMPRESSED_DTS),
      SadEncodingConversionTable( 8, AudioFormat::ENCODING::COMPRESSED_ATRAC),
      SadEncodingConversionTable( 9, AudioFormat::ENCODING::PDM_SACD),
      SadEncodingConversionTable(10, AudioFormat::ENCODING::COMPRESSED_E_AC3),
      SadEncodingConversionTable(11, AudioFormat::ENCODING::COMPRESSED_DTS_HD),
      SadEncodingConversionTable(12, AudioFormat::ENCODING::COMPRESSED_DOLBY_TRUEHD),
      SadEncodingConversionTable(13, AudioFormat::ENCODING::COMPRESSED_UNKNOWN),
      SadEncodingConversionTable(14, AudioFormat::ENCODING::COMPRESSED_WMA_PRO),
      SadEncodingConversionTable(15, AudioFormat::ENCODING::COMPRESSED_UNKNOWN),
      SadEncodingConversionTable( 0, AudioFormat::ENCODING::COMPRESSED_UNKNOWN)
    };
    int sadEncoding = ( aSadPacket[0] & HDMI_EDID_SAD_ENCODING_MASK ) >> HDMI_EDID_SAD_ENCODING_SHIFT;

    for(int i=0; (conversionTable[i].sadEncoding!=0); i++){
      if( conversionTable[i].sadEncoding == sadEncoding ){
        encoding = conversionTable[i].afwEncoding;
        break;
      }
    }

    if( ( encoding == AudioFormat::ENCODING::COMPRESSED_UNKNOWN ) && ( sadEncoding == HDMI_EDID_SAD_ENCODING_EXTENDED ) ){
      const static SadEncodingConversionTable exTable[]=
      {
        SadEncodingConversionTable( 4, AudioFormat::ENCODING::COMPRESSED_HE_AAC_V1),
        SadEncodingConversionTable( 5, AudioFormat::ENCODING::COMPRESSED_HE_AAC_V2),
        SadEncodingConversionTable( 6, AudioFormat::ENCODING::COMPRESSED_AAC_LC),
        SadEncodingConversionTable( 7, AudioFormat::ENCODING::COMPRESSED_DRA),
        SadEncodingConversionTable(12, AudioFormat::ENCODING::COMPRESSED_AC4),
        SadEncodingConversionTable( 0, AudioFormat::ENCODING::COMPRESSED_UNKNOWN)
      };
      int exEncoding = ( aSadPacket[2] & HDMI_EDID_SAD_ENCODING_EXTENDED_MASK ) >> HDMI_EDID_SAD_ENCODING_EXTENDED_SHIFT;

      for(int i=0; (exTable[i].sadEncoding!=0); i++){
        if( exTable[i].sadEncoding == exEncoding ){
          encoding = exTable[i].afwEncoding;
          break;
        }
      }
    }

    if( encoding == AudioFormat::PCM_UNKNOWN ){
      int bitDepth = aSadPacket[2] & HDMI_EDID_SAD_ENCODING_LPCM_BIT_DEPTH_MASK;
      if( bitDepth & HDMI_EDID_SAD_ENCODING_LPCM16 ){
        result.push_back( AudioFormat::ENCODING::PCM_16BIT);
      }
      if( bitDepth & HDMI_EDID_SAD_ENCODING_LPCM20 ){
        //result.push_back( AudioFormat::ENCODING::PCM_20BIT);
      }
      if( bitDepth & HDMI_EDID_SAD_ENCODING_LPCM24 ){
        result.push_back( AudioFormat::ENCODING::PCM_24BIT_PACKED);
      }
    } else {
      result.push_back( encoding );
    }
  }

  return result;
}

std::vector<AudioFormat::CHANNEL> HdmiEdidSadHelper::getAudioChannelFromSad(ByteBuffer aSadPacket)
{
  std::vector<AudioFormat::CHANNEL> result;

  if( aSadPacket.size() == HDMI_EDID_SAD_LENGTH ){
    int nChannels = (aSadPacket[0] & HDMI_EDID_SAD_CHANNEL_MASK) + 1;
    for(AudioFormat::CHANNEL i=AudioFormat::CHANNEL::CHANNEL_MONO; i<AudioFormat::CHANNEL::CHANNEL_UNKNOWN; i=AudioFormat::CHANNEL(i+1)){
      if( AudioFormat::getNumberOfChannels(i) <= nChannels ){
        result.push_back( i );
      }
    }
  }

  return result;
}

std::vector<int> HdmiEdidSadHelper::getAudioSamplingRatesFromSad(ByteBuffer aSadPacket)
{
  std::vector<int> result;

  if( aSadPacket.size() == HDMI_EDID_SAD_LENGTH ){
    int samplingRates = aSadPacket[1] & HDMI_EDID_SAD_SAMPLING_RATE_MASK;
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_32K ){ result.push_back( 32000); };
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_44K ){ result.push_back( 44100); };
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_48K ){ result.push_back( 48000); };
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_88K ){ result.push_back( 88200); };
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_96K ){ result.push_back( 96000); };
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_176K ){ result.push_back( 176000); };
    if( samplingRates & HDMI_EDID_SAD_SAMPLING_RATE_192K ){ result.push_back( 192000); };
  }

  return result;
}

std::vector<AudioFormat> HdmiEdidSadHelper::getAudioFormatsFromSad(ByteBuffer aSadPacket)
{
  std::vector<AudioFormat> result;

  std::vector<AudioFormat::ENCODING> encodings = getAudioEncodingsFromSad( aSadPacket );
  std::vector<int> samplingRates = getAudioSamplingRatesFromSad( aSadPacket);
  std::vector<AudioFormat::CHANNEL> channels = getAudioChannelFromSad( aSadPacket);

  for( AudioFormat::ENCODING anEncoding : encodings ){
    for( int aSamplingRate : samplingRates ){
      for( AudioFormat::CHANNEL aChannel : channels ){
        result.push_back( AudioFormat( anEncoding, aSamplingRate, aChannel ) );
      }
    }
  }

  return result;
}

std::map<std::string, std::string> HdmiEdidSadHelper::getAdditionalCapabilities(ByteBuffer aSadPacket)
{
  std::map<std::string, std::string> result;

  if( aSadPacket.size() == HDMI_EDID_SAD_LENGTH ){
    std::vector<AudioFormat::ENCODING> encodings = getAudioEncodingsFromSad( aSadPacket );
    if( encodings.size() == 1 ){
      AudioFormat::ENCODING theEncoding = encodings[0];
      if( !AudioFormat::isEncodingPcm( theEncoding ) ){
        // not PCM, codec specific
        switch( theEncoding ){
          case AudioFormat::ENCODING::COMPRESSED_E_AC3:
            // Thanks the info. https://www.mail-archive.com/linux-media@vger.kernel.org/msg148721.html
            result.insert_or_assign("JOC", ( aSadPacket[2] & HDMI_EDID_SAD_EXT_E_AC3_JOC ) ? "true" : "false" );
            result.insert_or_assign("JOC_DolbyAtmos", ( aSadPacket[2] & HDMI_EDID_SAD_EXT_E_AC3_ACMOD28 ) ? "true" : "false" );
            break;
          case AudioFormat::ENCODING::COMPRESSED_AAC_LC:
            result.insert_or_assign("channel_22.2ch", ( aSadPacket[2] & HDMI_EDID_SAD_EXT_AAC_LC_22CH ) ? "true" : "false" );
            break;
          default:
            result.insert_or_assign("bitRate", std::to_string( (int)aSadPacket[2] * HDMI_EDID_SAD_BIT_RATE_DIVIDER ) );
            break;
        }
      }
    }
  }

  return result;
}

bool HdmiEdidSadHelper::getAdditionalCapabilitiesFromHdmlLLCVsadb(std::map<std::string, std::string>& result, ByteBuffer& aVsadbPacket)
{
  bool bFound = false;

  struct HDMI_VSDB_LATENCY
  {
    int nOffset;
    std::string key;
    HDMI_VSDB_LATENCY(int nOffset, std::string key) : nOffset(nOffset), key(key){};
  };

  const static HDMI_VSDB_LATENCY table[] =
  {
    HDMI_VSDB_LATENCY(HDMI_EDID_VSDB_HDMI_LLC_VIDEO_LATENCY,            "videoLatency"),
    HDMI_VSDB_LATENCY(HDMI_EDID_VSDB_HDMI_LLC_AUDIO_LATENCY,            "audioLatency"),
    HDMI_VSDB_LATENCY(HDMI_EDID_VSDB_HDMI_LLC_INTERLACE_VIDEO_LATENCY,  "videoLatencyInterlace"),
    HDMI_VSDB_LATENCY(HDMI_EDID_VSDB_HDMI_LLC_INTERLACE_AUDIO_LATENCY,  "audioLatencyInterlace"),
    HDMI_VSDB_LATENCY(-1, "")
  };

  for( int i = 0, nOffSet = -1; nOffSet = table[i].nOffset, nOffSet != -1; i++ ){
    if( aVsadbPacket.size() > nOffSet ){
      result.insert_or_assign( table[i].key, std::to_string( (int)2 * ( aVsadbPacket[ nOffSet ] - 1 ) ) );
      bFound = true;
    }
  }

  return bFound;
}

std::map<std::string, std::string> HdmiEdidSadHelper::getAdditionalCapabilitiesFromVsadb(uint32_t vsadbId, ByteBuffer aVsadbPacket)
{
  std::map<std::string, std::string> result;

  switch( vsadbId ){
    case HDMI_EDID_VSDB_ID_HDMI_LLC:
      getAdditionalCapabilitiesFromHdmlLLCVsadb( result, aVsadbPacket );
      break;
    case HDMI_EDID_VSDB_ID_HDMI_FORUM:
    case HDMI_EDID_VSDB_ID_DOLBY_LAB:
    default:
      break;
  }

  return result;
}

