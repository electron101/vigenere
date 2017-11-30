/* Описание программы:
 * 
 * Реализовать консольную программу, которая может шифровать 
 * и дешифровать сообщения английского языка с помощью шифра Виженера. 
 * При шифровке и дешифровке игнорировать все остальные символы кроме 
 * букв. Регистр букв не учитывать. Программа принимает сообщения и 
 * ключ в аргументах командной строчки : 
 * -k - опция, которая означает, что следующий аргумент - 
 *  ключ шифровки/дешифровки 
 * -d - булевская опция включения режима дешифровки. Если ключ не задан,
 *  попробовать дешифровать сообщение автоматически. 
 * -f - сообщение считывается с файла, название которого задано в 
 *  следующем аргументе. 
 * -о - зашифрованное сообщение записать в файл, название которого 
 *  задано в следующем аргументе.
 * Аргументы программы можут быть размещены в любом порядке, но 
 * после небулевских опций всегда должно идти их значение. Если 
 * аргументы заданы некорректно - вернуть EXIT_FAILURE. 
 * Результаты выдавать в виде текста в формате: 
 * 
 * KEY
 * ENCODEDORDECODEDMESSAGE
 * 
 * Если не задано опции -о , результат записывать в консоль, 
 * иначе - в указанный опцией файл. Если автоматическая дешифровка 
 * не реализована - возвращать статус программы EXIT_FAILURE.
 * Компиляция gcc. После успешной компиляции программа запускается 
 * с разными аргументами , проверяются коды статусов работы программы 
 * и ее результаты из stdout или *** файлов. 
 * Таймаут времени работы программы - 3 секунды. 
 * -----------------------------------------------------------------------
 * 
 * Примеры вызовов программы с аргументами:
 *
 *  ./a.out "Some message to encode" -k "RANDOM"
 *  ./a.out -d "jozh aqjsnjs ff drfcpv" -k "RANDOM"
 *  ./a.out "jozh aqjsnjs ff drfcpv" -d
 *  ./a.out -f "to_encode.txt" -k "RANDOM"
 *  ./a.out -k "RANDOM" -d -f "to_decode.txt"
 *  ./a.out -d -f "to_decode.txt" -k "RANDOM" -o "decoded.txt"
 *
 */

#include <stdio.h>
#include <stdlib.h>		/* для EXIT_SUCCESS и EXIT_FAILURE */
#include <unistd.h>		/* для функции getopt() */

/* Глобальная структура с аргументами 
 */
struct global_args_t {
	char		*key_string;	/* -k ключ */
	int		decryption;	/* -d ключ */
	const char	*in_filename;	/* -o ключ */
	FILE		*in_file;
	const char	*out_filename;	/* -f ключ */
	FILE		*out_file;
	char		*msg;		/* сообщение шифровки/дешифровки */
} global_args;

static const char *opt_string = "k:df:o:eh?";	/* строка с опциями getopt() */

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
	printf(" -e \t примеры использования программы\n");
	printf(" -h \t Вывод этого сообщения\n\n");
	exit( EXIT_FAILURE );
}

void example(char *progname) 
{
	printf("%s \"Some message to encode\" -k \"RANDOM\"\n", progname);
	printf("%s -d \"jozh aqjsnjs ff drfcpv\" -k \"RANDOM\"\n", progname);
	printf("%s \"jozh aqjsnjs ff drfcpv\" -d\n", progname);
	printf("%s -f \"to_encode.txt\" -k \"RANDOM\"\n", progname);
	printf("%s -k \"RANDOM\" -d -f \"to_decode.txt\"\n", progname);
	printf("%s -d -f \"to_decode.txt\" -k \"RANDOM\" -o \"decoded.txt\"\n", progname);
	exit( EXIT_FAILURE );
}

int main( int argc, char *argv[] )
{
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
	global_args.msg		 = NULL;
	
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
			
			case 'e':
				example(argv[0]);
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

	for (i = optind; i < argc; i++)
	{
		if (argv[i][0] != '-') 
		{
			/* printf("default = %s\n\n", argv[i]); */
			global_args.msg = argv[i];
			break;
		}
	}
	
	printf ("k = %s\n", global_args.key_string);
	printf ("d = %d\n", global_args.decryption);
	printf ("f = %s\n", global_args.in_filename);
	printf ("o = %s\n", global_args.out_filename);
	printf ("msg = %s\n", global_args.msg);

	
	/* for (i = 0; i < argc; i++) */
	/* 	printf ("argv = %s\n", argv[i]); */
	
	return EXIT_SUCCESS;
}
