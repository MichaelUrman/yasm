/*
 * Semi-portable (Windows and Unix) plugin loading
 *
 *  Copyright (C) 2008  Peter Johnson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND OTHER CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR OTHER CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <util.h>

#include <string.h>

#include "libyasm-stdint.h"
#include "yasm-plugin.h"

#if defined(_MSC_VER)
#include <windows.h>
#elif defined(__GNUC__)
#include <dlfcn.h>
#endif

static void **loaded_plugins = NULL;
static int num_loaded_plugins = 0;

static void *
load_dll(const char *name, const char **perr)
{
    void *dll = NULL;
#if defined(_MSC_VER)
    static char message[512] = { 0 };
    dll = LoadLibrary(name);
    if (!dll) {
        DWORD err = GetLastError();
        if (err != 0 && FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
                                           FORMAT_MESSAGE_IGNORE_INSERTS,
                                       0, err, 0, message, 511, NULL)) {
            *perr = message;
        }
    }
#elif defined(__GNUC__)
    dll = dlopen(name, RTLD_NOW);
    if (!dll) {
        *perr = dlerror();
    }
#endif
    return dll;
}

int
load_plugin(const char *name, const char **perr)
{
    char *path;
    void *lib = NULL;
    void (*init_plugin)(void) = NULL;
    const char *err = "";

    /* Load library */

    path = yasm_xmalloc(strlen(name) + 10);
#if defined(_MSC_VER)
    strcpy(path, name);
    strcat(path, ".dll");
    lib = load_dll(path, perr);
    perr = &err; /* prefer error from above */
#elif defined(__GNUC__) || defined(__clang__)
    strcpy(path, "lib");
    strcat(path, name);
    strcat(path, ".so");
    lib = load_dll(path, perr);
    if (!lib) {
        strcpy(path, name);
        strcat(path, ".so");
        lib = load_dll(path, perr);
    }
    perr = &err; /* prefer error from above */
#endif
    yasm_xfree(path);
    if (!lib)
        lib = load_dll(name, perr);

    if (!lib)
        return 0; /* Didn't load successfully */

    /* Add to array of loaded plugins */
    loaded_plugins = yasm_xrealloc(loaded_plugins,
                                   (num_loaded_plugins + 1) * sizeof(void *));
    loaded_plugins[num_loaded_plugins] = lib;
    num_loaded_plugins++;

    /* Get yasm_init_plugin() function and run it */

#if defined(_MSC_VER)
    init_plugin =
        (void (*)(void))GetProcAddress((HINSTANCE)lib, "yasm_init_plugin");
#elif defined(__GNUC__)
    init_plugin = (void (*)(void))(uintptr_t)dlsym(lib, "yasm_init_plugin");
#endif

    if (!init_plugin)
        return 0; /* Didn't load successfully */

    init_plugin();
    return 1;
}

void
unload_plugins(void)
{
    int i;

    if (!loaded_plugins)
        return;

    for (i = 0; i < num_loaded_plugins; i++) {
#if defined(_MSC_VER)
        FreeLibrary((HINSTANCE)loaded_plugins[i]);
#elif defined(__GNUC__)
        dlclose(loaded_plugins[i]);
#endif
    }
    yasm_xfree(loaded_plugins);
    num_loaded_plugins = 0;
}
