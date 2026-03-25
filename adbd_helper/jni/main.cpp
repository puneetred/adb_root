#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
    const char* real_adbd = "/apex/com.android.adbd/bin/adbd.real";

    char* const envp[] = {
        const_cast<char*>("LD_PRELOAD=/system/lib64/libadb_root_helper.so"),
    };

    // u:r:adbd:s0 is restricted
    char* const new_argv[] = { 
        argv[0],
        const_cast<char*>("--root_seclabel=u:r:magisk:s0")
    };

    int ret = execve(real_adbd, new_argv, envp);
    
    // If we reach here, execve failed
    FILE* kmsg = fopen("/dev/kmsg", "w");
    if (kmsg) {
        fprintf(kmsg, "adb_root: execve failed: %s (%d) for path %s\n", strerror(errno), errno, real_adbd);
        fclose(kmsg);
    }
    return ret;
}