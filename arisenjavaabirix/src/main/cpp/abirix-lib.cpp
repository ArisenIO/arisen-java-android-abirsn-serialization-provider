
#include <jni.h>
#include <string>

#include "abirix.h"

extern "C"
{
    const char *empty = "";

    abirix_context * getContext(JNIEnv *env, jobject context_buffer) {
        if (nullptr == context_buffer) return nullptr;
        return (abirix_context *)env->GetDirectBufferAddress(context_buffer);
    }

    JNIEXPORT jstring JNICALL
    stringFromAbiRix(JNIEnv *env, jobject /* this */) {
        std::string hello = "Hello from abirix-lib!!";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT jobject JNICALL
    create(JNIEnv *env, jobject /* this */) {
        abirix_context* context = abirix_create();
        return env->NewDirectByteBuffer((void *)context, sizeof(context));
    }

    JNIEXPORT void JNICALL
    destroy(JNIEnv *env, jobject /* this */, jobject context_direct_byte_buffer) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        if (nullptr == context) return;

        abirix_destroy(context);
    }

    JNIEXPORT jstring JNICALL
    getError(JNIEnv *env, jobject /* this */, jobject context_direct_byte_buffer) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        return env->NewStringUTF(abirix_get_error(context));
    }

    JNIEXPORT jint getBinSize(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        return abirix_get_bin_size(context);
    }

    JNIEXPORT jobject getBinData(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        const char *data = abirix_get_bin_data(context);
        return (nullptr == data) ? nullptr : env->NewDirectByteBuffer((void *)data, sizeof(data));
    }

    JNIEXPORT jstring JNICALL
    getBinHex(JNIEnv *env, jobject /* this */, jobject context_direct_byte_buffer) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        const char *hex = abirix_get_bin_hex(context);

        return (nullptr == hex) ? nullptr : env->NewStringUTF(hex);
    }

    JNIEXPORT jlong JNICALL
    stringToName(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jstring str) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isCopy;
        const char *nameStr = (str == nullptr) ? nullptr : env->GetStringUTFChars(str, &isCopy);
        jlong name = abirix_string_to_name(context, nameStr);
        if (nameStr != nullptr)
            env->ReleaseStringUTFChars(str, nameStr);
        return name;
    }

    JNIEXPORT jstring JNICALL
    nameToString(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jlong name) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        const char *str = abirix_name_to_string(context, (uint64_t) name);
        return (str == nullptr) ? nullptr : env->NewStringUTF(str);
    }

    JNIEXPORT jboolean JNICALL
    setAbi(JNIEnv *env, jobject /* this */,
            jobject context_direct_byte_buffer,
            jlong contract,
            jstring abi) {
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isCopy;
        const char *abiStr = (abi == nullptr) ? nullptr : env->GetStringUTFChars(abi, &isCopy);
        abirix_bool ret = abirix_set_abi(context, contract, abiStr);
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
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isTypeCopy;
        const char *typeStr = (type == nullptr) ? nullptr : env->GetStringUTFChars(type, &isTypeCopy);
        jboolean isJsonCopy;
        const char *jsonStr = (json == nullptr) ? nullptr : env->GetStringUTFChars(json, &isJsonCopy);

        abirix_bool ret = 0;
        if (reorderable) {
            ret = abirix_json_to_bin_reorderable(context, contract, typeStr, jsonStr);
        } else {
            ret = abirix_json_to_bin(context, contract, typeStr, jsonStr);
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
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        jboolean isTypeCopy;
        const char *typeStr = (type == nullptr) ? nullptr : env->GetStringUTFChars(type, &isTypeCopy);
        jboolean isHexCopy;
        const char *hexStr = (hex == nullptr) ? nullptr : env->GetStringUTFChars(hex, &isHexCopy);

        const char *jsonStr = abirix_hex_to_json(context, contract, typeStr, hexStr);

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
        abirix_context* context = getContext(env, context_direct_byte_buffer);
        const char *typeStr = abirix_get_type_for_action(context, (uint64_t)contract, (uint64_t)action);
        return typeStr == nullptr ? nullptr : env->NewStringUTF(typeStr);
    }

    static JNINativeMethod method_table[] = {
            {"stringFromAbiRix", "()Ljava/lang/String;", (void *) stringFromAbiRix},
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

        jclass clazz = env->FindClass("one/block/arisenjavaabirixserializationprovider/AbiRixSerializationProviderImpl");
        if (NULL == clazz) {
            return JNI_ERR;
        }

        jint ret = env->RegisterNatives(clazz, method_table,
                                        sizeof(method_table) / sizeof(method_table[0]));
        return ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;
    }
}


