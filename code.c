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
 *
 * Результаты выдавать в виде текста в формате: 
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
#include <string.h>
#include <stdlib.h>		/* для EXIT_SUCCESS и EXIT_FAILURE */
#include <unistd.h>		/* для функции getopt() */

#define MAXBUF  5000		/* максимальная длина буфера */
typedef enum {false, true} bool;

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
	printf("\nИспользование:\n\n");
	printf("%s [ключ] \n\n", progname);
	printf("Ключи:\n");
	printf(" -k \t ключ шифровки/дешифровки\n");
	printf(" -d \t ключ включения режима дешифровки\n");
	printf(" -f \t файл для чтения сообщения\n");
	printf(" -o \t файл для записи сообщения\n");
	printf(" -e \t примеры использования программы\n");
	printf(" -h \t вывод этого сообщения\n\n");
	exit( EXIT_FAILURE );
}

void example(char *progname) 
{
	printf("\nПримеры использования программы:\n\n");
	printf("%s \"Some message to encode\" -k \"RANDOM\"\n", progname);
	printf("%s -d \"jozh aqjsnjs ff drfcpv\" -k \"RANDOM\"\n", progname);
	printf("%s \"jozh aqjsnjs ff drfcpv\" -d\n", progname);
	printf("%s -f \"to_encode.txt\" -k \"RANDOM\"\n", progname);
	printf("%s -k \"RANDOM\" -d -f \"to_decode.txt\"\n", progname);
	printf("%s -d -f \"to_decode.txt\" -k \"RANDOM\" -o \"decoded.txt\"\n", progname);
	printf("\n");
	exit( EXIT_FAILURE );
}

void validate_args(int argc, char *argv[])
{
	/* Инизиализация структуры 
	 */
	global_args.key_string	 = NULL;		/* -k ключ */
	global_args.decryption	 = 0;			/* -d ключ */
	global_args.in_filename	 = NULL;		/* -o ключ */
	global_args.in_file	 = NULL;
	global_args.out_filename = NULL;		/* -f ключ */
	global_args.out_file	 = NULL;
	global_args.msg		 = NULL;
	
	int opt = 0;
	opterr	= 0;		/* отключим вывод ошибок в getopt()*/
	
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
}

