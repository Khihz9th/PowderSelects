#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main()
{
	int charge[12]={26480, 31760, 32080 ,48480, 22160, 57120, 70240, 119840, 58240,	48000, 24480};
	int judgeOfCharge[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int levelOfCharge[12] = {0};
	int i, j, l = 0;
	//求数量级 
	for(i = 0; i < 12; i++)
	{
		for(j = 1; charge[i] >= j; j *= 10){
			l++;
		}
		levelOfCharge[i] = l - 1;
		l=0;
	}
	for(i=0;i<12;i++)
	{
		printf("charge[%d]=%d的数量级是10^%d\n ",i,charge[i],levelOfCharge[i]);
	}
	printf("\n");
	//求出现最多的数量级 
	getch();
	system("cls");
	int normal1[12][2]={0};
	normal1[0][0]=levelOfCharge[0];
	normal1[0][1]=1;
	for(i=1;i<12;i++)
	{
		for(j=0;j<i;j++)
		{
			if(normal1[j][0]==levelOfCharge[i])
			{
				normal1[j][1]++;
				break;
			}	
		}
		if(j==i){
			l++;
			normal1[l][0]=levelOfCharge[i];
			normal1[l][1]=1;
		}
	}
	
	for(i=0;i<l+1;i++)
	{
		for(j=0;j<2;j++)
		{
		printf("%d ",normal1[i][j]);
		}
		printf("\n");
	}
	getch();
	system("cls");
	j=0;
	for(i=0;i<11;i++)
	{
		if(normal1[i][1]<normal1[i+1][1]) j=i+1;
	}
	
	printf("\n众数是%d",normal1[j][0]);
	getch();
	system("cls");
	int normalValue[12];
	int s=1;	
	for(i=0;i<normal1[j][0];i++) s*=10;
	printf("\ns=%d\n",s);
	for(i=0;i<12;i++){
		if(charge[i]*10/s>4){
			normalValue[i]=charge[i]/s+1;
		}else{
			normalValue[i]=charge[i]/s;
		}		
	}
	getch();
	system("cls");
	for(i=0;i<12;i++)
	{
		printf(" charge[%d]=%d的特征数字是%d\n ",i,charge[i],normalValue[i]);
	}
	getch();
	system("cls");
	printf("\n");
	int normal2[12][2]={0};
	l=0;
	normal2[0][0]=normalValue[0];
	normal2[0][1]=1;
	for(i=1;i<12;i++)
	{
		for(j=0;j<i;j++)
		{
			if(normalValue[i]==0) break;
			if(normal2[j][0]==normalValue[i])
			{
				normal2[j][1]++;
				break;
			}	
		}
		if(j==i){
			l++;
			normal2[l][0]=normalValue[i];
			normal2[l][1]=1;
		}
	}
	for(i=0;i<l+1;i++)
	{
		for(j=0;j<2;j++)
		{
		printf("%d ",normal2[i][j]);
		}
		printf("\n");
	}
	getch();
	system("cls");
	int tmp;
	for(i=0;i<l;i++){
		for(j=0;j<l-i;j++){
			if(normal2[j][1]<normal2[j+1][1])
			{
				tmp=normal2[j+1][1];	
				normal2[j+1][1]=normal2[j][1];
				normal2[j][1]=tmp;
				
				tmp=normal2[j+1][0];	
				normal2[j+1][0]=normal2[j][0];
				normal2[j][0]=tmp;
			}	
		}
	} 
	getch();
	system("cls");
	printf("\n");
	
	for(i=0;i<l+1;i++)
	{
		for(j=0;j<2;j++)
		{
		printf("%d ",normal2[i][j]);
		}
		printf("\n");
	}
	getch();
	system("cls");
	int judgeCenter;
	if(normal2[0][1]==normal2[1][1])
	{
		judgeCenter=(normal2[0][0]+normal2[1][0])/2;
	}else{
		judgeCenter=normal2[0][0];
	}
	int judgeTop,judgeBottom;
	judgeTop=(judgeCenter+2)*s;
	judgeBottom=(judgeCenter-2)*s;
	for(i=0;i<12;i++){
		if(judgeOfCharge[i]==0) continue;
		if(charge[i]<judgeBottom||charge[i]>judgeTop){
			judgeOfCharge[i]=0;
			printf("%d不在%d~%d范围内\n",charge[i],judgeBottom,judgeTop);
		}else{
			printf("%d在%d~%d范围内\n",charge[i],judgeBottom,judgeTop);
		}
	}
	for(i=0;i<12;i++) printf("%d ",judgeOfCharge[i]);
	getch();
	system("cls");
	int minOutput;
	l=0;
	for(i=0;i<12;i++){	
		if(judgeOfCharge[i]==0) continue;
		if(l==0) {
		l++;
		minOutput=charge[i];
		}
		else if(charge[i]<minOutput) minOutput=charge[i];	
	}
	printf("\n minOutput=%d",minOutput);
}
