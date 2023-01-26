#include "console_util.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter your favorite color: ");
    char *buffer = get_line_dynamic();
    printf("%s", buffer);
    free(buffer);
}