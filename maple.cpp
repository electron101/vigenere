#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<string.h>
#include	<locale.h>
#include	<windows.h>

#define		SIZE_COMMAND	70		/* размер имени команды */
#define		SIZE_INFO	4096		/* размер описания */

/* Прототипы функций */
void		add_record(void);
void		lookup(void);
char		menu(void);

char		command_name[SIZE_COMMAND];	/* имя комманды */
const char	*file_name = "maple_commands";	/* имя файла с данными */

/* Структура для хранения записей в файле */
struct	one_record_data
{
	char command[SIZE_COMMAND];		/* имя команды */
	char info[SIZE_INFO];			/* описание команды */
};


/*
* usage() -		Правила использования программы.
*/
void usage()
{
	printf("Использование:\n");
	printf("По нажатию клавиш:\n");
	printf(" a \t Доавить команду maple и её описание\n");
	printf(" l \t Вывод описания команды maple\n");
	printf(" q \t Выход\n\n");
}

/*
* menu() -	Функция меню.
*/
char menu()
{
	char ch = 0;
	do
	{
		printf("(a) Добавить, (l) Показать, (q) Выход: ");
		fflush(stdin);					/* Очистка буфера клавиатуры */
		ch = tolower(getchar());
		printf("\n");
	} 
	while (ch != 'q' && ch != 'a' && ch != 'l');
	return ch;
}

/*
* add_record() -	Добавление новой записи в файл.
*/
void add_record(void)
{
	FILE	*fp;
	struct	one_record_data	file_data;	/* структура записи */

	/*
	* Открываем файл на добавление, если
	* операция прошла успешно идём дальше
	* если нет выдаём ошибку и выходим
	*/
	if ((fp = fopen(file_name, "a")) == NULL)
	{
		printf("Ошибка чтения файла \n");
		exit(1);
	}

	printf("Введи добавляемую команду: ");
	fscanf(stdin, "%s", file_data.command);
	fscanf(stdin, "%*c"); /* удаление возврата каретки из потока ввода */
	printf("Введи её описание: ");
	/* Читает все символы пока не встретит перевод на новую строку */
	fscanf(stdin, "%[^\r\n]", file_data.info);
	fscanf(stdin, "%*c");

	/* запись в файл */
	fprintf(fp, "%s|%s\n", file_data.command, file_data.info);
	fclose(fp);				/* закрываем файл */
}

/*
* lookup() -		Просмотр описания команды.
*/
void lookup(void)
{
	FILE	*fp;
	struct	one_record_data	file_data;	/* структура записи */

	/*
	* Открываем файл на чтение, если
	* операция прошла успешно идём дальше
	* если нет выдаём ошибку и выходим
	*/
	if ((fp = fopen(file_name, "r")) == NULL)
	{
		printf("Ошибка чтения файла \n");
		exit(1);
	}

	printf("Введите имя команды: ");
	scanf("%s", command_name);

	/*
	* Пока не достигнут конец файла читаем
	* из него строку и записываем её в структуру
	*/
	while (!feof(fp))
	{
		/*
		* %[^|] - читает до символа | и записывает
		* в первое поле структуры.
		* %[^\r\n] - читает всё что осталось пока не
		* встретит перевод на новую строку и записывает
		* во второе поле структуры.
		* символ | стоящий между двумя этими выражениями
		* означает то что он из файла считываться не будет.
		*/
		fscanf(fp, "%[^|]|%[^\r\n]\n", file_data.command, file_data.info);
		if (!strcmp(command_name, file_data.command))
		{
			printf("%s\n%s\n", file_data.command, file_data.info);
			break;
		}
	}

	fclose(fp);				/* закрываем файл */
}

/*
* main() -		Справка команд maple.
*/
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//setlocale(LC_ALL, "");
	usage();				/* правила использования */

	char choice;				/* какая клавиша нажата */
	do
	{
		choice = menu();		/* вывести меню */
		/*
		* В зависимости от нажатой клавиши
		* запускаем нужную функцию
		*/
		switch (choice)
		{
		case 'a': add_record(); /* функция добавления */
			break;
		case 'l': lookup();	/* функция просмотра */
			break;
		}
	} while (choice != 'q');			/* если клавиша = q, выходим */

	return 0;
}