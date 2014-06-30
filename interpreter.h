void interpret(int argc, char const *argv[],int* record,int max_file_id);
void addWord(char* word,int *record);
void mergeWord(char* word,int* record,int max_file_id);
int isOr(const char *input);
int isAnd(const char *input);
void quick_sort(int* idx,int* val,int start,int end);
void swap(int i,int j,int* idx,int *val);
