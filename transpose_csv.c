#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int read_char_occurrence(char ch, char END, const char* path)
{
    FILE *fs = fopen(path, "r");
    int len = 0;
    char c;
    while((c = fgetc(fs)) != END)
    {
        if(c == ch) len++;
    }
    fclose(fs);
    return len;
}

static void* calloc_(size_t block, size_t size) 
{ 
  if (block > 0 && size > 0) 
  {
    void *ptr = calloc(block, size);
    if (ptr == NULL) {
      fprintf( stderr, "Cannot allocate memory %zu * %zu\n", block, size);
      exit(0);
    }
    return ptr;
  }
  return NULL;
}

char*** mkarr(size_t r, size_t c, size_t h) 
{
  char ***arr = calloc_(r, sizeof (arr[0]));
  for (size_t ii = 0; ii < r; ++ii) 
  {
    arr[ii] = calloc_(c, sizeof (arr[ii][0]));
    for (size_t jj = 0; jj < c; ++jj) 
    {
      arr[ii][jj] = calloc_(h, sizeof(arr[ii][jj][0]));
    }
  }
  return arr;
}

void transpose_csv(const char *path, const char *outfile)
{
    //CSV analysis
    //known delimiter in csv file: comma(,), semicolon(;), tab(\t), a space( ), and a pipe(|),
    //check which delimiter is used
    char del[32] = "%s";
    char delimiter = read_char_occurrence(',', '\n', path) ? ',' : (read_char_occurrence(';', '\n', path) ? ';' : read_char_occurrence('\t', '\n', path) ? '\t' : read_char_occurrence(' ', '\n', path) ? ' ' : '|');
    printf("delimited: %c\n", delimiter);
    strcat(del, &delimiter);

    //some csv has whitespace or \t after their delimiter, I need to check for that as well
    int white_sparator = read_char_occurrence(' ', '\n', path) > 0 ? true : false;
    int tab_sparator = read_char_occurrence('\t', '\n', path) > 0 ? true : false;

    if(white_sparator)
    {
        printf("there is a white space after delimited\n");
        for(int r = 0; r < white_sparator; r++)
            if(strlen(del) >  1)
                strcat(del, " ");
    }

    if(tab_sparator)
    {
        printf("there is a tab after delimited\n");
        for(int r = 0; r < tab_sparator; r++)
            if(strlen(del) >  1)
                strcat(del, "\t");
    }

    int col, row;
    col = read_char_occurrence(delimiter, '\n', path) + 1; //I can get row by known delimiter in a line
    row = read_char_occurrence('\n', EOF, path) + 1;        //I just depend on \n to tell us how much row is there

    printf("row: %d, col: %d\n", row, col);

    char ***buf = mkarr(row, col, 1); //mimimal 3D array allocated here

    int fin = 0;
    FILE *fs = fopen(path, "r");                    //open for just a read operation

    if(fs == NULL) return;
    
    for(int j = 0; j < row; j++)
    {
        for(int k = 0; k < col; k++)
        {
            int p = 1, i = 0;
            char ch;
            
            while((ch = fgetc(fs)) != EOF)
            {
                if((ch == delimiter) || (ch == '\n'))
                {
                    break;
                }
                else if((ch != '\t') && (ch != '\n') && (ch != ' ') && (ch != '\r')) 
                {            
                    buf[j][k][i++] = ch;   
                    p++;                     
                    buf[j][k] = realloc(buf[j][k], sizeof(char)+p);           //here I resize space to hold unkown and increasing char
                }
            }
            fin += p;
            buf[j][k][i] = '\0';
        }
    }
    fclose(fs);

    fs = fopen(outfile, "w");     //here I transpose the csv file, cool stuff... 
    printf("transposing...\n");
    for(int i = 0; i < col; i++)
    {   
        for(int k = 0; k < row; k++)
        {  
            char *arg;
            if(k < row - 1)
            {
                arg = calloc(sizeof(del)+1, sizeof(char));  // I get fancy a little bit here, make thing a little interesting, not needed but should help us keep the file size in check
                strcpy(arg, del);
            }
            else
            {
                arg = calloc(sizeof("%s\n")+1, sizeof(char));
                strcpy(arg, "%s\n");
            }
            fprintf(fs, arg, (char*)buf[k][i]);
            free(arg);
        }
    }
    fclose(fs);
}

int main(void)
{
    transpose_csv("./_sample_data/input.csv", "./_sample_data/out_fileput.csv");
    return 0;
}