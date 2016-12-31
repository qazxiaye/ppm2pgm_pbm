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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "imgStruct.h"

static char* ChangeExtension(char* fileName, char* ext)
{
    if(fileName == NULL)
        return NULL;

    if(ext==NULL || strlen(ext)==0 )
        ext = "gen";

    char* dot   = strrchr(fileName, '.');
    char* slash = strrchr(fileName, '/');
    
    char* res;
    if(dot > slash)
    {
        int nameLen = dot - fileName;
        res = malloc( nameLen + strlen(ext) + 2);
        if(res == NULL)
        {
            ColorShow("memory allocation error!", RED);
            return NULL;
        }

        memcpy(res, fileName, nameLen);
        res[nameLen] = '.';
        strcpy(res + nameLen + 1, ext);
    }
    else
    {
        res = malloc(strlen(fileName) + strlen(ext) + 2);
        if(res == NULL)
        {
            ColorShow("memory allocation error!", RED);
            return NULL;
        }

        strcpy(res, fileName);
        res[strlen(fileName)] = '.';
        strcpy(res+strlen(fileName)+1, ext);
    }

    return res;
}

int SaveImg(ImgStruct* img, char* inFileName)
{
    char* outFileName;
    switch(img->type)
    {
        case PGM:
            outFileName = ChangeExtension(inFileName, "pgm");
            break;
        case PBM:
            outFileName = ChangeExtension(inFileName, "pbm");
            break;
        case PPM:
            outFileName = ChangeExtension(inFileName, "bk.ppm");
            break;
		default:
            ColorShow("unexpected image type!", RED);
			return 1;
    }

    FILE* file = fopen(outFileName, "w");

    if(file == NULL)
    {
        printf("%sfile %s can not be written!%s\n", RED, outFileName, NRM);
        free(outFileName);
        return 1;
    }

    if(img->type == PGM)
        fprintf(file, "P2\n");
    else if(img->type == PBM)
        fprintf(file, "P1\n");
    else
        fprintf(file, "P3\n");

    fprintf(file, "%d %d\n%d\n", img->width, img->height, img->max); 

	uint64_t *ptr = img->pixels;

    int i, j;
    for(i = 0; i < img->height; i++)
    {
        for(j = 0; j < img->width; j++)
        { 
            fprintf(file, "%d ", * ptr);         
            ptr++;
        }
    }

    fclose(file);
    printf("%sFile %s has been generated.%s\n", GRN, outFileName, NRM);
    free(outFileName);

    return 0;
}

