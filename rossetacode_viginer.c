#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* struct FreqArray { */
/* 	char _char_freq; */
/* 	double _double_freq; */
/* }; */
/* struct FreqArray freq[26]; */

typedef struct _freq {
	char _char_freq;
	double _double_freq;
} FreqArray;


double targets[26];
double sortedTargets[26];
FreqArray freq[26];

typedef struct _output {
	char *str1;
	char *str2;
} output;

FreqArray frequency(const char *input) 
{
	for (char c = 'A'; c <= 'Z'; ++c) {
		freq[c - 'A']._char_freq = c;
		freq[c - 'A']._double_freq = 0;
	}

	for (size_t i = 0; i < strlen(input); ++i)
		freq[input[i] - 'A']._double_freq++;

	return *freq;
}

double correlation(const char *input) 
{
	double result = 0.0;

	frequency(input);

	int i = 0;
	int j = 0;
	/* Сортируем по возрастанию частоты символа 
	 * ( второго поля структуры)
	 */
	for(i = 0 ; i < 26 - 1; i++) { 
		/* сравниваем два соседних элемента. */
		for(j = 0 ; j < 26 - i - 1 ; j++) {  
			if(freq[j]._double_freq > freq[j+1]._double_freq) {
				// если они идут в неправильном порядке, то  
				//  меняем их местами. 
				FreqArray tmp_freq = freq[j];
				freq[j] = freq[j+1] ;
				freq[j+1] = tmp_freq; 
			}
		}
	}

	for (size_t i = 0; i < 26; ++i)
		result += freq[i]._double_freq * sortedTargets[i];

	return result;
}

void VigenereAnalyser(double targetFreqs[26]) 
{
	size_t i;
	size_t j;
	for (i = 0; i < 26; i++)
	{
		targets[i] = targetFreqs[i];
		sortedTargets[i] = targets[i];
	}
	
	/* Сортируем по возрастанию */
	for(i = 0 ; i < 26 - 1; i++) { 
		for(j = 0 ; j < 26 - i - 1 ; j++) {  
			if(sortedTargets[j] > sortedTargets[j+1]) {
				/* по возрастанию */
				double tmp	   = sortedTargets[j];
				sortedTargets[j]   = sortedTargets[j+1] ;
				sortedTargets[j+1] = tmp; 
			}
		}
	}
}

output analyze(char *input) 
{
	output result_output;
	char cleaned[strlen(input) + 1];
	size_t i;
	for (i = 0; i < strlen(input); ++i) 
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			size_t cur_len = strlen(cleaned);
			if(cur_len < strlen(input)) {
				cleaned[cur_len] = input[i];
				cleaned[cur_len + 1] = '\0';
			}

		}
		else if (input[i] >= 'a' && input[i] <= 'z')
		{
			size_t cur_len = strlen(cleaned);
			if(cur_len < strlen(input)) {
				cleaned[cur_len] = input[i] + 'A' - 'a';
				cleaned[cur_len + 1] = '\0';
			}
		}
	}

	size_t bestLength = 0;
	double bestCorr = -100.0;

	/* Предположим, что если символов меньше 20 символов
	 * за столбец, ключ слишком длинный, чтобы угадать
	 */
	for (i = 2; i < strlen(cleaned) / 20; ++i) 
	{
		char **pieces;
		pieces = (char **) malloc(i * sizeof(char *));
		int n;	/* n - колличество строк в массиве */
		/* m - длина каждой строки + 1 для запаса */
		int m = (int) strlen(cleaned) / i  + 1;
		for (n = 0; n < i; n++) {
			pieces[n] = (char *) malloc(m * sizeof(char));
		}

		for (size_t j = 0; j < strlen(cleaned); ++j) {
			size_t cur_len = strlen(pieces[j % i]);
			if(cur_len < m) {
				pieces[j % i][cur_len] = cleaned[j];
				pieces[j % i][cur_len + 1] = '\0';
			}
		}

		/* Корреляция искусственно возрастает для меньших
		 * фрагменты / более длинные ключей
		 */
		double corr = -0.5*i;
		for (size_t j = 0; j < i; ++j)
			corr += correlation(pieces[j]);

		if (corr > bestCorr) 
		{
			bestLength = i;
			bestCorr = corr;
		}
	}

	if (bestLength == 0)
	{
		result_output.str1 = "Текст слишком короткий для анализа";
		result_output.str2 = "";
		return result_output;
	}

	char *pieces[bestLength];
	/* m - длина строки полученной при разделении 
	 * всего шифрованного текста на отрезки количеством bestLength.
	 * + 1 для запаса
	 */
	int m = (int) strlen(cleaned) / bestLength  + 1;
	for (i = 0; i < strlen(cleaned); ++i)
	{
		size_t cur_len = strlen(pieces[i % bestLength]);
		if(cur_len < m) {
			pieces[i % bestLength][cur_len] = cleaned[i];
			pieces[i % bestLength][cur_len + 1] = '\0';
		}
		
	}

	/* FreqArray *freqs; */
	/* freqs = (FreqArray*)malloc(bestLength * sizeof(FreqArray)); */
	FreqArray *freqs[bestLength];
	/* freqs = (FreqArray*)malloc(bestLength * sizeof(FreqArray)); */

	for (i = 0; i < bestLength; ++i)
		freqs[i] = frequency(pieces[i]); 

	char *key = "";
	for (i = 0; i < bestLength; ++i) 
	{
		int ii = 0;
		int jj = 0;
		for(ii = 0 ; ii < 26 - 1; ii++) { 
			/* сравниваем два соседних элемента. */
			for(jj = 0 ; jj < 26 - ii - 1 ; jj++) {  
				if(freq[jj]._double_freq < freq[jj+1]._double_freq) {
					// если они идут в неправильном порядке, то  
					//  меняем их местами. 
					FreqArray tmp_freq = freq[jj];
					freq[jj] = freq[jj+1] ;
					freq[jj+1] = tmp_freq; 
				}
			}
		}

		size_t m = 0;
		double mCorr = 0.0;
		for (size_t j = 0; j < 26; ++j) 
		{
			double corr = 0.0;
			char c = 'A' + j;
			for (size_t k = 0; k < 26; ++k) 
			{
				int d = (freqs[i][k] - c + 26) % 26;
				corr += freqs[i][k].second * targets[d];
			}

			if (corr > mCorr) 
			{
				m = j;
				mCorr = corr;
			}
		}

		key += m + 'A';
	}

	string result = "";
	for (size_t i = 0; i < cleaned.size(); ++i)
		result += (cleaned[i] - key[i % key.length()] + 26) % 26 + 'A';
	return make_pair(result, key);
}



