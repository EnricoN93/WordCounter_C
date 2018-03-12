/* 
Programma che implementa una versione semplificata del comando Unix wc limitatamente alle opzioni -l e -w (man 1 wc).
Se non vengono passate opzioni, il programma stampa sia il numero di linee che il numero di parole del/dei file i cui
nomi sono passati come argomento (mywc [-l -w] file1 [file2 file3 ….]).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int contalinee(FILE *file)
{
	if(file == NULL)
	{
		perror("contalinee function");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_SET);
	int line_counter = 0;
	char *buf = (char*) malloc(100* sizeof(char));
	while(fgets(buf, 1024, file) != NULL)
	{
		line_counter++;
	}
	free(buf);
	return line_counter;
}

int contaparole(FILE *file)
{
	if(file == NULL)
	{
		perror("contalinee function");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_SET);
	int word_counter = 0;
	char *token;
	char *buf = (char*) malloc(100* sizeof(char));

	while((fgets(buf, 1024, file)) != NULL)
	{
		token= strtok(buf, " ");
	
		while(token != NULL)
		{
			++word_counter;
			token = strtok(NULL, " ");
		}
	}
	free(buf);
	return word_counter;
}


int main(int argc, char *argv[])
{
	int opt;
	//FLAGS
	int lines = 0;
	int words = 0;

	while ((opt = getopt(argc, argv, "nw")) != -1)
	{
		switch (opt)
	 	{
        	case 'n': lines = 1;
        			  continue;

        	case 'w' : words = 1 ;
        			   continue;
	 	}
	}

	if (optind >= argc) //nessun file passato come argomento
	{
	 	
    	fprintf(stderr, "Expected argument after options\n");
    	exit(EXIT_FAILURE);
    }

    while(optind < argc)
    {
    	FILE *input = fopen(argv[optind], "r");
    	if(input == NULL)
    	{
    		perror("Aprendo il file");
    		exit(EXIT_FAILURE);
    	}

    	if(lines == 1)
    	{
    		int line_counter = contalinee(input);
    		printf("Righe del file %s: %d \n",argv[optind], line_counter);
    	}

    	if(words == 1)
    	{
    		if(lines == 1);
    		int word_counter = contaparole(input);
    		printf("Parole presenti nel file %s: %d \n",argv[optind], word_counter);
    	}

    	if(lines == 0 && words == 0)
    	{
    		int line_counter = contalinee(input);
    		int word_counter = contaparole(input);
    		printf("Righe del file %s: %d \n",argv[optind], line_counter);
    		printf("Parole presenti nel file %s: %d \n",argv[optind], word_counter);
    	}
    	
    	optind++;
    }

	return 0;
}
