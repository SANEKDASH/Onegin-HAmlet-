#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "color_print.h"
#include "debug.h"
#include "onegin_funcs.h"

static void VoidSwap (void *a, void *b, size_t data_size);

static int SubStrCmp(const void *ptr_str_lhs, size_t lhs_len, const void *ptr_str_rhs, size_t rhs_len);

void PrintTextInFile(char **text, FILE *output_file)
{
    CHECK(output_file);

    for (int i  = 0; *(text + i) != 0; i++)
    {
        fprintf(output_file, "%s\n", *(text + i));
    }
}

long GetFileSize(FILE *ptr_file)
{
    CHECK(ptr_file);

    fseek(ptr_file, 0, SEEK_END);
    long buf_size = ftell(ptr_file);

    fseek(ptr_file, 0, SEEK_SET);

    return buf_size;
}

int SplitBufIntoLines(char *buf)
{
    CHECK(buf);

    char *read_ptr = buf;
    int lines_count = 0;

    while (*read_ptr++ != '\0')
    {
        if (*read_ptr == '\n')
        {
            while (*read_ptr == '\n')
            {
                ++read_ptr;
            }

            *(--read_ptr) = '\0';

            ++lines_count;

            ++read_ptr;
        }
    }

    return lines_count;
}

void FillText(char **text, const char *buf, size_t BufSize)
{
    CHECK(text);
    CHECK(buf);

    size_t i = 0;

    char *cur_line = (char *)buf;

    while (i < BufSize)
    {
        if (*(buf + i) == '\0')
        {
            *text++ = cur_line;

            ++i;

            cur_line = (char *)(buf + i);
        }
        ++i;
    }

    *text++ = cur_line;
    *text = nullptr;
}


void InsertSort(char **data,
                size_t data_len,
                int (*CompFunc)(const void* str_lhs, const void* str_rhs))
{
    CHECK(data);
    for (size_t i = 0; i < data_len; i++)
    {
        for (size_t n = i; n > 0; n--)
        {
            if (CompFunc(*(data + n), *(data + n - 1)) < 0)
            {
                VoidSwap(data + n, data + n - 1, sizeof(char *));
            }
        }
    }

//rabotaet
}


void VoidInsertSort(void *data,
                    size_t data_len,
                    size_t data_size,
                    int (*CompFunc)(const void* str_lhs, const void* str_rhs))
{
    CHECK(data);

    for (size_t i = 0; i < data_len; i++)
    {
        for (size_t n = i; n > 0; n--)
        {
            if (CompFunc((data + n * data_size), (data + (n  - 1) * data_size)) < 0)
            {
                VoidSwap((data + n * data_size), (data + (n - 1) * data_size), data_size);
            }
        }
    }
//rabotaet
}

static void VoidSwap(void *a, void *b, size_t data_size)
{
    for (size_t i = 0; i < data_size; i++)
    {
        char tmp = *((char*) b + i);

        *((char*) b + i) = *((char*) a + i);

        *((char*) a + i) = tmp;
    }
}

int MyStrcmp (const void *ptr_str_lhs, const void *ptr_str_rhs)
{
    CHECK(ptr_str_rhs);
    CHECK(ptr_str_lhs);

    const char *str_lhs = *(const char **) ptr_str_lhs;
    const char *str_rhs = *(const char **) ptr_str_rhs;

    //printf("\nlhs - %s\nrhs - %n", str_lhs, str_rhs);

    while (*str_lhs != '\0' && *str_rhs != '\0')
    {
        if (!isalpha(*str_lhs))
        {
            str_lhs++;

            continue;
        }

        if (!isalpha(*str_rhs))
        {
            str_rhs++;

            continue;
        }

        if (isalpha(*str_lhs) && isalpha(*str_rhs) && toupper(*str_lhs) == toupper((*str_rhs)))
        {
            ++str_lhs;
            ++str_rhs;

            continue;
        }
        else
        {
            return toupper(*str_lhs) - toupper(*str_rhs);
        }
    }

    return toupper(*str_lhs) - toupper(*str_rhs);
//ne rabotaet
}

int MyReverseStrcmp(const void *ptr_str_lhs, const void *ptr_str_rhs)
{
    CHECK(ptr_str_lhs);
    CHECK(ptr_str_rhs);

    const char *lhs_str = *(const char **)ptr_str_lhs;
    const char *rhs_str = *(const char **)ptr_str_rhs;

    return SubStrCmp(ptr_str_lhs, strlen(lhs_str), ptr_str_rhs, strlen(rhs_str));
}

static int SubStrCmp(const void *ptr_str_lhs, size_t lhs_len, const void *ptr_str_rhs, size_t rhs_len)
{
    CHECK(ptr_str_rhs);
    CHECK(ptr_str_lhs);

    const char *str_lhs = *(const char **)ptr_str_lhs + lhs_len - 1;
    const char *str_rhs = *(const char **)ptr_str_rhs + rhs_len - 1;

    while (lhs_len > 0  && rhs_len > 0)
    {
        if (!isalpha(*str_lhs))
        {
            lhs_len--;
            str_lhs--;

            continue;
        }

        if (!isalpha(*str_rhs))
        {
            rhs_len--;
            str_rhs--;

            continue;
        }

        if (isalpha(*str_lhs) && isalpha(*str_rhs) && toupper(*str_lhs) == toupper((*str_rhs)))
        {
            --str_lhs;
            --str_rhs;
            --lhs_len;
            --rhs_len;

            continue;
        }
        else
        {
            return toupper(*str_lhs) - toupper(*str_rhs);
        }
    }

    return toupper(*str_lhs) - toupper(*str_rhs);
}

size_t GetTextSize(const char** text)
{
    size_t text_size = 0;

    while (*(text + text_size) != nullptr)
    {
        ++text_size;
    }

    return text_size;
}


int CompPointers(const void *ptr_lhs_ptr, const void *ptr_rhs_ptr)
{
    const char *lhs_ptr = *(char **)ptr_lhs_ptr;
    const char *rhs_ptr = *(char **)ptr_rhs_ptr;

    return lhs_ptr - rhs_ptr;
}

char **ReadTextFromFile(const char *file_name)
{
    CHECK(file_name);

    FILE *input_file = fopen(file_name, "rb");

    const size_t kBufSize = GetFileSize(input_file);

    char *buf = (char *) calloc(kBufSize + 1, sizeof(char));
    fread(buf, sizeof(char), kBufSize, input_file);

    fclose(input_file);

    const size_t kLinesCount = SplitBufIntoLines(buf);
    char **text = (char **) calloc(kLinesCount, sizeof(char *));
    FillText(text, buf, kBufSize);

    free(buf);

    return text;
}
