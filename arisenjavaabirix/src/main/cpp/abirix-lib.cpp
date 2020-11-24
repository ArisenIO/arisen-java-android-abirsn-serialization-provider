
#include <jni.h>
#include <string>

#include "ABIRSN.h"

extern "C"
{
    const char *empty = "";

    ABIRSN_context * getContext(JNIEnv *env, jobject context_buffer) {
        if (nullptr == context_buffer) return nullptr;
        return (ABIRSN_context *)env->GetDirectBufferAddress(context_buffer);
    }

    JNIEXPORT jstring JNICALL
    stringFromABIRSN(JNIEnv *env, jobject /* this */) {
        std::string hello = "Hello from ABIRSN-lib!!";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT jobject JNICALL
    create(JNIEnv *env, jobject /* this */) {
        ABIRSN_context* context = ABIRSN_create();
        return env->NewDirectByteBuffer((void *)context, sizeof(context));
    }

    JNIEXPORT void JNICALL
    destroy(JNIEnv *env, jobject /* this */, jobject context_direct_byte_buffer) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        if (nullptr == context) return;

        ABIRSN_destroy(context);
    }

    JNIEXPORT jstring JNICALL
    getError(JNIEnv *env, jobject /* this */, jobject context_direct_byte_buffer) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        return env->NewStringUTF(ABIRSN_get_error(context));
    }

    JNIEXPORT jint getBinSize(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        return ABIRSN_get_bin_size(context);
    }

    JNIEXPORT jobject getBinData(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        const char *data = ABIRSN_get_bin_data(context);
        return (nullptr == data) ? nullptr : env->NewDirectByteBuffer((void *)data, sizeof(data));
    }

    JNIEXPORT jstring JNICALL
    getBinHex(JNIEnv *env, jobject /* this */, jobject context_direct_byte_buffer) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        const char *hex = ABIRSN_get_bin_hex(context);

        return (nullptr == hex) ? nullptr : env->NewStringUTF(hex);
    }

    JNIEXPORT jlong JNICALL
    stringToName(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jstring str) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isCopy;
        const char *nameStr = (str == nullptr) ? nullptr : env->GetStringUTFChars(str, &isCopy);
        jlong name = ABIRSN_string_to_name(context, nameStr);
        if (nameStr != nullptr)
            env->ReleaseStringUTFChars(str, nameStr);
        return name;
    }

    JNIEXPORT jstring JNICALL
    nameToString(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jlong name) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        const char *str = ABIRSN_name_to_string(context, (uint64_t) name);
        return (str == nullptr) ? nullptr : env->NewStringUTF(str);
    }

    JNIEXPORT jboolean JNICALL
    setAbi(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jlong contract,
            jstring abi) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isCopy;
        const char *abiStr = (abi == nullptr) ? nullptr : env->GetStringUTFChars(abi, &isCopy);
        ABIRSN_bool ret = ABIRSN_set_abi(context, contract, abiStr);
        if (abiStr != nullptr)
            env->ReleaseStringUTFChars(abi, abiStr);
        return (jboolean)ret;
    }

    JNIEXPORT jboolean JNICALL
    jsonToBin(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jlong contract,
            jstring type,
            jstring json,
            jboolean reorderable) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isTypeCopy;
        const char *typeStr = (type == nullptr) ? nullptr : env->GetStringUTFChars(type, &isTypeCopy);
        jboolean isJsonCopy;
        const char *jsonStr = (json == nullptr) ? nullptr : env->GetStringUTFChars(json, &isJsonCopy);

        ABIRSN_bool ret = 0;
        if (reorderable) {
            ret = ABIRSN_json_to_bin_reorderable(context, contract, typeStr, jsonStr);
        } else {
            ret = ABIRSN_json_to_bin(context, contract, typeStr, jsonStr);
        }
        if (typeStr != nullptr)
            env->ReleaseStringUTFChars(type, typeStr);
        if (jsonStr != nullptr)
            env->ReleaseStringUTFChars(json, jsonStr);
        return (jboolean)ret;
    }

    JNIEXPORT jstring JNICALL
    hexToJson(JNIEnv *env, jobject /* this */,
              jobject context_direct_byte_buffer,
              jlong contract,
              jstring type,
              jstring hex) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isTypeCopy;
        const char *typeStr = (type == nullptr) ? nullptr : env->GetStringUTFChars(type, &isTypeCopy);
        jboolean isHexCopy;
        const char *hexStr = (hex == nullptr) ? nullptr : env->GetStringUTFChars(hex, &isHexCopy);

        const char *jsonStr = ABIRSN_hex_to_json(context, contract, typeStr, hexStr);

        if (typeStr != nullptr)
            env->ReleaseStringUTFChars(type, typeStr);
        if (hexStr != nullptr)
            env->ReleaseStringUTFChars(hex, hexStr);

        return jsonStr == nullptr ? nullptr : env->NewStringUTF(jsonStr);
    }

    JNIEXPORT jstring JNICALL
    getTypeForAction(JNIEnv *env, jobject /* this */,
              jobject context_direct_byte_buffer,
              jlong contract,
              jlong action) {
        ABIRSN_context* context = getContext(env, context_direct_byte_buffer);
        const char *typeStr = ABIRSN_get_type_for_action(context, (uint64_t)contract, (uint64_t)action);
        return typeStr == nullptr ? nullptr : env->NewStringUTF(typeStr);
    }

    static JNINativeMethod method_table[] = {
            {"stringFromABIRSN", "()Ljava/lang/String;", (void *) stringFromABIRSN},
            {"create", "()Ljava/nio/ByteBuffer;", (void *) create},
            {"destroy", "(Ljava/nio/ByteBuffer;)V", (void *) destroy},
            {"getError", "(Ljava/nio/ByteBuffer;)Ljava/lang/String;", (void *) getError},
            {"getBinSize", "(Ljava/nio/ByteBuffer;)I", (void *) getBinSize},
            {"getBinData", "(Ljava/nio/ByteBuffer;)Ljava/nio/ByteBuffer;", (void *) getBinData},
            {"getBinHex", "(Ljava/nio/ByteBuffer;)Ljava/lang/String;", (void *) getBinHex},
            {"stringToName", "(Ljava/nio/ByteBuffer;Ljava/lang/String;)J", (void *) stringToName},
            {"nameToString", "(Ljava/nio/ByteBuffer;J)Ljava/lang/String;", (void *) nameToString},
            {"setAbi", "(Ljava/nio/ByteBuffer;JLjava/lang/String;)Z", (void *) setAbi},
            {"jsonToBin", "(Ljava/nio/ByteBuffer;JLjava/lang/String;Ljava/lang/String;Z)Z", (void *) jsonToBin},
            {"hexToJson", "(Ljava/nio/ByteBuffer;JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void *) hexToJson},
            {"getTypeForAction", "(Ljava/nio/ByteBuffer;JJ)Ljava/lang/String;", (void *) getTypeForAction }
    };

    JNIEXPORT jint JNICALL
    JNI_OnLoad(JavaVM *vm, void *reserved) {

        JNIEnv *env;
        if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
            return JNI_ERR;
        }

        jclass clazz = env->FindClass("one/block/arisenjavaABIRSNserializationprovider/ABIRSNSerializationProviderImpl");
        if (NULL == clazz) {
            return JNI_ERR;
        }

        jint ret = env->RegisterNatives(clazz, method_table,
                                        sizeof(method_table) / sizeof(method_table[0]));
        return ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;
    }
}


