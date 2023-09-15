#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "color_print.h"
#include "debug.h"
#include "onegin_funcs.h"

int main()
{
   // CHECK(file_name);

    FILE *input_file = fopen("hamlet.txt", "rb");

    const size_t kBufSize = GetFileSize(input_file);

    char *buf = (char *) calloc(kBufSize + 1, sizeof(char));
    fread(buf, sizeof(char), kBufSize, input_file);

    fclose(input_file);

    const size_t kLinesCount = SplitBufIntoLines(buf);
    char **text = (char **) calloc(kLinesCount, sizeof(char *));
    FillText(text, buf, kBufSize);
    /*if (!buf)
    {
        perror("buf fucked up");
        fclose();
        return 2;
    } */

    //char **text = ReadTextFromFile("hamlet.txt");

    //const size_t kLinesCount = GetTextSize((const char **)text);

    FILE *output_file =  fopen("sorted_hamlet.txt", "w");\

    /*if ()
    {
        perror("output file fucked up");
    }*/



    fprintf(output_file, "\t\t\t\t\t[ALPHABET SORT]\n");

    qsort(text, kLinesCount, sizeof(char *), MyStrcmp);
    PrintTextInFile(text, output_file);


    fprintf(output_file,"\n-------------------------------------------------------------------\n"
                        "\t\t\t\t\t[REVERSE ALPHABET SORT]\n");

    VoidInsertSort(text, kLinesCount, sizeof(char *), MyReverseStrcmp);
    PrintTextInFile(text, output_file);

    fprintf(output_file,"\n-------------------------------------------------------------------\n"
                        "\t\t\t\t\t[SOURCE]\n");

    qsort(text, kLinesCount, sizeof(char *), CompPointers);
    PrintTextInFile(text, output_file);

    fclose(output_file);
    free(text);

    return 0;
}
