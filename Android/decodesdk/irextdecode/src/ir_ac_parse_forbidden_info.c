/**************************************************************************************
Filename:       ir_parse_forbidden_info.c
Revised:        Date: 2016-10-05
Revision:       Revision: 1.0

Description:    This file provides algorithms for forbidden area of AC code

Revision log:
* 2016-10-05: created by strawmanbobi
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ir_decode.h"
#include "../include/ir_ac_parse_forbidden_info.h"


extern protocol *context;


INT8 parse_nmode_data_speed(char *pdata, ac_n_mode seq)
{
    char buf[16] = {0};
    char *p = pdata;
    UINT16 pos = 0;
    UINT16 cnt = 0, index = 0;

    while (index <= ir_strlen(pdata))
    {
        while ((index != ir_strlen(pdata)) && (*(p++) != ','))
        {
            index++;
        }
        ir_memcpy(buf, pdata + pos, index - pos);
        pos = (UINT16) (index + 1);
        index = pos;
        context->n_mode[seq].speed[cnt++] = (UINT8) atoi(buf);
        context->n_mode[seq].speed_cnt = (UINT8) cnt;
        ir_memset(buf, 0, 16);
    }

    return IR_DECODE_SUCCEEDED;
}

INT8 parse_nmode_data_temp(char *pdata, ac_n_mode seq)
{

    char buf[16] = {0};
    char *p = pdata;
    UINT16 pos = 0;
    UINT16 cnt = 0, index = 0;

    while (index <= ir_strlen(pdata))
    {
        while ((index != ir_strlen(pdata)) && (*(p++) != ','))
        {
            index++;
        }
        ir_memcpy(buf, pdata + pos, index - pos);
        pos = (UINT16) (index + 1);
        index = pos;
        context->n_mode[seq].temp[cnt++] = (UINT8) (atoi(buf) - 16);
        context->n_mode[seq].temp_cnt = (UINT8) cnt;
        ir_memset(buf, 0, 16);
    }
    return IR_DECODE_SUCCEEDED;
}

INT8 parse_nmode_pos(char *buf, ac_n_mode index)
{
    UINT16 i = 0;
    char data[64] = {0};
    // char start[8] = {0};
    if (ir_strlen(buf) == 1)
    {
        if (buf[0] == 'S' || buf[0] == 's')
        {
            context->n_mode[index].allspeed = 1;
        }
        else if (buf[0] == 'T' || buf[0] == 't')
        {
            context->n_mode[index].alltemp = 1;
        }
        return IR_DECODE_SUCCEEDED;
    }

    for (i = 0; i < ir_strlen(buf); i++)
    {
        if (buf[i] == '&')
        {
            ir_memcpy(data, buf + i + 1, ir_strlen(buf) - i - 1);
            break;
        }
    }
    if (buf[0] == 'S')
    {
        parse_nmode_data_speed(data, index);
    }
    else
    {
        parse_nmode_data_temp(data, index);
    }

    return IR_DECODE_SUCCEEDED;
}

INT8 parse_nmode(struct tag_head *tag, ac_n_mode index)
{
    UINT16 i = 0;
    UINT16 preindex = 0;

    char buf[64] = {0};

    if (tag->pdata[0] == 'N' && tag->pdata[1] == 'A')
    {
        // ban this function directly
        context->n_mode[index].enable = 0;
        return IR_DECODE_SUCCEEDED;
    }
    else
    {
        context->n_mode[index].enable = 1;
    }

    preindex = 0;
    for (i = 0; i < tag->len; i++)
    {
        if (tag->pdata[i] == '|')
        {
            ir_memcpy(buf, tag->pdata + preindex, i - preindex);
            preindex = (UINT16) (i + 1);
            parse_nmode_pos(buf, index);
            ir_memset(buf, 0, 64);
        }

    }
    ir_memcpy(buf, tag->pdata + preindex, i - preindex);
    parse_nmode_pos(buf, index);
    ir_memset(buf, 0, 64);
    return IR_DECODE_SUCCEEDED;
}
