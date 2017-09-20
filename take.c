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
    while(array[i] != NULL) { array[++i] = strtok(NULL,"/"); }
    
    /*  above loop returns a trailing newline, let's get rid of it. */
    char* last_word = array[i - 1];
    array[i - 1][strlen(last_word) - 1] = '\0';

    *length_out = i;
}

void line_slice(char* str, char* buf, char* delimiter, int start, int end, int step) 
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
        }
        buf[buffers_running_index] = '\0';
    }
    else {
        for (int i = end - 1; i >= start; i += step) {
            for(int j = 0; j < strlen(array[i]); j++) {
                buf[buffers_running_index++] = array[i][j];

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


int main(int argc, char * argv[]) {
	int start = 0;
    int end = 0;
    int step = 1;
    char buf[USHRT_MAX] = "";
    char str_to_slice[USHRT_MAX] = "";    
    

    scanf("%[^\t]", str_to_slice);

    if (contains(argc, argv, "--by-line") || contains(argc, argv, "-l"))
    { 
        char* slice_expr = argv[2]; 
        parse(slice_expr, buf, &start, &end, &step);   
        line_slice(str_to_slice, buf, "/", start, end, step);
        printf("%s\n", buf);
        return 0;
    }

    else {
    	char* slice_expr = argv[1]; 
        parse(slice_expr, buf, &start, &end, &step);
        str_to_slice[strlen(str_to_slice) - 1] = '\0'; 
        slice(str_to_slice, buf, start, end, step);
        printf("%s\n", buf);
        return 0;
    }
}
