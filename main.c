#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SEP "----------\n"
#define SEPE "==========\n"
#define FILENAME "log.txt"

int main(int argc, char** argv){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char str[50];
	int lday, lmon, lyear;
	char sharp;
	char buffer[256];

	/* Opens file to read or creates file*/
	FILE *f = fopen("log.txt", "r");
	if (f == NULL){
		printf("Creating file\n");
		f = fopen("log.txt", "w");
		f = fopen("log.txt", "r");
	}

	/* Scan doc for '#' and store last value (inefficient)*/
	while(fgets(buffer, 256, f)){
		if(buffer[0] == '#')
			fscanf(f, "%c%2d/%2d/%4d", &sharp, &lday, &lmon, &lyear);
	}

	f = fopen("log.txt", "a");
	/* If new file or new day, write initialization of last date*/
	if(!sharp){
		lday = tm.tm_mday;
		lmon = tm.tm_mon +1;
		lyear = tm.tm_year + 1900;

		fprintf(f, "#%02d/%02d/%dNEWFILE\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		fprintf(f, SEP);
	}

	printf("LOG Time: %02d/%02d/%d\n", lday, lmon, lyear);
	printf("PC Time: %02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	/* LOG TIME INCORRECT, SEE LINE 29*/
	/* New day, new header*/
	if (lyear != tm.tm_year +1900 || lmon !=tm.tm_mon+1 || lday != tm.tm_mday){
		fprintf(f, "#%02d/%02d/%dNEWDAY\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		fprintf(f, SEP);
	}
	
	/* print time */
	fprintf(f, "%02d:%02d\n", tm.tm_hour, tm.tm_min);

	/* get input*/
	printf("> ");
	scanf("%[^\n]s",str);
	fprintf(f, str);
	fprintf(f, "\n");
	fprintf(f, SEP);


	fclose(f);
	return 0;
}