// https://docs.microsoft.com/en-us/windows/win32/direct3dtools/dx-graphics-tools-fxc-syntax

#ifndef PROFILES_H
#define PROFILES_H

#include "Parser.hpp"

namespace HLSL {

enum Profile {
    PROFILE_NONE,
    PROFILE_ps = 0,
    PROFILE_vs,
    PROFILE_cs_4_0,
    PROFILE_cs_4_1,
    PROFILE_cs_5_0,
    PROFILE_cs_5_1,
    PROFILE_ds_5_0,
    PROFILE_ds_5_1,
    PROFILE_gs_4_0,
    PROFILE_gs_4_1,
    PROFILE_gs_5_0,
    PROFILE_gs_5_1,
    PROFILE_lib_4_0,
    PROFILE_lib_4_1,
    PROFILE_lib_4_0_level_9_1,
    PROFILE_lib_4_0_level_9_1_vs_only,
    PROFILE_lib_4_0_level_9_1_ps_only,
    PROFILE_lib_4_0_level_9_3,
    PROFILE_lib_4_0_level_9_3_vs_only,
    PROFILE_lib_4_0_level_9_3_ps_only,
    PROFILE_lib_5_0,
    PROFILE_hs_5_0,
    PROFILE_hs_5_1,
    PROFILE_ps_2_0,
    PROFILE_ps_2_a,
    PROFILE_ps_2_b,
    PROFILE_ps_2_sw,
    PROFILE_ps_3_0,
    PROFILE_ps_3_sw,
    PROFILE_ps_4_0,
    PROFILE_ps_4_0_level_9_0,
    PROFILE_ps_4_0_level_9_1,
    PROFILE_ps_4_0_level_9_3,
    PROFILE_ps_4_1,
    PROFILE_ps_5_0,
    PROFILE_ps_5_1,
    PROFILE_rootsig_1_0,
    PROFILE_tx_1_0,
    PROFILE_vs_1_1,
    PROFILE_vs_2_0,
    PROFILE_vs_2_a,
    PROFILE_vs_2_sw,
    PROFILE_vs_3_0,
    PROFILE_vs_3_sw,
    PROFILE_vs_4_0,
    PROFILE_vs_4_0_level_9_0,
    PROFILE_vs_4_0_level_9_1,
    PROFILE_vs_4_0_level_9_3,
    PROFILE_vs_4_1,
    PROFILE_vs_5_0,
    PROFILE_vs_5_1
};

Profile parseProfile(Parser* parser);

}

#endif