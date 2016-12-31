/*
* Copyright @ Ye XIA <qazxiaye@126.com> & Xinxiu TAO <taozi_1101@163.com>
* 
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#include <stdint.h>
#include <stdlib.h>
#include "utils.h"
#include "imgStruct.h"

extern double pbm_threshold;

ImgStruct* Convert(ImgStruct* ppm)
{
    ImgStruct* res = malloc(sizeof(ImgStruct));
    if(res == NULL)
    {
        ColorShow("memory allocation error!", RED);
        return NULL;
    }

    res->type   = PBM;
    res->width  = ppm->width;
    res->height = ppm->height;
    res->max    = ppm->max;
    res->pixels = malloc(sizeof(uint64_t) * res->height * res->width);
    if(res->pixels == NULL)
    {
        ColorShow("memory allocation error!", RED);
        free(res);

        return NULL;
    }

    uint64_t *p_dst = res->pixels; 
	uint64_t *p_src = ppm->pixels;

    const uint64_t max = 65535;
    int i, j;
    for(i = 0; i < res->height; i++)
    {
        for(j = 0; j < res->width; j++)
        { 
            uint64_t pixel = * p_src;

            int r = (pixel & (max << 32)) >> 32;         
            int g = (pixel & (max << 16)) >> 16;
            int b = pixel & max;

            double v = (double) (r*g*b*1.0) / (res->max*res->max*res->max);
            * p_dst = v<pbm_threshold ? 1 : 0;

			p_src++;
            p_dst++;
        }
    } 

    ColorShow("File converting finished.", GRN);
    return res;
}

