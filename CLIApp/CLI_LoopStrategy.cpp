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
	printf("[���� ������ ���� ���� ȯ���մϴ�...]\n");
	while (true)
	{
		int n = 0;
		printf("[�ùķ��̼� �� �˼��� ���� �Է��Ͻʽÿ�...(����� 0 �Է�)] : ");
		scanf_s("%d", &n);
		if (!n) break;

		// Allocation
		printf("[���� ���� �ùķ��̼� �غ���...]\n");
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
		printf("[���� ���� �ùķ��̼��� �����մϴ�...]\n");
		int count = 0;
		int maxLoopCount = (n / 2);
		int foundCount = 0;
		int curLoop, paperNumber, nextNumber;
		while (n > count)
		{
			curLoop = paperNumber = nextNumber = 0;
			printf("[%d��° �˼� ����...]\n", count + 1);
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
			printf("[%d��° �˼� ����...]\n", count + 1);
			++count;
		}
		printf("[���� ���� �ùķ��̼��� �����մϴ�...]\n");

		// Statistics
		printf("[���� ���� �ùķ��̼��� ����� ����մϴ�...]\n");
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
		printf("[�˼��� �ڽ��� ��ȣ�� ã�� Ȯ��] : %.2lf\n", findProb);
		printf("[�˼����� ��� ���� Ƚ��] : %.2lf\n", avgLoop);
		printf("[�˼����� �ִ� ���� Ƚ��] : %d\n", maxLoop);
		printf("[�˼����� �ּ� ���� Ƚ��] : %d\n", minLoop);
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