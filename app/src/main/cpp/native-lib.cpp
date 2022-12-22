#include <jni.h>
#include <string>
#include "dlfcn/local_dlfcn.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_luoye_localdlfcn_MainActivity_test(
        JNIEnv* env,
        jobject /* this */) {

#ifdef __LP64__
    const char *lib_path = "/system/lib64/libc.so";
#else
    const char *lib_path = "/system/lib/libc.so";
#endif

    const char *sym_name = "open";

    struct local_dlfcn_handle *handle = static_cast<local_dlfcn_handle *>(local_dlopen(lib_path));

    off_t offset = local_dlsym(handle,sym_name);

    local_dlclose(handle);

    char text[128] = {0};
    snprintf(text,128,"Found symbol \"%s\" at 0x%lx.",sym_name,offset);

    return env->NewStringUTF(text);
}