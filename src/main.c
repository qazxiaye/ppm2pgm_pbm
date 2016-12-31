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

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "imgStruct.h"

//global variables used in convertion
double pbm_threshold = 0.28;
double pgm_weight_r  = 0.299;
double pgm_weight_g  = 0.587;
double pgm_weight_b  = 0.114;

int SaveImg(ImgStruct* img, char* inFileName);
ImgStruct* Convert(ImgStruct* ppm);
ImgStruct* ReadPPM(FILE* file);

void ShowImgData(ImgStruct img)
{
    printf("%sWidth  :%s %d\n", GRN, NRM, img.width);
    printf("%sHeight :%s %d\n", GRN, NRM, img.height);
    printf("%sMax    :%s %d\n", GRN, NRM, img.max);

    uint64_t* pixel = img.pixels;

    const uint64_t max = 65535;
    int i, j;
    for(i = 0; i < img.height; i++)
    {
        for(j = 0; j < img.width; j++)
        { 

            int r = (*pixel & (max << 32)) >> 32;         
            int g = (*pixel & (max << 16)) >> 16;
            int b = *pixel & max;

            printf("%sR :%s %d\n", GRN, NRM, r);
            printf("%sG :%s %d\n", GRN, NRM, g);
            printf("%sB :%s %d\n", GRN, NRM, b);
        }
    }
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        ColorShow("Please pass ppm images to be converted as parameters.", YEL);
        return 0;
    }

    int i;
    for(i=1; i<argc; i++)
    {
        //reading
        printf("reading image %s...\n", argv[i]);

        FILE* f = fopen(argv[i], "r");
        if(f == NULL)
        {
            printf("%sfile %s does not exist!%s\n", RED, argv[i], NRM);
            continue;
        }

        ImgStruct* ppm = ReadPPM(f);
        fclose(f);

        if(ppm == NULL)
            continue;

        //converting
        printf("converting image %s...\n", argv[i]);
        ImgStruct* img = Convert(ppm);

	    free(ppm->pixels);
	    free(ppm);

        if(img == NULL)
            continue;

        //saving result image
        printf("saving image %s...\n", argv[i]);
        SaveImg(img, argv[i]);

	    free(img->pixels);
	    free(img);
    }

	return 0;
}

