#include <stdio.h>
#include "utils.h"

void ColorShow(char *content, char *color)
{
    printf("%s%s%s\n", color, content, NRM);
}