int main( int argc, char *argv[] )
{
	if (argc < 2)			/* если ключи не заданы */
		usage(argv[0]);

	validate_args(argc, argv);	/* проверка входных параметров */
	
	int	i = 0;
	int	j = 0;
	char	s[MAXBUF];

	for (i = optind; i < argc; i++)
	{
		if (argv[i][0] != '-') 
		{
			global_args.msg = argv[i];
			break;
		}
	}
	printf ("k = %s\n", global_args.key_string);
	printf ("d = %d\n", global_args.decryption);
	printf ("f = %s\n", global_args.in_filename);
	printf ("o = %s\n", global_args.out_filename);
	printf ("msg = %s\n", global_args.msg);


	/* Создание таблицы Виженера на алфавите латиницы */

	int shift = 0;
	/* Таблица Виженера */
	char **tabula_recta = (char **) malloc(sizeof(char *) * 26);
	
	for (i = 0; i < 26; i++)
		tabula_recta[i] = (char *) malloc(sizeof(char) * 26);

	const char *alfabet = "abcdefghijklmnopqrstuvwxyz"; 

	/* Заполнение таблицы */
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++) 
		{
			shift = j + i;
			if (shift >= 26) 
				shift = shift % 26;
			tabula_recta[i][j] = alfabet[shift];
		}
	}



	/* Если ключ d не задан значит выбрана шифрация 
	 */
	if (global_args.decryption == 0)
	{
		if (global_args.key_string == NULL)	/* если -k не задан */
			usage(argv[0]);

		/* Если задан ключ f и в тоже время указано сообщение
		 */
		if (global_args.in_filename != NULL && global_args.msg != NULL)
			usage(argv[0]);

		if (global_args.in_filename == NULL)	/* если -f не задан */
		{
			if (global_args.msg != NULL)	/* если msg есть */
			{
				/* записываем в s сообщение из msg 
				 * предотвратим переполнение буфера
				 * а также выставим в ручную \0
				 */
				strncpy (s, global_args.msg, sizeof(s) - 1);
				s[sizeof(s) - 1] = '\0';
				
				printf ("s msg = %s\nn", s);
			}
			else 
				usage(argv[0]);
		}
		else		/* читаем строку из файла */
		{
			if ( (global_args.in_file = 
				fopen(global_args.in_filename, "r")) == NULL)
			{
				printf("Ошибка чтения файла %s \n", 
						global_args.in_filename);
				return EXIT_FAILURE;
			}
			fscanf (global_args.in_file, "%s", s);
			fclose(global_args.in_file);
			printf ("s file = %s\n\n", s);
		}
		
		/*---------*/
		/* Шифруем */
		/*---------*/

		
        // + 1 для терминального нуля в конце
        char	result[strlen(s) + 1];		//Строка - результат
	char	*key = global_args.key_string;		//Строка - ключ 
        //char	*key_on_s = "";
        char	key_on_s[strlen(s) + 1];
        bool	flag;
	int	x= 0, y = 0;		//Координаты нового символа из таблицы Виженера
	int	registr = 0; //Регистр символа
	char	dublicat; //Дубликат прописной буквы

        key_on_s[0] = '\0' ;
        result[0] = '\0' ;

	//Формирование строки, длиной шифруемой, состоящей из повторений ключа
	for (i = 0; i < strlen(s); i++)
        {
            size_t cur_len = strlen(key_on_s);
            if(cur_len < strlen(s)) {
                key_on_s[cur_len] = key[i % strlen(key)];
                key_on_s[cur_len + 1] = '\0';
            }
        }
		
	//Шифрование при помощи таблицы
	for (i = 0; i < strlen(s); i++)
	{
		//Если нешифруемый символ
		if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
		{
			size_t cur_len = strlen(result);
			if(cur_len < strlen(s)) {
				result[cur_len] = s[i];
				result[cur_len + 1] = '\0';
			}
		}
		else
		{
			//Поиск в первом столбце строки, начинающейся с символа ключа
			int l = 0;
			flag = false;

			//Пока не найден символ
			while ((l < 26) && (flag == false))
			{
				//Если символ найден
				if (key_on_s[i] == tabula_recta[l][0])
				{
					//Запоминаем в х номер строки
					x = l;
					flag = true;
				}
				l++;
			}
			//Уменьшаем временно регистр прописной буквы
			if (((int)(s[i]) <= 90) && ((int)(s[i]) >= 65))
			{
				dublicat = (char)((int)(s[i]) + 32);
				registr = 1;
			}
			else
			{
				registr = 0;
				dublicat = s[i];
			}
			l = 0;
			flag = false;
			//Пока не найден столбец в первой строке с символом строки
			while ((l < 26) && (flag == false))
			{
				if (dublicat == tabula_recta[0][l])
				{
					//Запоминаем номер столбца
					y = l;
					flag = true;
				}
				l++;
			}
			//Увеличиваем регистр буквы до прописной
			if (registr == 1)
			{
				/* Изменяем символ на первоначальный 
				 * регистр
				 */
				dublicat = tabula_recta[x][y] - 32;

				/* допишем в result символ из dublicat
				 * вычислим текущую длинну result 
				 * и сравним с максимальной - 2 
				 * (2 потомучто, один символ из dublicat
				 * второй это терминальный ноль).
				 * код эквивалентен следующему выражению
				 * result += dublicat;
				 */
				size_t cur_len = strlen(result);
				if(cur_len < strlen(s)) {
					result[cur_len] = dublicat;
					result[cur_len + 1] = '\0';
				}
			}
			else
			{
				size_t cur_len = strlen(result);
				if(cur_len < strlen(s)) {
					result[cur_len] = 
						tabula_recta[x][y];
					result[cur_len + 1] = '\0';
				}
			}
		}
	}

	printf("\n\nEncryption complete!\n");
	printf("Result: %s\n\n", result);




	}








	return EXIT_SUCCESS;
}
