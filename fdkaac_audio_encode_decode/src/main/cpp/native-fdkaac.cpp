//
// Created by 阳坤 on 2020-06-02.
//
#include <jni.h>

#define ENCODE_NATIVE_CLASS "com/devyk/fdkaac_audio_encode/FDKAACEncode"
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))


#include "encode/AACEncoder.h"

AACEncoder *mAACEncode = 0;

static jint Android_JNI_init(JNIEnv *jniEnv, jobject jobje, jint bitRate, jint channels, jint sampleRate) {
    if (!mAACEncode)
        mAACEncode = new AACEncoder();


    AACProfile profile = LC_AAC;
    mAACEncode->init(profile, sampleRate,channels, bitRate);

    return 1;

}

static void Android_JNI_encode(JNIEnv *jniEnv, jobject jobje, jbyteArray byteArray, jint size) {
    jbyte *pcm = jniEnv->GetByteArrayElements(byteArray, 0);
    char *outBuffer = 0;
    if (mAACEncode)
        mAACEncode->encode((Byte *) (pcm), size, &outBuffer);
    jniEnv->ReleaseByteArrayElements(byteArray, pcm, 0);

}

static void Android_JNI_destory() {
    if (mAACEncode) {
        mAACEncode->destory();
        delete mAACEncode;
        mAACEncode = 0;
    }

}


/**
 * 编码对应的 native 函数，用于动态注册
 */
static JNINativeMethod ENCODER_NATIVE_METHOD[] = {
        //native 函数-------签名-------对象的函数
        {"init",    "(III)I", (void *) Android_JNI_init},
        {"encode",  "([BI)V", (void *) Android_JNI_encode},
        {"destory", "()V",    (void *) Android_JNI_destory}
};

/**
 * System.loadLibrary 会执行
 * @param javaVM
 * @param pVoid
 * @return
 */
jint JNI_OnLoad(JavaVM *javaVM, void *pVoid) {
    JNIEnv *jniEnv;
    if (javaVM->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    jclass enClass = jniEnv->FindClass(ENCODE_NATIVE_CLASS);
    jniEnv->RegisterNatives(enClass, ENCODER_NATIVE_METHOD, NELEM(ENCODER_NATIVE_METHOD));
    jniEnv->DeleteLocalRef(enClass);
    return JNI_VERSION_1_6;
}
