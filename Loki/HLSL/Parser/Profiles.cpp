#include "Profiles.hpp"
#include "Lib/String.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace HLSL {

Profile parseProfile(Parser* parser) {
    Profile prof = Profile::PROFILE_NONE;
    if(strcmp(parser->currentToken()->value, "ps")) prof = Profile::PROFILE_ps;
    if(strcmp(parser->currentToken()->value, "vs")) prof = Profile::PROFILE_vs;
    if(strcmp(parser->currentToken()->value, "cs_4_0")) prof = Profile::PROFILE_cs_4_0;
    if(strcmp(parser->currentToken()->value, "cs_4_1")) prof = Profile::PROFILE_cs_4_1;
    if(strcmp(parser->currentToken()->value, "cs_5_0")) prof = Profile::PROFILE_cs_5_0;
    if(strcmp(parser->currentToken()->value, "cs_5_1")) prof = Profile::PROFILE_cs_5_1;
    if(strcmp(parser->currentToken()->value, "ds_5_0")) prof = Profile::PROFILE_ds_5_0;
    if(strcmp(parser->currentToken()->value, "ds_5_1")) prof = Profile::PROFILE_ds_5_1;
    if(strcmp(parser->currentToken()->value, "gs_4_0")) prof = Profile::PROFILE_gs_4_0;
    if(strcmp(parser->currentToken()->value, "gs_4_1")) prof = Profile::PROFILE_gs_4_1;
    if(strcmp(parser->currentToken()->value, "gs_5_0")) prof = Profile::PROFILE_gs_5_0;
    if(strcmp(parser->currentToken()->value, "gs_5_1")) prof = Profile::PROFILE_gs_5_1;
    if(strcmp(parser->currentToken()->value, "lib_4_0")) prof = Profile::PROFILE_lib_4_0;
    if(strcmp(parser->currentToken()->value, "lib_4_1")) prof = Profile::PROFILE_lib_4_1;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_1")) prof = Profile::PROFILE_lib_4_0_level_9_1;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_1_vs_only")) prof = Profile::PROFILE_lib_4_0_level_9_1_vs_only;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_1_ps_only")) prof = Profile::PROFILE_lib_4_0_level_9_1_ps_only;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_3")) prof = Profile::PROFILE_lib_4_0_level_9_3;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_3_vs_only")) prof = Profile::PROFILE_lib_4_0_level_9_3_vs_only;
    if(strcmp(parser->currentToken()->value, "lib_4_0_level_9_3_ps_only")) prof = Profile::PROFILE_lib_4_0_level_9_3_ps_only;
    if(strcmp(parser->currentToken()->value, "lib_5_0")) prof = Profile::PROFILE_lib_5_0;
    if(strcmp(parser->currentToken()->value, "hs_5_0")) prof = Profile::PROFILE_hs_5_0;
    if(strcmp(parser->currentToken()->value, "hs_5_1")) prof = Profile::PROFILE_hs_5_1;
    if(strcmp(parser->currentToken()->value, "ps_2_0")) prof = Profile::PROFILE_ps_2_0;
    if(strcmp(parser->currentToken()->value, "ps_2_a")) prof = Profile::PROFILE_ps_2_a;
    if(strcmp(parser->currentToken()->value, "ps_2_b")) prof = Profile::PROFILE_ps_2_b;
    if(strcmp(parser->currentToken()->value, "ps_2_sw")) prof = Profile::PROFILE_ps_2_sw;
    if(strcmp(parser->currentToken()->value, "ps_3_0")) prof = Profile::PROFILE_ps_3_0;
    if(strcmp(parser->currentToken()->value, "ps_3_sw")) prof = Profile::PROFILE_ps_3_sw;
    if(strcmp(parser->currentToken()->value, "ps_4_0")) prof = Profile::PROFILE_ps_4_0;
    if(strcmp(parser->currentToken()->value, "ps_4_0_level_9_0")) prof = Profile::PROFILE_ps_4_0_level_9_0;
    if(strcmp(parser->currentToken()->value, "ps_4_0_level_9_1")) prof = Profile::PROFILE_ps_4_0_level_9_1;
    if(strcmp(parser->currentToken()->value, "ps_4_0_level_9_3")) prof = Profile::PROFILE_ps_4_0_level_9_3;
    if(strcmp(parser->currentToken()->value, "ps_4_1")) prof = Profile::PROFILE_ps_4_1;
    if(strcmp(parser->currentToken()->value, "ps_5_0")) prof = Profile::PROFILE_ps_5_0;
    if(strcmp(parser->currentToken()->value, "ps_5_1")) prof = Profile::PROFILE_ps_5_1;
    if(strcmp(parser->currentToken()->value, "rootsig_1_0")) prof = Profile::PROFILE_rootsig_1_0;
    if(strcmp(parser->currentToken()->value, "tx_1_0")) prof = Profile::PROFILE_tx_1_0;
    if(strcmp(parser->currentToken()->value, "vs_1_1")) prof = Profile::PROFILE_vs_1_1;
    if(strcmp(parser->currentToken()->value, "vs_2_0")) prof = Profile::PROFILE_vs_2_0;
    if(strcmp(parser->currentToken()->value, "vs_2_a")) prof = Profile::PROFILE_vs_2_a;
    if(strcmp(parser->currentToken()->value, "vs_2_sw")) prof = Profile::PROFILE_vs_2_sw;
    if(strcmp(parser->currentToken()->value, "vs_3_0")) prof = Profile::PROFILE_vs_3_0;
    if(strcmp(parser->currentToken()->value, "vs_3_sw")) prof = Profile::PROFILE_vs_3_sw;
    if(strcmp(parser->currentToken()->value, "vs_4_0")) prof = Profile::PROFILE_vs_4_0;
    if(strcmp(parser->currentToken()->value, "vs_4_0_level_9_0")) prof = Profile::PROFILE_vs_4_0_level_9_0;
    if(strcmp(parser->currentToken()->value, "vs_4_0_level_9_1")) prof = Profile::PROFILE_vs_4_0_level_9_1;
    if(strcmp(parser->currentToken()->value, "vs_4_0_level_9_3")) prof = Profile::PROFILE_vs_4_0_level_9_3;
    if(strcmp(parser->currentToken()->value, "vs_4_1")) prof = Profile::PROFILE_vs_4_1;
    if(strcmp(parser->currentToken()->value, "vs_5_0")) prof = Profile::PROFILE_vs_5_0;
    if(strcmp(parser->currentToken()->value, "vs_5_1")) prof = Profile::PROFILE_vs_5_1;

    if(prof == Profile::PROFILE_NONE) {
        printf("ERROR Unknow profile %s at line %u!\n", parser->currentToken()->value, parser->currentToken()->line);
        exit(-1);
    }

    parser->readToken(Token::TOKEN_IDENTIFIER);
    return prof;
}


}