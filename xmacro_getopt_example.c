/*
 * XMACRO_GETOPT demo program.
 * gcc -DSHORT  xmacro_getopt_example.c -o xmacro_getopt_example
 * gcc xmacro_getopt_example.c -o xmacro_getopt_example
 */

#include <stdio.h>

#ifdef SHORT

#define XMACRO_GETOPT_USE_SHORT_OPTIONS
#define XMACRO_GETOPT_OPTIONS_NO_ARG \
	XMACRO_GETOPT_OPTION_NO_ARG(INIT, 'i') \
	XMACRO_GETOPT_OPTION_NO_ARG(LIST, 'l') \
	XMACRO_GETOPT_OPTION_NO_ARG(RESTART, 'r')\
	XMACRO_GETOPT_OPTION_NO_ARG(ONE, '1')\
	XMACRO_GETOPT_OPTION_NO_ARG(TWO, '2')
#define XMACRO_GETOPT_OPTIONS_WITH_ARG \
	XMACRO_GETOPT_OPTION_WITH_ARG(FILE_OPT, 'f') \
	XMACRO_GETOPT_OPTION_WITH_ARG(NUM, 'n') 
	
#else

#define XMACRO_GETOPT_OPTIONS_NO_ARG \
	XMACRO_GETOPT_OPTION_NO_ARG(INIT, 'i',"init") \
	XMACRO_GETOPT_OPTION_NO_ARG(LIST, 'l',"list") \
	XMACRO_GETOPT_OPTION_NO_ARG(RESTART, 'r',"restart")
#define XMACRO_GETOPT_OPTIONS_SHORT_ONLY_NO_ARG \
	XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG(ONE, '1') \
	XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG(TWO, '2')
#define XMACRO_GETOPT_OPTIONS_WITH_ARG \
	XMACRO_GETOPT_OPTION_WITH_ARG(FILE_OPT, 'f',"file") \
	XMACRO_GETOPT_OPTION_WITH_ARG(NUM, 'n',"number")

#endif
	
#include "xmacro_getopt.h"

int opt_already_set(int opt)
{
	if(xmacro_getopt_option_used[opt]){
		fprintf(stderr, "option %c already set\n", FILE_OPT);		
		return 1;
	}
	xmacro_getopt_option_used[opt] = 1;
	return 0;
}

int main (int argc, char *argv[])
{
	int opt;

	printf("There is a total of %d defined options.\n",  XMACRO_GETOPT_NUM_OF_OPTIONS);
	while((opt = XMACRO_GETOPT(argc, argv)) != -1){
		switch(opt){
			case INIT:
				if(!opt_already_set(INIT_INDEX))
					printf("recognized option: %c\n", INIT);
			break;
			case LIST :
				if(!opt_already_set(LIST_INDEX))
					printf("recognized option: %c\n", LIST);
			break;
			case RESTART:
				if(!opt_already_set(RESTART_INDEX))
					printf("recognized option: %c\n", RESTART);
			break;
			case ONE:
				if(!opt_already_set(ONE_INDEX))
					printf("recognized option: %c\n", ONE);
			break;
			case TWO:
				if(!opt_already_set(TWO_INDEX))
					printf("recognized option: %c\n", TWO);
			break;
			case FILE_OPT:
				if(!opt_already_set(FILE_OPT_INDEX))
					printf("filename: %s\n", optarg);
			break;
			case NUM:
				if(!opt_already_set(NUM_INDEX))
					printf("number: %s\n", optarg);
			break;
			case ':':
				fprintf(stderr, "option %c: missing parameter\n", optopt);
				return 1;
			break;
			case '?':
				fprintf(stderr, "unknown option");
				if (isprint (optopt))
					fprintf(stderr, ": %c", optopt);
				fprintf(stderr, "\n");
				return 1;
			break;
			default:
				fprintf(stderr, "error parsing elements\n");
				return 1;
			break;
		}
	}
	for(; optind < argc; optind++)
		printf("argument: %s\n", argv[optind]);
	return 0;
}
