#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct dictionary {
	char* word;
	int count;
}dictionary;

int main(int argc, char* argv[])
{
	int toknum = 0;

	FILE* fp1;
	FILE* fp2;

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
	
	char strTemp[4000];
	char* str;
	char delimiters[40] = {0,};
	
	int num = 0;

	for (int i = 32;i < 48;i++) {
		delimiters[num] = i;
		num++;
	}
	for (int i = 58;i < 65;i++) {
		delimiters[num] = i;
		num++;
	}
	for (int i = 91;i < 97;i++) {
		delimiters[num] = i;
		num++;
	}
	for (int i = 123;i < 128;i++) {
		delimiters[num] = i;
		num++;
	}
	delimiters[num] = '\n';
	num++;
	delimiters[num] = '\t';
	num++;
	delimiters[num] = '\r';
	num++;

	dictionary* d_arr;
	d_arr = (dictionary*)malloc(sizeof(dictionary) * 50000);

	int total = 0;
	int p_total = 0;
	int n = 1;

	if (fp1 != NULL) {
		while (!feof(fp1)) {
			str = fgets(strTemp, sizeof(strTemp), fp1);
			char* token = strtok(str, delimiters);
			while (token != NULL)
			{

				total++;
				int flag = 0;
				char* token_s = _strlwr(token);
				for (int i = 0;i < p_total;i++) {
					if(strcmp(d_arr[i].word, token_s) == 0){
						d_arr[i].count++;
						flag++;
						break;
					}
				}
				
				if (flag == 0) {
					d_arr[p_total].word = (char*)malloc(sizeof(char) * 20);
					strcpy(d_arr[p_total].word, token_s);
					d_arr[p_total].count = 1;
					p_total++;
				}

				token = strtok(NULL, delimiters);
			}
		}
		fclose(fp1);
	}

	for (int i = 0;i < p_total;i++) {
		fprintf(fp2,"[%04d] %s (%d)\n", i+1, d_arr[i].word, d_arr[i].count);
		free(d_arr[i].word);
	}
	fprintf(fp2,"[total] %04d\n", total);

	fprintf(fp2, "\n\n-----------------\n");
	fprintf(fp2, "Jin-Young Baek\n");
	fprintf(fp2, "Student ID : 20181945\n");
	fprintf(fp2, "-----------------\n");

	free(d_arr);
	fclose(fp2);
}