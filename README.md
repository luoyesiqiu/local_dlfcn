# local_dlfcn

读取本地so文件的符号的偏移

## 用法

```cpp
#ifdef __LP64__
    const char *lib_path = "/system/lib64/libc.so";
#else
    const char *lib_path = "/system/lib/libc.so";
#endif

const char *sym_name = "open";

struct local_dlfcn_handle *handle = static_cast<local_dlfcn_handle *>(local_dlopen(lib_path));
off_t offset = local_dlsym(handle,sym_name);
local_dlclose(handle);
```

## 感谢

- [Nougat_dlfunctions](https://github.com/avs333/Nougat_dlfunctions)
- [dlfcn_compat](https://github.com/lizhangqu/dlfcn_compat)