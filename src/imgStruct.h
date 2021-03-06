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

#ifndef _DATASTRUCT_H__
#define _DATASTRUCT_H__

#include <stdint.h>

typedef enum
{
    PPM = 1,
    PBM = 2,
    PGM = 3
} ImgType;

typedef struct
{
    ImgType  type;
    unsigned width;
    unsigned height;
    unsigned max;
    uint64_t* pixels;
} ImgStruct;

#define PIXEL_MAX 65535

#endif

