#pragma once
#include<stdio.h>
#pragma once
#include<string.h>
#pragma once
int logpage(int* p_pMp);//�û���½ҳ��
#pragma once

/*ȱ���û�����������txt�����ݴ����ϲ������ر����㣬���Խ���ʹ��csv�ļ�*/
#pragma once
struct user{
	char name[6];
	char pass[6];
	char rname[12];
	int star;//1Ϊ����Ա,2Ϊ�߼��û�,3Ϊ��ͨ�û�
	int naL;//�����ֳ�
	int paL;//�����ֳ�
}ren[3] = {
	{"star","123","���õ�",1,4,3},
	{"vip","vip","����",2,3,3},
	{"norm","wan5","��",3,4,5} };

//��¼��Ϣ�⣬����ʽ���ú�ѳ�ʼֵע��#pragma once
#pragma once
struct user* pren = ren;
//return pren;
//*pren = &ren[3];