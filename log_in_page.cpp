#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#include "log_in_page.h"

//�û����ݱ�

typedef struct{
	char name[13];			//�û���¼����12��Ӣ��������ַ���
	char username[24];		//�û�����������������Ʒ����ҳ����ʾ��
	char password[17];		//�û���¼���루16�����ֻ�Ӣ���ַ���
	int feature;			//0Ϊ����Ա,����Ϊע���û�(������չʱʹ�ã�
	int feature2;			//�ڶ������루0Ϊ�̼ң�1Ϊ��ͨ�û���
}USER;

/*��¼���溯�� ��������ֵΪ0��1��1��ʾ��¼������0��ʾ��¼ʧ��
ͬʱ����ָ��ֱ𷵻��û������ı�ʶ����һ������͵ڶ������룬�ش���ֵ������������Ҫ�����*/

/*�����ռ���ɻ�*/

int log_in_page( int* pfeature) {

	//��¼��Ϣ¼��

	int ret = 0, i;
	FILE* LOG;
	LOG = fopen("D:\\cx4\\loginf.txt", "r");//����·��
	int zrs;
	
	//�жϵ�¼�ļ��Ƿ����
	if (LOG == NULL) {
		printf("��¼��Ϣ�����ʧ��");
		return ret;//��ǰ����������
	}

		//��ȡ������ʾ�룬Ϊ�ṹ������㹻�Ŀռ�
	fscanf(LOG, "%d,", &zrs);
	USER* pren = (USER*)malloc(zrs * sizeof(USER));//���ݿ�pren
	//����¼��
	for (i = 0; i < zrs; i++) {
		//printf("��%d�������ѳɹ�����\n", i + 1);// ����ͷ��β����ע���Ϊ���Ժ���
		fscanf(LOG, "%[^,],%[^,],%[^,],%d,%d,", &((pren + i)->name), &((pren + i)->username), \
			& ((pren + i)->password), &((pren + i)->feature), &((pren + i)->feature2));
		/*printf("%s  %s %s %d %d\n", ((pren + i)->name), ((pren + i)->username), \
			((pren + i)->password), ((pren + i)->feature), ((pren + i)->feature2));*/
	}
	//�û���¼

	char judge = '0',tp_pp[17];
	char tn[13] = "0", tp[17] = "0";
	char* tnp, * tpp;
	tnp = tn, tpp = tp;

	int j, j1 = 0, j2,j4=0,j5;//j�����Ƚ��ж�,j4=1ʱ����ѭ��
	char j3;
	
	while (1) {
		system("cls");
		//�����û���
		printf("�û�����");
		scanf("%s", &tn);
		getchar();
		//printf("��������%s\n", tn);
		for (i = 0; i < zrs; i++) {
			j = strcmp(tnp, (pren+i)->name);
			//printf("j=%d\n", j);
			if (j == 0) break;
		}
		//û�и��û������
		if (j != 0) {
			system("cls");
			printf("��ϵͳû������û�.\nY����������   N���˳�ϵͳ   C�������º���\n");
			scanf("%c", &j3);
			getchar();
			if (j3 == 'C');
			if (j3 == 'N') j4=1;
		}
		else {
			for (j2 = 0; j2 < 3; j2++) {
				system("cls");//
				printf("�û� %s ��ã�������������롣\n���룺", tn);
				//scanf("%s", &tp);
				//getchar();
				/*for (j5 = 0; (tp_pp[j5]= getch()) != '\r'&&j5 < 16; j5++) {
					*(tpp + j5) = tp_pp[j5];
					printf("*");
				}
				*(tpp + j5+1) = '\0';*/
				fflush(stdin);
				for (j5 = 0; (tp_pp[j5] = getch()) != '\r' && j5 < 16; j5++) {
					if (tp_pp[j5] == '\b') {
						if (j5 != 0) {
							printf("\b \b");
							j5 -= 2;
						}
						else { j5--; }
					}
					else {
						printf("*");
						*(tpp + j5) = tp_pp[j5];
					}
				}
				*(tpp + j5 ) = '\0';
				//printf("\n %s", tp);
				j = strcmp(tpp, (pren + i)->password);

				if (j == 0)	break;
				else {
					system("cls");
					printf("����������������롣");
					getch();
				}
			}
			if (j == 0) {
				//�û�����������д��
				system("cls");
				//pusername = pren->username;
				//strcpy(pusername, pren->username);
				*pfeature = i;
				
				//*pfeature2 = ;
				//printf("pusername=%s pfeature=%d pfeature2=%d\n", pusername, pfeature, pfeature2);
				ret = 1;//һ������
				j4 = 1;
				*pfeature = i;
			}
			else {
				system("cls");//
				printf("���������������������������\n");
				j4=1;
			}

		}
		if (j4 == 1) break;
		getchar();
	}
	free(pren);
	return ret;
}