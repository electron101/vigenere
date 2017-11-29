/* gcc test_opt.c -o test */
/* ./test -a "zzasdfasdfasdfasdf sssas" -C -d -b /home/grom/CODING/cpp/qr_algoritm/qr_algoritm.cpp */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int rez=0;

	opterr=0;
	int i = 1;
	while ( (rez = getopt(argc,argv,"ab:C::d")) != -1)
	{
		if (argv[i][0] != '-') 
		{
			printf("default = %s\n\n", argv[i]);
			/* break; */
		}
		switch (rez)
		{
			case 'a': printf("found argument \"a\".\n"); break;
			case 'b': printf("found argument \"b = %s\".\n",optarg); break;
			case 'C': printf("found argument \"C = %s\".\n",optarg); break;
			case 'd': printf("found argument \"d\"\n"); break;
			case '?': printf("Error found !\n");break;
			/* default:  printf("found argument default = %s\".\n",optarg); break; */
		};
		
		i++;
	};

};

