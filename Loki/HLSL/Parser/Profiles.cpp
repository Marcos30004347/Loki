#include "Profiles.hpp"
#include "Lib/String.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace HLSL {

Profile parseProfile(Parser* parser) {
    Profile prof = Profile::PROFILE_NONE;

    if(strcmp(parser->currentToken()->value, "ps") == 0) prof = Profile::PROFILE_ps;
    if(strcmp(parser->currentToken()->value, "vs") == 0) prof = Profile::PROFILE_vs;
    if(strcmp(parser->currentToken()->value, "cs_4_0") == 0) prof = Profile::PROFILE_cs_4_0;
    if(strcmp(parser->currentToken()->value, "cs_4_1") == 0) prof = Profile::PROFILE_cs_4_1;
    if(strcmp(parser->currentToken()->value, "cs_5_0") == 0) prof = Profile::PROFILE_cs_5_0;
    if(strcmp(parser->currentToken()->value, "cs_5_1") == 0) prof = Profile::PROFILE_cs_5_1;
    if(strcmp(parser->currentToken()->value, "ds_5_0") == 0) prof = Profile::PROFILE_ds_5_0;
    if(strcmp(parser->currentToken()->value, "ds_5_1") == 0) prof = Profile::PROFILE_ds_5_1;
    if(strcmp(parser->currentToken()->value, "gs_4_0") == 0) prof = Profile::PROFILE_gs_4_0;
    if(strcmp(parser->currentToken()->value, "gs_4_1") == 0) prof = Profile::PROFILE_gs_4_1;
    if(strcmp(parser->currentToken()->value, "gs_5_0") == 0) prof = Profile::PROFILE_gs_5_0;
    if(strcmp(parser->currentToken()->value, "gs_5_1") == 0) prof = Profile::PROFILE_gs_5_1;
    if(strcmp(parser->currentToken()->value, "lib_4_0") == 0) prof = Profile::PROFILE_lib_4_0;
    if(strcmp(parser->currentToken()->value, "lib_4_1") == 0) prof = Profile::PROFILE_lib_4_1;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_1") == 0) prof = Profile::PROFILE_lib_4_0_level_9_1;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_1_vs_only") == 0) prof = Profile::PROFILE_lib_4_0_level_9_1_vs_only;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_1_ps_only") == 0) prof = Profile::PROFILE_lib_4_0_level_9_1_ps_only;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_3") == 0) prof = Profile::PROFILE_lib_4_0_level_9_3;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_3_vs_only") == 0) prof = Profile::PROFILE_lib_4_0_level_9_3_vs_only;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_3_ps_only") == 0) prof = Profile::PROFILE_lib_4_0_level_9_3_ps_only;
    if(strcmp(parser->currentToken()->value, "lib_5_0") == 0) prof = Profile::PROFILE_lib_5_0;
    if(strcmp(parser->currentToken()->value, "hs_5_0") == 0) prof = Profile::PROFILE_hs_5_0;
    if(strcmp(parser->currentToken()->value, "hs_5_1") == 0) prof = Profile::PROFILE_hs_5_1;
    if(strcmp(parser->currentToken()->value, "ps_2_0") == 0) prof = Profile::PROFILE_ps_2_0;
    if(strcmp(parser->currentToken()->value, "ps_2_a") == 0) prof = Profile::PROFILE_ps_2_a;
    if(strcmp(parser->currentToken()->value, "ps_2_b") == 0) prof = Profile::PROFILE_ps_2_b;
    if(strcmp(parser->currentToken()->value, "ps_2_sw") == 0) prof = Profile::PROFILE_ps_2_sw;
    if(strcmp(parser->currentToken()->value, "ps_3_0") == 0) prof = Profile::PROFILE_ps_3_0;
    if(strcmp(parser->currentToken()->value, "ps_3_sw") == 0) prof = Profile::PROFILE_ps_3_sw;
    if(strcmp(parser->currentToken()->value, "ps_4_0") == 0) prof = Profile::PROFILE_ps_4_0;
    if(strcmp(parser->currentToken()->value, "ps_4_0_level_9_0") == 0) prof = Profile::PROFILE_ps_4_0_level_9_0;
    if(strcmp(parser->currentToken()->value, "ps_4_0_level_9_1") == 0) prof = Profile::PROFILE_ps_4_0_level_9_1;
    if(strcmp(parser->currentToken()->value, "ps_4_0_level_9_3") == 0) prof = Profile::PROFILE_ps_4_0_level_9_3;
    if(strcmp(parser->currentToken()->value, "ps_4_1") == 0) prof = Profile::PROFILE_ps_4_1;
    if(strcmp(parser->currentToken()->value, "ps_5_0") == 0) prof = Profile::PROFILE_ps_5_0;
    if(strcmp(parser->currentToken()->value, "ps_5_1") == 0) prof = Profile::PROFILE_ps_5_1;
    if(strcmp(parser->currentToken()->value, "rootsig_1_0") == 0) prof = Profile::PROFILE_rootsig_1_0;
    if(strcmp(parser->currentToken()->value, "tx_1_0") == 0) prof = Profile::PROFILE_tx_1_0;
    if(strcmp(parser->currentToken()->value, "vs_1_1") == 0) prof = Profile::PROFILE_vs_1_1;
    if(strcmp(parser->currentToken()->value, "vs_2_0") == 0) prof = Profile::PROFILE_vs_2_0;
    if(strcmp(parser->currentToken()->value, "vs_2_a") == 0) prof = Profile::PROFILE_vs_2_a;
    if(strcmp(parser->currentToken()->value, "vs_2_sw") == 0) prof = Profile::PROFILE_vs_2_sw;
    if(strcmp(parser->currentToken()->value, "vs_3_0") == 0) prof = Profile::PROFILE_vs_3_0;
    if(strcmp(parser->currentToken()->value, "vs_3_sw") == 0) prof = Profile::PROFILE_vs_3_sw;
    if(strcmp(parser->currentToken()->value, "vs_4_0") == 0) prof = Profile::PROFILE_vs_4_0;
    if(strcmp(parser->currentToken()->value, "vs_4_0_level_9_0") == 0) prof = Profile::PROFILE_vs_4_0_level_9_0;
    if(strcmp(parser->currentToken()->value, "vs_4_0_level_9_1") == 0) prof = Profile::PROFILE_vs_4_0_level_9_1;
    if(strcmp(parser->currentToken()->value, "vs_4_0_level_9_3") == 0) prof = Profile::PROFILE_vs_4_0_level_9_3;
    if(strcmp(parser->currentToken()->value, "vs_4_1") == 0) prof = Profile::PROFILE_vs_4_1;
    if(strcmp(parser->currentToken()->value, "vs_5_0") == 0) prof = Profile::PROFILE_vs_5_0;
    if(strcmp(parser->currentToken()->value, "vs_5_1") == 0) prof = Profile::PROFILE_vs_5_1;

    if(prof != Profile::PROFILE_NONE) parser->readToken(Token::TOKEN_IDENTIFIER);

    return prof;
}
const char* profileToString(Profile profile) {
    switch(profile) {
        case Profile::PROFILE_ps:
            return "ps";
        case Profile::PROFILE_vs:
            return "vs";
        case Profile::PROFILE_cs_4_0:
            return "cs_4_0";
        case Profile::PROFILE_cs_4_1:
            return "cs_4_1";
        case Profile::PROFILE_cs_5_0:
            return "cs_5_0";
        case Profile::PROFILE_cs_5_1:
            return "cs_5_1";
        case Profile::PROFILE_ds_5_0:
            return "ds_5_0";
        case Profile::PROFILE_ds_5_1:
            return "ds_5_1";
        case Profile::PROFILE_gs_4_0:
            return "gs_4_0";
        case Profile::PROFILE_gs_4_1:
            return "gs_4_1";
        case Profile::PROFILE_gs_5_0:
            return "gs_5_0";
        case Profile::PROFILE_gs_5_1:
            return "gs_5_1";
        case Profile::PROFILE_lib_4_0:
            return "lib_4_0";
        case Profile::PROFILE_lib_4_1:
            return "lib_4_1";
        case Profile::PROFILE_lib_4_0_level_9_1:
            return "lib_4_0_level_9_1";
        case Profile::PROFILE_lib_4_0_level_9_1_vs_only:
            return "lib_4_0_level_9_1_vs_only";
        case Profile::PROFILE_lib_4_0_level_9_1_ps_only:
            return "lib_4_0_level_9_1_ps_only";
        case Profile::PROFILE_lib_4_0_level_9_3:
            return "lib_4_0_level_9_3";
        case Profile::PROFILE_lib_4_0_level_9_3_vs_only:
            return "lib_4_0_level_9_3_vs_only";
        case Profile::PROFILE_lib_4_0_level_9_3_ps_only:
            return "lib_4_0_level_9_3_ps_only";
        case Profile::PROFILE_lib_5_0:
            return "lib_5_0";
        case Profile::PROFILE_hs_5_0:
            return "hs_5_0";
        case Profile::PROFILE_hs_5_1:
            return "hs_5_1";
        case Profile::PROFILE_ps_2_0:
            return "ps_2_0";
        case Profile::PROFILE_ps_2_a:
            return "ps_2_a";
        case Profile::PROFILE_ps_2_b:
            return "ps_2_b";
        case Profile::PROFILE_ps_2_sw:
            return "ps_2_sw";
        case Profile::PROFILE_ps_3_0:
            return "ps_3_0";
        case Profile::PROFILE_ps_3_sw:
            return "ps_3_sw";
        case Profile::PROFILE_ps_4_0:
            return "ps_4_0";
        case Profile::PROFILE_ps_4_0_level_9_0:
            return "ps_4_0_level_9_0";
        case Profile::PROFILE_ps_4_0_level_9_1:
            return "ps_4_0_level_9_1";
        case Profile::PROFILE_ps_4_0_level_9_3:
            return "ps_4_0_level_9_3";
        case Profile::PROFILE_ps_4_1:
            return "ps_4_1";
        case Profile::PROFILE_ps_5_0:
            return "ps_5_0";
        case Profile::PROFILE_ps_5_1:
            return "ps_5_1";
        case Profile::PROFILE_rootsig_1_0:
            return "rootsig_1_0";
        case Profile::PROFILE_tx_1_0:
            return "tx_1_0";
        case Profile::PROFILE_vs_1_1:
            return "vs_1_1";
        case Profile::PROFILE_vs_2_0:
            return "vs_2_0";
        case Profile::PROFILE_vs_2_a:
            return "vs_2_a";
        case Profile::PROFILE_vs_2_sw:
            return "vs_2_sw";
        case Profile::PROFILE_vs_3_0:
            return "vs_3_0";
        case Profile::PROFILE_vs_3_sw:
            return "vs_3_sw";
        case Profile::PROFILE_vs_4_0:
            return "vs_4_0";
        case Profile::PROFILE_vs_4_0_level_9_0:
            return "vs_4_0_level_9_0";
        case Profile::PROFILE_vs_4_0_level_9_1:
            return "vs_4_0_level_9_1";
        case Profile::PROFILE_vs_4_0_level_9_3:
            return "vs_4_0_level_9_3";
        case Profile::PROFILE_vs_4_1:
            return "vs_4_1";
        case Profile::PROFILE_vs_5_0:
            return "vs_5_0";
        case Profile::PROFILE_vs_5_1:        
            return "vs_5_1";
        }

    return nullptr;
}


}