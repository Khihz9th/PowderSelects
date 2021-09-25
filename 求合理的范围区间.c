#include <stdio.h>

#define MONTH 12
#define BOOLTRUE 1
#define BOOLFALSE 0
#define FIX_ARANGE_MAX 1

int arrayOrderf(int original[], int selected[], int changeTime, int fixValue);
void debugPrintArrayf(int a[], int changeTime);
int radiusf(int a[], int length, int fixValue);

int main()
{
	int arrayOfOriginalValue[MONTH] = { 896880,	242960,	643280,	696560,	640160,	679760,	578800,	667440,	541120,	608400};
	int arrayOfSelected[MONTH] = { 0 };
	int fixValue;

	fixValue = arrayOrderf(arrayOfOriginalValue, arrayOfSelected, MONTH, FIX_ARANGE_MAX);
	debugPrintArrayf(arrayOfSelected, MONTH - fixValue );

	int numOfaverge;
	numOfaverge = sumOfAveragef(arrayOfSelected, MONTH, fixValue);

	int radiusAverage;
	int Output[MONTH] = { 0 };
	radiusAverage = radiusf(arrayOfSelected, MONTH, fixValue);

	int errNumber;
	errNumber = arrayOrderf(arrayOfSelected, Output, MONTH - fixValue, numOfaverge - (int)1.5*radiusAverage);
	printf("\n");
	printf("平均数是%d，半径是%d", numOfaverge,radiusAverage);
	printf("\n");
	debugPrintArrayf(Output, MONTH - fixValue - errNumber);
	printf("\n");
	printf("第一次过滤异常数据%d个，第二次过滤异常数据%d个，功率约为%.2lfkW.", \
		fixValue, errNumber,  Output[0] / (0.81 * 30000));
}

int arrayOrderf(int original[], int selected[], int changeTime, int fixValue)
{
	/*过滤掉original数组的小于fixValue的数，并将剩下的数组按从小到大的顺序排列，返回被过滤的数的个数numErr*/
	int numErr = 0;
	int b = 0;
	
	for (int i = 0; i < changeTime; i++)
	{
		//printf("original[%d] = %d \n", i, original[i]);
		if (original[i] < fixValue)
		{
			numErr++;
			continue;
		}
		if (b == 0)
		{
			selected[0] = original[i];
			//printf("selected[0] = %d \n ", selected[0]);
			b = 1;
			continue;
		}
		for (int j = 0; j < i - numErr + 1; j++) 
		{
			if (original[i] > selected[j]) 
			{
				continue;
			}
			else 
			{
				for (int k = i - numErr; k > j ; k--) selected[k] = selected[k - 1];
				selected[j] = original[i];
				break;
			}
		}
		if (selected[i - numErr] == 0) selected[i - numErr] = original[i];
	}
	return numErr;
}

void debugPrintArrayf(int a[], int changeTime) 
{
	/*输出一个数组中的前changeTime个*/
	for (int i = 0; i < changeTime; i++) printf("%d ", a[i]);
}

int sumOfAveragef(int a[], int length,int fixValue)
{
	/*去掉两个最大值和两个最小值，再计算并返回它们的平均值*/
	int calTime = length - fixValue;
	if (calTime < 5) return -1;
	int sum = 0;
	for (int i = 1; i < calTime - 2; i++) sum += a[i];
	return sum / (calTime - 4);
}

int radiusf(int a[], int length, int fixValue)
{
	int half = (length - fixValue) / 2;
	int sum = 0, odd = BOOLFALSE;
	printf("%d \n", half);
	if (((length - fixValue) % 2) == 1) odd = BOOLTRUE;
	for (int i = 1; i < half; i++) {
		sum += a[half + i + odd] - a[i];
		printf("%d-%d=%d,sum=%d\n", a[half + i + odd], a[i], a[half + i + odd] - a[i], sum);
	}
	return sum / (half - 1);
}
