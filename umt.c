#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _kFour
{
	int q1;
	char a;
	char v;
	int q2;
} Four;

typedef struct _kMachine
{
	int q;
	int pos;
} Machine;

int main(int argc, char* argv[])
{
	const unsigned PROGS = 1000;
	char* lenta;
	int i, ch, cmdFound, len = 0, running = 1;
	Four p[PROGS], tmp;
	Machine m;
	int LEN = 100;


	FILE* prgFile = NULL;
	FILE* inFile = NULL;
	FILE* outFile = NULL;

	if(argc < 4)
	{
		printf("Usage: %s program inputFile outputFile [len = 100]\n", argv[0]);

		return 0;
	}

	if(argc == 5)
	{
		LEN = atoi(argv[4]);
	}

	lenta = (char*)malloc(LEN);

	inFile = fopen(argv[2], "rt");
	prgFile = fopen(argv[1], "rt");
	outFile = fopen(argv[3], "wt");

	if(prgFile == NULL)
	{
		printf("Ошибка открытия файла с программой\n");

		return 0;
	}

	if(inFile == NULL)
	{
		printf("Ошибка открытия файла с входными данными\n");
		return 0;
	}

	if(outFile == NULL)
	{
		printf("Ошибка открытия файла с выходными данными\n");
		return 0;
	}



	//printf("Input Line:\n");
	
	for (i = 0; i < LEN; i++) lenta[i] = ' ';

	while ((ch = fgetc(inFile)) != EOF)
	{
		if (ch == '\n' || len == LEN) break;

		lenta[len++] = ch;
	}

	m.q = 0;
	m.pos = len;
	lenta[LEN] = '\0';
	i = 0;

	//printf("Input commands:\n");

	while (fscanf(prgFile, "%d,%c,%c,%d", &tmp.q1, &tmp.a, &tmp.v, &tmp.q2) != EOF)
	{
		if (i == PROGS) break;

		p[i++] = tmp;
	}

	while (running)
	{
		cmdFound = 0;

		for (i = 0; i < PROGS; i++)
		{
			if (m.q == p[i].q1)
			{
				if (lenta[m.pos] == p[i].a)
				{
					if (p[i].q1 == p[i].q2 && p[i].a == p[i].v)
					{
						//printf("Machine stopped\n");

						cmdFound = 1;
						running = 0;

						break;
					}

					switch (p[i].v)
					{
						case '<':
						{
							if (m.pos > 0) m.pos--;
							else
							{
								printf("[Error] Out of range (left side)\n");

								running = 0;
							}
						}
						break;

						case '>':
						{
							if (m.pos < LEN) m.pos++;
							else
							{
								printf("[Error] Out of range (right side)\n");

								running = 0;
							}
						}
						break;

						case '#':
						{
							//printf("Machine stopped\n");

							running = 0;
						}
						break;

						default: lenta[m.pos] = p[i].v; break;
					}

					m.q = p[i].q2;
					cmdFound = 1;

					break;
				}
			}
		}

		if (!cmdFound)
		{
			printf("[Error] Command for state '%d' and letter '%c' not found\n", m.q, lenta[m.pos]);

			break;
		}
	}

	fprintf(outFile, "%s\n", lenta);

	fclose(prgFile);
	fclose(inFile);
	fclose(outFile);

	return 0;
}
