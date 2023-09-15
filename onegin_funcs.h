void FillText(char **text, const char *buf, size_t BufSize);

long GetFileSize(FILE *ptr_file);

int SplitBufIntoLines(char *buf);

void InsertSort(char **data,
                size_t data_len,
                int (*CompFunc)(const void* str_lhs, const void* str_rhs));

void PrintTextInFile(char **text, FILE *output_file);

int MyStrcmp(const void *ptr_str_lhs, const void *ptr_str_rhs);

int MyReverseStrcmp(const void *ptr_str_lhs, const void *ptr_str_rhs);

int CompPointers(const void *ptr_lhs_ptr, const void *ptr_rhs_ptr);

void VoidInsertSort(void *data,
                    size_t data_len,
                    size_t data_size,
                    int (*CompFunc)(const void* str_lhs, const void* str_rhs));

size_t GetTextSize(const char** text);

char **ReadTextFromFile(const char *file_name);
