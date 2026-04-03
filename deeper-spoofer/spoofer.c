/* devkit_unlocker.c */

#include <taihen.h>
#include <string.h>
#include <psp2common/kernel/modulemgr.h>

#define NUM_HOOKS 12

static SceUID         g_hooks[NUM_HOOKS];
static tai_hook_ref_t ref_hooks[NUM_HOOKS];

static const char *devkit_int_keys[] = {
    "show_debug_info",
    "debug_screenshot",
    "debug_screenshot_format",
    "gpi_switch",
    "fake_sdslot_broken",
    "fake_no_memory_card",
    "fake_contents_max",
    "fake_free_space",
    "fake_free_space_quota",
    "idu_mode",
    "debug_ingame_commerce2",
    "debug",
    "nav_only",
    "np_ad_clock_diff",
    "np_geo_filtering",
    "test_patch",
    "trophy_setup_dialog_debug",
    "fake_plus",
    "store_start_control",
    "revocation_check_req",
    "ssl_cert_ignorable",
    "web_security_status",
    "counter",
    NULL
};

static int sceRegMgrGetKeyInt_patched(const char *category, const char *name, int *buf)
{
    int ret = TAI_CONTINUE(int, ref_hooks[0], category, name, buf);

    for (int i = 0; devkit_int_keys[i] != NULL; i++) {
        if (strcmp(name, devkit_int_keys[i]) == 0) {
            *buf = 1;
            return 0;
        }
    }

    if (strcmp(name, "fake_free_space_quota") == 0) {
        *buf = 0x7FFFFFFF;
        return 0;
    }

    return ret;
}

static int sceRegMgrGetKeyStr_patched(const char *category, const char *name, char *buf, int bufSize)
{
    int ret = TAI_CONTINUE(int, ref_hooks[1], category, name, buf, bufSize);

    if (strcmp(name, "env") == 0) {
        strncpy(buf, "np", bufSize - 1);
        buf[bufSize - 1] = '\0';
        return 0;
    }

    return ret;
}

static int sceRegMgrGetKeyBin_patched(const char *category, const char *name, void *buf, int bufSize)
{
    return TAI_CONTINUE(int, ref_hooks[2], category, name, buf, bufSize);
}

static int sceSblQafMgrIsAllowAllDebugMenuDisplay_patched(void)          { return 1; }
static int sceSblQafMgrIsAllowLimitedDebugMenuDisplay_patched(void)      { return 1; }
static int sceSblQafMgrIsAllowMinimumDebugMenuDisplay_patched(void)      { return 1; }
static int sceSblQafMgrIsAllowNpFullTest_patched(void)                   { return 1; }
static int sceSblQafMgrIsAllowNpTest_patched(void)                       { return 1; }
static int sceSblQafMgrIsAllowForceUpdate_patched(void)                  { return 1; }
static int sceSblQafMgrIsAllowScreenShotAlways_patched(void)             { return 1; }
static int sceSblQafMgrIsAllowRemoteSysmoduleLoad_patched(void)          { return 1; }
static int sceSblQafMgrIsAllowNonQAPup_patched(void)                     { return 1; }

void _start() __attribute__((weak, alias("module_start")));

int module_start(SceSize argc, const void *args)
{
    for (int i = 0; i < NUM_HOOKS; i++)
        g_hooks[i] = -1;

    g_hooks[0] = taiHookFunctionImport(&ref_hooks[0], TAI_MAIN_MODULE,
        0xC436F916, 0x16DDF3DC, sceRegMgrGetKeyInt_patched);

    g_hooks[1] = taiHookFunctionImport(&ref_hooks[1], TAI_MAIN_MODULE,
        0xC436F916, 0xE188382F, sceRegMgrGetKeyStr_patched);

    g_hooks[2] = taiHookFunctionImport(&ref_hooks[2], TAI_MAIN_MODULE,
        0xC436F916, 0x0B98D646, sceRegMgrGetKeyBin_patched);

    g_hooks[3] = taiHookFunctionImport(&ref_hooks[3], TAI_MAIN_MODULE,
        0x756B7E89, 0x66843305, sceSblQafMgrIsAllowAllDebugMenuDisplay_patched);

    g_hooks[4] = taiHookFunctionImport(&ref_hooks[4], TAI_MAIN_MODULE,
        0x756B7E89, 0xC456212D, sceSblQafMgrIsAllowLimitedDebugMenuDisplay_patched);

    g_hooks[5] = taiHookFunctionImport(&ref_hooks[5], TAI_MAIN_MODULE,
        0x756B7E89, 0xA156BBD2, sceSblQafMgrIsAllowMinimumDebugMenuDisplay_patched);

    g_hooks[6] = taiHookFunctionImport(&ref_hooks[6], TAI_MAIN_MODULE,
        0x756B7E89, 0x72168C6E, sceSblQafMgrIsAllowNpFullTest_patched);

    g_hooks[7] = taiHookFunctionImport(&ref_hooks[7], TAI_MAIN_MODULE,
        0x756B7E89, 0xA9EBCBAC, sceSblQafMgrIsAllowNpTest_patched);

    g_hooks[8] = taiHookFunctionImport(&ref_hooks[8], TAI_MAIN_MODULE,
        0x756B7E89, 0x63F29BA0, sceSblQafMgrIsAllowForceUpdate_patched);

    g_hooks[9] = taiHookFunctionImport(&ref_hooks[9], TAI_MAIN_MODULE,
        0x756B7E89, 0xD22A8731, sceSblQafMgrIsAllowScreenShotAlways_patched);

    g_hooks[10] = taiHookFunctionImport(&ref_hooks[10], TAI_MAIN_MODULE,
        0x756B7E89, 0xF45AA706, sceSblQafMgrIsAllowRemoteSysmoduleLoad_patched);

    g_hooks[11] = taiHookFunctionImport(&ref_hooks[11], TAI_MAIN_MODULE,
        0x756B7E89, 0xB5621615, sceSblQafMgrIsAllowNonQAPup_patched);

    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
    for (int i = NUM_HOOKS - 1; i >= 0; i--) {
        if (g_hooks[i] >= 0) {
            taiHookRelease(g_hooks[i], ref_hooks[i]);
            g_hooks[i] = -1;
        }
    }
    return SCE_KERNEL_STOP_SUCCESS;
}