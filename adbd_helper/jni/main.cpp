#include <unistd.h>

#include <stdlib.h>

int main(int argc, char** argv) {
    const char* real_adbd = "/apex/com.android.adbd/bin/adbd.real";

    setenv("LD_PRELOAD", "/system/lib64/libadb_root_helper.so", 1);

    // u:r:adbd:s0 is restricted
    char* const new_argv[] = { 
        argv[0],
        const_cast<char*>("--root_seclabel=u:r:magisk:s0"),
        nullptr
    };

    return execv(real_adbd, new_argv);
}