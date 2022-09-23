#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using std::vector;

struct BOX
{
	int iPaperNumber;
};

struct PRISONER
{
	int iNumber;
	int iLoop;
	bool bFound;
};

void DistributeNumber(BOX*, int);

int main()
{
	srand((unsigned int)time(NULL));
	printf("[루프 전략에 오신 것을 환영합니다...]\n");
	while (true)
	{
		int n = 0;
		printf("[시뮬레이션 할 죄수의 수를 입력하십시오...(종료시 0 입력)] : ");
		scanf_s("%d", &n);
		if (!n) break;

		// Allocation
		printf("[루프 전략 시뮬레이션 준비중...]\n");
		PRISONER* prisoner = new PRISONER[n];
		for (int i = 0; i < n; ++i)
		{
			prisoner[i].iNumber = (i + 1);
			prisoner[i].iLoop = 0;
			prisoner[i].bFound = false;
		}

		BOX* boxes = new BOX[n];
		DistributeNumber(boxes, n);

		// Main Logic
		printf("[루프 전략 시뮬레이션을 시작합니다...]\n");
		int count = 0;
		int maxLoopCount = (n / 2);
		int foundCount = 0;
		int curLoop, paperNumber, nextNumber;
		while (n > count)
		{
			curLoop = paperNumber = nextNumber = 0;
			printf("[%d번째 죄수 입장...]\n", count + 1);
			nextNumber = prisoner[count].iNumber;
			while (maxLoopCount > curLoop++)
			{
				prisoner[count].iLoop = curLoop;
				paperNumber = boxes[nextNumber - 1].iPaperNumber;
				if (paperNumber == prisoner[count].iNumber)
				{
					++foundCount;
					prisoner[count].bFound = true;
					break;
				}

				nextNumber = paperNumber;
			}
			printf("[%d번째 죄수 퇴장...]\n", count + 1);
			++count;
		}
		printf("[루프 전략 시뮬레이션을 종료합니다...]\n");

		// Statistics
		printf("[루프 전략 시뮬레이션의 결과를 출력합니다...]\n");
		double findProb = (double)foundCount / (double)n;
		int maxLoop = INT_MIN;
		int minLoop = INT_MAX;
		int totalLoop = 0;
		for (int i = 0; i < n; ++i)
		{
			if (prisoner[i].iLoop > maxLoop)
				maxLoop = prisoner[i].iLoop;
			if (prisoner[i].iLoop < minLoop)
				minLoop = prisoner[i].iLoop;

			totalLoop += prisoner[i].iLoop;
		}
		double avgLoop = (double)totalLoop / (double)n;

		printf("**************************************************\n");
		printf("[죄수가 자신의 번호를 찾을 확률] : %.2lf\n", findProb);
		printf("[죄수들의 평균 루프 횟수] : %.2lf\n", avgLoop);
		printf("[죄수들의 최대 루프 횟수] : %d\n", maxLoop);
		printf("[죄수들의 최소 루프 횟수] : %d\n", minLoop);
		printf("**************************************************\n");

		// Release
		delete[] prisoner;
		delete[] boxes;
	}

	return 0;
}

void DistributeNumber(BOX* boxes, int size)
{
	vector<int> numberPapers;
	for (int i = 0; i < size; ++i)
		numberPapers.push_back(i + 1);

	int count = 0;
	while (size > count)
	{
		int paperNumber = rand() % size + 1;
		vector<int>::iterator iter = std::find(numberPapers.begin(), numberPapers.end() - 1, paperNumber);
		boxes[count++].iPaperNumber = *iter;
		numberPapers.erase(iter);
	}
}