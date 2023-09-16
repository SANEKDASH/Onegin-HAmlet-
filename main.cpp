#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "color_print.h"
#include "debug.h"
#include "onegin_funcs.h"

int main()
{
    Text text = {};
    ReadTextFromFile("hamlet.txt", &text);

    const size_t kLinesCount = GetLinesCount(text.lines_ptr);

    FILE *output_file =  fopen("sorted_hamlet.txt", "w");
    CHECK(output_file);

    fprintf(output_file, "\t\t\t\t\t[ALPHABET SORT]\n");
    qsort(text.lines_ptr, text.lines_count, sizeof(char *), MyStrcmp);
    PrintTextInFile(text.lines_ptr, output_file);

    fprintf(output_file,"\n-------------------------------------------------------------------\n"
                        "\t\t\t\t\t[REVERSE ALPHABET SORT]\n");
    qsort(text.lines_ptr, text.lines_count, sizeof(char *), MyReverseStrcmp);
    PrintTextInFile(text.lines_ptr, output_file);

    fprintf(output_file,"\n-------------------------------------------------------------------\n"
                        "\t\t\t\t\t[SOURCE]\n");

    VoidInsertSort(text.lines_ptr, text.lines_count, sizeof(char *), CompPointers);
    PrintTextInFile(text.lines_ptr, output_file);

    fclose(output_file);
    free(text.lines_ptr);
    free((void *)text.buf);

    return 0;
}
