# Hdmi Edid Short Audio Descriptor Parser

This is a parser for Hdmi Edid Short Audio Descriptor (SAD).
And the parsing result is output defined in Audio Framework's AudioFormat definition.

See https://github.com/hidenorly/audioframework

# How to use

```
$ make -j 4
$ make -j 4 test
$ bin/sadParser -s 09,7f,05
encoding:PCM_16BIT channel:1 samplingRate:32000
encoding:PCM_16BIT channel:2 samplingRate:32000
encoding:PCM_16BIT channel:1 samplingRate:44100
encoding:PCM_16BIT channel:2 samplingRate:44100
encoding:PCM_16BIT channel:1 samplingRate:48000
encoding:PCM_16BIT channel:2 samplingRate:48000
encoding:PCM_16BIT channel:1 samplingRate:88200
encoding:PCM_16BIT channel:2 samplingRate:88200
encoding:PCM_16BIT channel:1 samplingRate:96000
encoding:PCM_16BIT channel:2 samplingRate:96000
encoding:PCM_16BIT channel:1 samplingRate:176000
encoding:PCM_16BIT channel:2 samplingRate:176000
encoding:PCM_16BIT channel:1 samplingRate:192000
encoding:PCM_16BIT channel:2 samplingRate:192000
encoding:PCM_24BIT channel:1 samplingRate:32000
encoding:PCM_24BIT channel:2 samplingRate:32000
encoding:PCM_24BIT channel:1 samplingRate:44100
encoding:PCM_24BIT channel:2 samplingRate:44100
encoding:PCM_24BIT channel:1 samplingRate:48000
encoding:PCM_24BIT channel:2 samplingRate:48000
encoding:PCM_24BIT channel:1 samplingRate:88200
encoding:PCM_24BIT channel:2 samplingRate:88200
encoding:PCM_24BIT channel:1 samplingRate:96000
encoding:PCM_24BIT channel:2 samplingRate:96000
encoding:PCM_24BIT channel:1 samplingRate:176000
encoding:PCM_24BIT channel:2 samplingRate:176000
encoding:PCM_24BIT channel:1 samplingRate:192000
encoding:PCM_24BIT channel:2 samplingRate:192000
```

```
$ bin/sadParser -s 11,04,20
encoding:COMPRESSED_14 channel:1 samplingRate:48000
encoding:COMPRESSED_14 channel:2 samplingRate:48000
bitRate=256000
```

Note that COMPRESSED_14 means AudioFormat::ENCODING::COMPRESSED_AC3.


# Please note that

You may need to set LD_LIBRARY_PATH

## On Mac OS

```
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/work/audioframework/lib
```

## On Ubuntu

```
export LD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/work/audioframework/lib
```