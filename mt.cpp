#include <vector>
#include <cstdio>
#include <cstring>

struct State
{
	int q1;
	char c;
	char a;
	int q2;
};

int main()
{
	const int MAX_LINE_LEN = 100;

	int curPos = 0;
	int curState = 0;
	char line[MAX_LINE_LEN + 2]; // \n + \0
	std::vector<State> states;
	State state;
	
	for (int i = 0; i < MAX_LINE_LEN + 2; ++i)
		line[i] = ' ';

	fgets(line, MAX_LINE_LEN, stdin);

	curPos = strlen(line) - 1; // учитывая \n
	line[curPos] = ' ';
	line[curPos + 1] = ' ';
	line[MAX_LINE_LEN + 1] = '\0';

	while (scanf("%d,%c,%c,%d", &state.q1, &state.c, &state.a, &state.q2) == 4)
		states.push_back(state);

	while (true)
	{
		int stateInd = -1;

		for (int i = 0; i < states.size(); ++i)
		{
			if (states[i].q1 == curState && states[i].c == line[curPos])
			{
				stateInd = i;

				break;
			}
		}

		if (stateInd == -1)
		{
			printf("Error. State not found for '%d' and '%c'\n", curState, line[curPos]);

			break;
		}

		State& state = states[stateInd];

		if (state.q1 == state.q2 && state.c == state.a)
		{
			printf("Stopped\n");

			break;
		}

		if (state.a == '<')
			--curPos;
		else if (state.a == '>')
			++curPos;
		else
			line[curPos] = state.a;

		curState = state.q2;

		printf("%s\n", line);
		//printf("%*s^\n", curPos, "");
	}

	return 0;
}
