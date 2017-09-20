#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define NEWLINE "\n"
#define true (1==1)
#define false (!true)

void append_char_to_string(char* string, char character) {
    int len = strlen(string);
    string[len] = character;
    string[len + 1] = '\0';    
}

void spill_into(char* buffer, int * idx_out) {
    /* Convert buffer to int and set as the result of idx_out */
    if (strlen(buffer) != 0) {
        *idx_out = atoi(buffer);
        buffer[0] = '\0';
    }
}

void parse(char* str, char* buffer, int * start_out, int * end_out, int * step_out) {
    int start = 0;
    int end = 0;
    int step = 1;
    int colon_index = 0;    

    for (int i=0; i<strlen(str); i++) {
        if  (str[i] != ':') {
            append_char_to_string(buffer, str[i]);
        }
        else {
            if (colon_index == 0) {
                spill_into(buffer, &start);
            }

            if (colon_index == 1) {
                spill_into(buffer, &end);
            }            
            
            colon_index ++;            
        }
    }
    if (colon_index == 2) {    
        spill_into(buffer, &step);
    }

    else if (colon_index == 1) {    
        spill_into(buffer, &end);
    }
    *start_out = start;
    *end_out = end;
    *step_out = step;
}


void slice(char* str, char* buf, int start, int end, int step) { 
    
    int length = strlen(str);
    /* Allow negative indexes */
    if (start < 0) {
        start += length;
    }

    if (end <= 0) {
        end += length;
    }
    
    int buffers_running_index = 0;
    if (step > 0) {
        for (int i = start; i < end; i += step) {
            buf[buffers_running_index++] = str[i];
        }
    }
    else {
       for (int i = end - 1; i >= start; i += step) {
            buf[buffers_running_index++] = str[i];
       }
    }

    buf[buffers_running_index] = '\0';
}


void split_by(char* str, char* delimiter, char* array[], int * length_out) { 
    int i = 0;  
    array[i] = strtok(str, delimiter);
    while(array[i] != NULL) { array[++i] = strtok(NULL, delimiter); }
    
   /*  does above loop returns a trailing newline? */
    *length_out = i;
}

void line_slice(char* str, char* buf, char* delimiter, 
                int start, int end, int step, int include_delimiter) 
{
    int length;
    char* array[USHRT_MAX];

    split_by(str, delimiter, array, &length);

    if (start < 0) {
        start += length;
    }

    if (end <= 0) {
        end += length;
    }

    int buffers_running_index = 0;
    
    if (step > 0) {
        for (int i = start; i < end; i += step) {
            for(int j = 0; j < strlen(array[i]); j++) {
                buf[buffers_running_index++] = array[i][j];
            } 
            if (include_delimiter == true) {
                if (i != end - 1) {
                    for(int j = 0; j < strlen(delimiter); j++) {
                        buf[buffers_running_index++] = delimiter[j];
                    }
                }
            }
        }
        buf[buffers_running_index] = '\0';
    }

    else {
        for (int i = end - 1; i >= start; i += step) {
            for(int j = 0; j < strlen(array[i]); j++) {
                buf[buffers_running_index++] = array[i][j];

            }
            if (include_delimiter == true) {
                if (i != start) {
                    for(int j = 0; j < strlen(delimiter); j++) {
                        buf[buffers_running_index++] = delimiter[j];
                    }
                }
            }
        }
        buf[buffers_running_index] = '\0';
    }


}

int contains(int argc, char* argv[] , char* contained) { 
    for (int i = 0; i < argc; i ++) { 
        if (strstr(argv[i], contained) != NULL) {
            return true;
        }
    }
    return false;
}

char * slice_expression(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) { 
        if (strstr(argv[i], ":") != NULL){
            return argv[i];
        }
    }
}

int main(int argc, char * argv[]) {
    int start = 0;
    int end = 0;
    int step = 1;
    char buf[USHRT_MAX] = "";
    char str_to_slice[USHRT_MAX] = "";    

    scanf("%[^\t]", str_to_slice);
    char* slice_expr = slice_expression(argc, argv); 
    parse(slice_expr, buf, &start, &end, &step);

    if (contains(argc, argv, "--by-line") || contains(argc, argv, "-l"))
    {
	char delimiter[2] = "\0";
	delimiter[0] = 10;
        int with_delimiter = contains(argc, argv, "--with-delimiter" ) || 
                             contains (argc, argv, "-w");
        line_slice(str_to_slice, buf, delimiter, start, end, step, with_delimiter);
    }

    else {
        str_to_slice[strlen(str_to_slice) - 1] = '\0'; 
        slice(str_to_slice, buf, start, end, step);
    }

    
    printf("%s\n", buf);
    return 0;
}
