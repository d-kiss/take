#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	int nekudotayim_index = 0;	

	for (int i=0; i<strlen(str); i++) {
		if  (str[i] != ':') {
			append_char_to_string(buffer, str[i]);
		}
		else {
			if (nekudotayim_index == 0) {
				spill_into(buffer, &start);
			}

			if (nekudotayim_index == 1) {
				spill_into(buffer, &end);
			}			
			
			nekudotayim_index ++;			
		}
	}
    
    spill_into(buffer, &step);

	/* Spill the rest */
    *start_out = start;
	*end_out = end;
	*step_out = step;
}

void slice(void* arr, int length, int start, int end, int step) { 
    
    /* Allow negative indexes */
    if (start < 0) {
        start += length;
    }

    if (end <= 0) {
        end += length;
    }
    


    if (step > 0) {

    }
    else {
        /* TODO: Implement this part. */
    }
}


int main(int argc, char * argv[]) {
	int start = 0;
    int end = 0;
    int step = 1;
    char buf[256] = "";
	char* slice_expr = argv[1];

	parse(slice_expr, buf, &start, &end, &step);
    
	return 0;
}
