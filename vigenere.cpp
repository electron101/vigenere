#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std;
int main()
{
	int k; //Переменная выбора - шифрование/дешифрование
	string result = ""; //Строка - результат
	string key = ""; //Строка - ключ 
	string key_on_s = "";
	bool flag;
	int x = 0, y = 0; //Координаты нового символа из таблицы Виженера
	int registr = 0; //Регистр символа
	char dublicat; //Дубликат прописной буквы
	
	/* Создание таблицы Виженера на алфавите латиницы */
	int shift = 0;
	char **tabula_recta = new char *[26]; //Таблица Виженера
	for (int i = 0; i < 26; i++)
		tabula_recta[i] = new char [26];

	string alfabet = "abcdefghijklmnopqrstuvwxyz"; //Алфавит латиницы

	/* Заполнение таблицы */
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
		{
			shift = j + i;
			if (shift >= 26) 
				shift = shift % 26;
			tabula_recta[i][j] = alfabet[shift];
		}

	cout<<"Enter 1 for encryption and decryption of 2\n";
	cin>>k; 

	switch (k) //Если k
	{
		case 1: //Если выбрано шифрование
		{
			cout<<"Enter key encryption\n";
			cin>>key;
			cout<<"Read of file...\n";
			setlocale(LC_ALL,"Russian");//Чтение файла
			string s; //Строка считанная из файла
			ifstream in("Test.txt");
			getline(in,s);
			cout<<"Text of file: \n"<<s<<endl;
			in.close(); 
			cout<<"Reading complete!\n";
			cout<<"Encryption...\n";
	
			//Формирование строки, длиной шифруемой, состоящей из повторений ключа
			for (int i = 0; i < s.length(); i++)
				key_on_s += key[i % key.length()];
			
			//Шифрование при помощи таблицы
			for (int i = 0; i < s.length(); i++)
			{
				//Если нешифруемый символ
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
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
						//Изменяем символ на первоначальный регистр
						dublicat = char((int)(tabula_recta[x][y]) - 32);
						result += dublicat;
					}
					else
						result += tabula_recta[x][y];
				}
			}
			cout<<"Encryption complete!\n";
			cout<<"Result:\n";
			cout<<result; //Вывод результата
			break;
		}

		case 2: //Если выбрано дешифрование
		{
			cout<<"Enter key decryption\n";
			cin>>key;
			cout<<"Read of file...\n";
			setlocale(LC_ALL,"Russian");
			string s;
			ifstream in("Test.txt");
			getline(in,s);
			cout<<"Text of file: \n"<<s<<endl;
			in.close();
			cout<<"Reading complete!\n";
			cout<<"Decryption...\n";
			//Формирование строки, длиной дешифруемой, состоящей из повторений ключа
			for (int i = 0; i < s.length(); i++)
			{
				key_on_s += key[i % key.length()];
			}
			
			//Дешифрование при помощи таблицы
			for (int i = 0; i < s.length(); i++)
			{
				//Если недешифруемый символ
				if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
					result += s[i];
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
					//Пока не найден столбец в x строке с символом строки
					while ((l < 26) && (flag == false))
					{
						if (dublicat == tabula_recta[x][l])
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
						//Изменяем символ на первоначальный регистр
						dublicat = char((int)(tabula_recta[0][y]) - 32);
						result += dublicat;
					}
					else
						result += tabula_recta[0][y];
				}
			} 
			cout<<"Decryption complete!\n";
			cout<<"Result:\n";
			cout<<result; //Вывод результата
			break;
		}
		default: //Если ошибочное значение
		{
			cout<<"Error value\n";
			break;
		}
	}
	return 0;
}
