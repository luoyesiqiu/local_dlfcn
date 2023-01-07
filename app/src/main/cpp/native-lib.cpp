#include <jni.h>
#include <string>
#include <dlfcn.h>
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
#define CMP_COUNT 8
    const char *sym_name = "open";

    struct local_dlfcn_handle *handle = static_cast<local_dlfcn_handle *>(local_dlopen(lib_path));

    off_t offset = local_dlsym(handle,sym_name);

    FILE *fp = fopen(lib_path,"rb");
    char file_bytes[CMP_COUNT] = {0};
    if(fp != NULL){
        fseek(fp,offset,SEEK_SET);
        fread(file_bytes,1,CMP_COUNT,fp);
        fclose(fp);
    }

    void *dl_handle = dlopen(lib_path,RTLD_NOW);
    void *sym = dlsym(dl_handle,sym_name);

    int is_hook = memcmp(file_bytes,sym,CMP_COUNT) != 0;

    local_dlclose(handle);
    dlclose(dl_handle);

    char text[128] = {0};
    snprintf(text,128,"Function \"%s\" is hook: %s",sym_name,is_hook ? "true" : "false");

    return env->NewStringUTF(text);
}