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
#include <stdint.h>
#include <stdlib.h>
#include "imgStruct.h"

const int MaxPixelDigitNB = 5; //max value of a pixel 65535
int isLegal = 1;

static int IsContent(char c)
{
    if(c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\0' || c == '\x0B')
        return 0;

    return 1;
}

static char NextDigit(FILE* file)
{
    if(feof(file))
    {
        isLegal = 0;
        return ' ';
    }

    char res = getc(file);

    //pass blank
    while(!IsContent(res))
    {
        if(feof(file))
        {
            isLegal = 0;
            return ' ';
        }

        res = getc(file);
    }

    //pass comment
    if(res == '#')
    {
        while(res != '\n')
        {
            res = getc(file);
        }

        if(!IsContent(res))
            return NextDigit(file);
        else
            return res;
    }

    return res;
}

static unsigned NextNumber(FILE* file, int length)
{
	char str[length + 1];

    char c = NextDigit(file);
    if(c == ' ')
    {
        isLegal = 0;
        return 0;
    }

    int i;
    for(i=0; IsContent(c); i++)
    {
        str[i] = c;
        c = getc(file);

        if(feof(file))
        {
            isLegal = 0;
            return 0;
        }
    }
    str[i] = '\0';

	uint32_t res = strtoul(str, '\0', 10);

    return res;
}

static unsigned NextPixelColor(FILE* file)
{
    unsigned res = NextNumber(file, MaxPixelDigitNB);

    if(res > PIXEL_MAX)
    {
        printf("%simage pixel value %d exceed 65535!%s\n", YEL, res, NRM);
        return 0;
    }

    return res;
}

static int ReadPPMHead(FILE* file, ImgStruct* img)
{
    char str[3];
    str[2] = '\0';

    if(fgets(str, 3, file) == NULL || strcmp(str, "P3") != 0)
    {
        printf("%sget %s in file head, only ASCII ppm format is supported, file can not be converted!%s\n", RED, str, NRM);
        return 1;
    }

    img->type   = PPM;
    img->width  = NextNumber(file, 10); // max of unsigned 4294967295
    img->height = NextNumber(file, 10);
    img->max    = NextNumber(file, 10);

    if(img->max > PIXEL_MAX)
    {
        printf("%smax value exceed 65535!%s\n", RED, NRM);
        return 1;
    }

    return 0;
}

ImgStruct* ReadPPM(FILE* file)
{
    isLegal = 1;

    ImgStruct* res = malloc(sizeof(ImgStruct));
    if(res == NULL)
    {
        printf("%smemory allocation error!%s\n", RED, NRM);
        return NULL;
    }

    if(ReadPPMHead(file, res))
    {
        printf("%sfile reading fail!%s\n", RED, NRM);
        free(res);
        return NULL;
    }

    res->pixels = malloc(sizeof(uint64_t) * res->width * res->height);
    if(res->pixels == NULL)
    {
        printf("%smemory allocation error!%s\n", RED, NRM);
        free(res);
        return NULL;
    }

    uint64_t* ptr = res->pixels;

    int i, j;
    for(i = 0; i < res->height && isLegal; i++)
    {
        for(j = 0; j < res->width && isLegal; j++)
        {
            int r = NextPixelColor(file);
            int g = NextPixelColor(file);
            int b = NextPixelColor(file);
            *ptr = ((uint64_t) r<<32) + ((uint64_t) g<<16) + (uint64_t) b;
            ptr++;
        }
    }

    if(!isLegal)
    {
        printf("%sillegal file found!%s\n", RED, NRM);
        return NULL;
    }

    printf("%sFile reading finished.%s\n", GRN, NRM);
    return res;
}

