#include <jni.h>
#include <string>

// 指定要注册的类
#define JNIREG_CLASS "com/example/jnilibrary/JniUtils"

// 指定代码所在的段。在编译时，把该函数编译到自定义的section里。
// 由于在java层没有定义该函数，因此需要写到一个自定义的section里。
extern "C"
__attribute__((section(".mysection"))) JNICALL jstring getStr1(JNIEnv *env, jobject obj) {
    return env->NewStringUTF("Hello from C++");
}

extern "C"
__attribute__((section(".mysection"))) JNICALL jint getInt1(JNIEnv *env, jobject obj, jint count) {
    return (count + 1);
}

// 第一个参数：Java层的方法名
// 第二个参数：方法的签名，括号内为参数类型，后面为返回类型
// 第三个参数：需要重新注册的方法名
static JNINativeMethod getMethods[] = {
        {"stringFromJNI",  "()Ljava/lang/String;", (void *) getStr1},
        {"calculateByJNI", "(I)I",                 (void *) getInt1}
};

extern "C"
int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *getMethods,
                          int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, getMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C"
int registerNatives(JNIEnv *env) {
    if (!registerNativeMethods(env, JNIREG_CLASS, getMethods,
                               sizeof(getMethods) / sizeof(getMethods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C"
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    if (!registerNatives(env)) {
        return -1;
    }
    return JNI_VERSION_1_6;
}