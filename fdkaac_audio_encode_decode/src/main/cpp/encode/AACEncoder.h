//
// Created by 阳坤 on 2020-06-02.
//

#ifndef AVSAMPLE_AACENCODER_H
#define AVSAMPLE_AACENCODER_H


#include <aacenc_lib.h>

#include <android/log.h>
#include "stdio.h"


#include <sys/time.h>
#include <android/log.h>
#include <zconf.h>

#define LOG_TAG "encode"
#ifdef __ANDROID__
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#elif defined(__APPLE__)    // IOS or OSX
#define LOGI(...)  printf("  ");printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#define LOGE(...)  printf(" Error: ");printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#endif

static inline long long currentTimeMills() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long) tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


/**
 * 定义 AAC 编码格式
 * LC-AAC:应用于中高码率场景的编码 （>= 80Kbit/s）
 * HE-AAC:主要应用于中低码率场景的编码 (<= 80kit/s)
 * HE-V2-AAC: 主要应用于低码率场景的编码 (<= 48Kbit/s)
 */
typedef enum {
    LC_AAC = 2,
    HE_AAC = 5,
    LC_v2_AAC = 29,
} AACProfile;


class AACEncoder {
private:
    HANDLE_AACENCODER mAacencoder;
    AACENC_InfoStruct mEncInfo = {0};
    uint8_t *mInBuffer = 0;
    int mInBufferCursor;
    int mInputSizeFixed;
    uint8_t mAacOutbuf[20480];
    /**
     * 设置编码出来的 AAC 是否带 ADTS
     */
    bool isFlagGlobalHeader = true;

    FILE *aacFile = 0;

public:
    AACEncoder();

    ~AACEncoder();

    int init(AACProfile profile, int sampleRate, int channels, int bitRate);

    int encode(Byte *pData, int dataByteSize, char **outBuffer);

    void destory();

    int fdkEncodeAudio();


    void addADTS2Packet(uint8_t *packet,int packetLen);

    void writeAACPacketToFile(uint8_t *string, int i);
};


#endif //AVSAMPLE_AACENCODER_H
