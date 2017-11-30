#include <stdio.h>
#include <stdlib.h>		/* для EXIT_SUCCESS и EXIT_FAILURE */
#include <unistd.h>		/* для функции getopt() */


/* Программа принимает сообщения и ключ в аргументах командной строчки :
 * -k - опция, означает, что следующий аргумент - ключ шифровки/дешифровки
 * -d - булевская опция включения режима дешифровки. Если ключ не задан, 
 *  попробовать дешифровать сообщение автоматически.
 * -f - сообщение считывается с файла, его имя задано в следующем аргументе.
 * -о - зашифрованное сообщение записать в файл, его имя в следующем аргументе.
 */

/* Глобальная структура с аргументами 
 */
struct global_args_t {
	char		*key_string;		/* -k ключ */
	int		decryption;		/* -d ключ */
	const char	*in_filename;		/* -o ключ */
	FILE		*in_file;
	const char	*out_filename;		/* -f ключ */
	FILE		*out_file;
} global_args;

static const char *opt_string = "k:df:o:?";	/* строка с опциями getopt() */

/* Сообщение с информацией об опциях 
 */
void usage(char *progname) 
{
	printf("Использование:\n");
	printf("%s [ключ] \n\n", progname);
	printf("Ключи:\n");
	printf(" -k \t ключ шифровки/дешифровки\n");
	printf(" -d \t опция включения режима дешифровки\n");
	printf(" -f \t файл для чтения сообщения\n");
	printf(" -o \t файл для записи сообщения\n");
	printf(" -h \t Вывод этого сообщения\n\n");
	/* exit(1); */
	exit( EXIT_FAILURE );
}

int main( int argc, char *argv[] )
{
	/* usage(argv[0]); */

	int opt = 0;
	opterr	= 0;		/* отключим вывод ошибок в getopt()*/
	int i	= 0;
	
	/* Инизиализация структуры 
	 */
	global_args.key_string	 = NULL;		/* -k ключ */
	global_args.decryption	 = 0;			/* -d ключ */
	global_args.in_filename	 = NULL;		/* -o ключ */
	global_args.in_file	 = NULL;
	global_args.out_filename = NULL;		/* -f ключ */
	global_args.out_file	 = NULL;
	
	/* Обработки параметров в программе. 
	 * Как только getopt() распознает параметр, конструкция switch 
	 * определит, какой точно параметр был найден, и отметит 
	 * соответствующее поле в структуре globalArgs. Когда getopt() 
	 * вернет -1, то можно считать, что обработка параметров 
	 * выполнена и оставшиеся аргументы являются файлами ввода.
	 */
	while( (opt = getopt( argc, argv, opt_string )) != -1 ) {
		switch( opt ) {
			case 'k':
				global_args.key_string = optarg;
				break;
			
			case 'd':
				global_args.decryption = 1;	/* true */
				break;
				
			case 'f':
				global_args.in_filename = optarg;
				break;
			
			case 'o':
				global_args.out_filename = optarg;
				break;
				
			case 'h':	/* переход к следующему кейсу */
			case '?':
				usage(argv[0]);
				break;
				
			default:
				/* если не один из кейсов не сработал */
				break;
		}
	}
	
	/* global_args.inputFiles = argv + optind; */
	/* global_args.numInputFiles = argc - optind; */

	/* convert_document(); */
	
	printf ("k = %s\n", global_args.key_string);
	printf ("d = %d\n", global_args.decryption);
	printf ("f = %s\n", global_args.in_filename);
	printf ("o = %s\n", global_args.out_filename);

	for (i = optind; i < argc; i++)
	{
		if (argv[i][0] != '-') 
			printf("default = %s\n\n", argv[i]);
	}
	
	/* for (i = 0; i < argc; i++) */
	/* 	printf ("argv = %s\n", argv[i]); */
	
	return EXIT_SUCCESS;
}