int main() 
{
	char input[] =
		"MOMUD EKAPV TQEFM OEVHP AJMII CDCTI FGYAG JSPXY ALUYM NSMYH"
		"VUXJE LEPXJ FXGCM JHKDZ RYICU HYPUS PGIGM OIYHF WHTCQ KMLRD"
		"ITLXZ LJFVQ GHOLW CUHLO MDSOE KTALU VYLNZ RFGBX PHVGA LWQIS"
		"FGRPH JOOFW GUBYI LAPLA LCAFA AMKLG CETDW VOELJ IKGJB XPHVG"
		"ALWQC SNWBU BYHCU HKOCE XJEYK BQKVY KIIEH GRLGH XEOLW AWFOJ"
		"ILOVV RHPKD WIHKN ATUHN VRYAQ DIVHX FHRZV QWMWV LGSHN NLVZS"
		"JLAKI FHXUF XJLXM TBLQV RXXHR FZXGV LRAJI EXPRV OSMNP KEPDT"
		"LPRWM JAZPK LQUZA ALGZX GVLKL GJTUI ITDSU REZXJ ERXZS HMPST"
		"MTEOE PAPJH SMFNB YVQUZ AALGA YDNMP AQOWT UHDBV TSMUE UIMVH"
		"QGVRW AEFSP EMPVE PKXZY WLKJA GWALT VYYOB YIXOK IHPDS EVLEV"
		"RVSGB JOGYW FHKBL GLXYA MVKIS KIEHY IMAPX UOISK PVAGN MZHPW"
		"TTZPV XFCCD TUHJH WLAPF YULTB UXJLN SIJVV YOVDJ SOLXG TGRVO"
		"SFRII CTMKO JFCQF KTINQ BWVHG TENLH HOGCS PSFPV GJOKM SIFPR"
		"ZPAAS ATPTZ FTPPD PORRF TAXZP KALQA WMIUD BWNCT LEFKO ZQDLX"
		"BUXJL ASIMR PNMBF ZCYLV WAPVF QRHZV ZGZEF KBYIO OFXYE VOWGB"
		"BXVCB XBAWG LQKCM ICRRX MACUO IKHQU AJEGL OIJHH XPVZW JEWBA"
		"FWAML ZZRXJ EKAHV FASMU LVVUT TGK";

	double english[26] = {
		0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
		0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
		0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
		0.00978, 0.02360, 0.00150, 0.01974, 0.00074
	};

	VigenereAnalyser(english);

	int j = 0;

	struct _output output; 
	output = analyze(input);


	return 0;
}
