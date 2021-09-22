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

#ifndef __HDMI_EDID_SAD_PRIMITIVE_HPP__
#define __HDMI_EDID_SAD_PRIMITIVE_HPP__

#define HDMI_EDID_SAD_LENGTH  3
#define BIT0 (1)
#define BIT1 (2)
#define BIT2 (4)
#define BIT3 (8)
#define BIT4 (16)
#define BIT5 (32)
#define BIT6 (64)
#define BIT7 (128)

#define HDMI_EDID_SAD_ENCODING_MASK (BIT3 | BIT4 | BIT5 | BIT6)
#define HDMI_EDID_SAD_ENCODING_SHIFT (3)
#define HDMI_EDID_SAD_ENCODING_LPCM_BIT_DEPTH_MASK (BIT0 | BIT1 | BIT2)
#define HDMI_EDID_SAD_ENCODING_LPCM16 (BIT0)
#define HDMI_EDID_SAD_ENCODING_LPCM20 (BIT1)
#define HDMI_EDID_SAD_ENCODING_LPCM24 (BIT2)
#define HDMI_EDID_SAD_ENCODING_EXTENDED (15)
#define HDMI_EDID_SAD_ENCODING_EXTENDED_MASK (BIT7 | BIT6 | BIT5 | BIT4 | BIT3)
#define HDMI_EDID_SAD_ENCODING_EXTENDED_SHIFT (3)

#define HDMI_EDID_SAD_CHANNEL_MASK (BIT2 | BIT1 | BIT0)

#define HDMI_EDID_SAD_SAMPLING_RATE_MASK (BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
#define HDMI_EDID_SAD_SAMPLING_RATE_32K (BIT0)
#define HDMI_EDID_SAD_SAMPLING_RATE_44K (BIT1)
#define HDMI_EDID_SAD_SAMPLING_RATE_48K (BIT2)
#define HDMI_EDID_SAD_SAMPLING_RATE_88K (BIT3)
#define HDMI_EDID_SAD_SAMPLING_RATE_96K (BIT4)
#define HDMI_EDID_SAD_SAMPLING_RATE_176K (BIT5)
#define HDMI_EDID_SAD_SAMPLING_RATE_192K (BIT6)

#define HDMI_EDID_SAD_BIT_RATE_DIVIDER (8000)

#define HDMI_EDID_SAD_EXT_E_AC3_JOC (1)
#define HDMI_EDID_SAD_EXT_E_AC3_ACMOD28 (2)
#define HDMI_EDID_SAD_EXT_AAC_LC_22CH (1)

#define HDMI_EDID_VSDB_ID_HDMI_LLC   0x000C03
#define HDMI_EDID_VSDB_HDMI_LLC_VIDEO_LATENCY (8)
#define HDMI_EDID_VSDB_HDMI_LLC_AUDIO_LATENCY (9)
#define HDMI_EDID_VSDB_HDMI_LLC_INTERLACE_VIDEO_LATENCY (10)
#define HDMI_EDID_VSDB_HDMI_LLC_INTERLACE_AUDIO_LATENCY (11)
#define HDMI_EDID_VSDB_ID_HDMI_FORUM 0xC45DD8
#define HDMI_EDID_VSDB_ID_DOLBY_LAB  0x00D046

#define HDMI_EDID_DATA_BLOCK_TYPE (BIT7 | BIT6 | BIT5)
#define HDMI_EDID_DATA_BLOCK_TYPE_SHIFT (5)
#define HDMI_EDID_DATA_BLOCK_SIZE (BIT4 | BIT3 | BIT2 | BIT1 | BIT0)

#endif /* __HDMI_EDID_SAD_PRIMITIVE_HPP__ */
