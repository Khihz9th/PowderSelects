#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#include "sudo.h"

void HIDECUR(int n);
static  void  SetPos(int  x, int  y);
static void arr(int x, int y);
static void ow(int x, int y);
static int topitem(int lx, int y, int width, int type);
static int merchandise(int x, int y, int order);
static int lllitem(int ly, int x, int y, int height, int type);
//static int ttfunction(USE* a, PROD* b, int c);
static void topinf(void);


typedef struct {
	int ProNum;
	char ProNam[30];
	double cPr;
	double sPr;
	double zpr;
	int sto;
	int toL;
	int inDa;
	int mCnum;
	int type;//���������
}PROD;

typedef struct {
	char name[13];			//�û���¼����12��Ӣ��������ַ���
	char username[24];		//�û�����������������Ʒ����ҳ����ʾ��
	char password[17];		//�û���¼���루16�����ֻ�Ӣ���ַ���
	int feature;			//0Ϊ����Ա,����Ϊע���û�(������չʱʹ�ã�
	int feature2;			//�ڶ������루0Ϊ�̼ң�1Ϊ��ͨ�û���
}USE;

int sudo(int feature)
{
	time_t timep;
	struct tm* ptime;
	time(&timep);
	ptime = gmtime(&timep);

	int times, day;
	int nowuser = 0;
	int p_zs, u_zs, j3;
	int bpn, bun, buj;
	int x = 4, y = 1, width = 16, type = 3, tr = 0, use_code = 0, badin = 0, h5 = 0;
	int* usde = &use_code;

	int lret, c_a;
	char check[24];
	double c1, c2;
	//����
	int display = 0;
	//order
	char proname[25];
	int shuliang;
	double cgj, fsj;
	int ctype;
	//CHUANGJIAN
	int czsz[500];
	char filename[50] = "D:\\cx4\\proinf\\";
	char backic[5] = ".txt";
	char midcha[10];


	FILE* U = fopen("D:\\cx4\\loginf.txt", "r");
	FILE* P = fopen("D:\\cx4\\cominf.txt", "r");
	fscanf(U, "%d,", &u_zs);
	fscanf(P, "%d,", &p_zs);
	USE* user_ = (USE*)malloc(u_zs * sizeof(USE));
	PROD* prod_ = (PROD*)malloc(p_zs * sizeof(PROD));

	for (int us = 0; us < p_zs; us++) {
		fscanf(P, "%[^,],%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", &((prod_ + us)->ProNam), &((prod_ + us)->ProNum), \
			& ((prod_ + us)->sto), &((prod_ + us)->toL), &((prod_ + us)->inDa), &((prod_ + us)->cPr), \
			& ((prod_ + us)->sPr), &((prod_ + us)->mCnum), &((prod_ + us)->type), &((prod_ + us)->zpr));
	}
	for (int us = 0; us < u_zs; us++) {
		fscanf(U, "%[^,],%[^,],%[^,],%d,%d,", &((user_ + us)->name), &((user_ + us)->username), \
			& ((user_ + us)->password), &((user_ + us)->feature), &((user_ + us)->feature2));
	}
	fclose(U);
	fclose(P);

	FILE* bP = fopen("D:\\cx4\\badcom.txt", "r");
	FILE* bU = fopen("D:\\cx4\\badlog.txt", "r");

	fscanf(bP, "%d,", &bpn);
	fscanf(bU, "%d,", &bun);

	int* bpnp = (int*)malloc(bpn * sizeof(int));
	int* bpup = (int*)malloc(bun * sizeof(int));

	for (int j1 = 0; j1 < bpn; j1++) {
		fscanf(bP, "%d,", (bpnp + j1));
		//printf("%d ", *(bpnp + j1));
	}
	for (int j1 = 0; j1 < bun; j1++) {
		fscanf(bU, "%d,", (bpup + j1));
		//printf("%d ", *(bpup + j1));
	}
	fclose(bP);
	fclose(bU);


	int* a = (int*)malloc(p_zs * sizeof(int));//


inital0:


	display = p_zs;
	for (int i = 0; i < p_zs; i++) {
		*(a + i) = i;
	}
sy:

	system("cls");
	topinf();
	tr = topitem(x, y, width, type);
	switch (tr) {
	case 1:
		printf("\n\n      1.ɾ����Ʒ ");
		printf("\n      2.�޸���Ʒ ");
		printf("\n      3.�����ϼ� ");
		tr=lllitem(3, 4, 3, 1, 3);
		switch (tr) {
		case 1:
			system("cls");
			printf("������Ʒ��ż���ɾ�������� - 1�����ϼ�\n");
			fflush(stdin);
			scanf("%d", &tr);
			printf("�ظ�Yȷ��ɾ������Ϊ%s����Ʒ�����򷵻��ϼ���\n",(prod_+tr)->ProNam);
			if (getch() != 'Y') goto sy;
			else {
				FILE* RE = fopen("D:\\cx4\\cominf.txt", "w+");
				fprintf(RE, "%06d,", p_zs - 1);
				for (int us = 0; us < p_zs; us++) {
					if (((prod_ + us)->ProNum) == tr) continue;
					fprintf(RE, "%s,%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", ((prod_ + us)->ProNam), ((prod_ + us)->ProNum), \
						((prod_ + us)->sto), ((prod_ + us)->toL), ((prod_ + us)->inDa), ((prod_ + us)->cPr), \
						((prod_ + us)->sPr), ((prod_ + us)->mCnum), ((prod_ + us)->type), ((prod_ + us)->zpr));
				}
				fclose(RE);
				printf("ɾ���ɹ����������������ҳˢ�����ݿ⣻");
				return 1;
			}
			break;
		case 2:
			system("cls");
			printf("������Ʒ��ż����޸ģ����� - 1�����ϼ�\n");
			fflush(stdin);
			scanf("%d", &tr);
			printf("�ظ�Yȷ���޸�����Ϊ%s����Ʒ�����򷵻��ϼ���\n", (prod_ + tr)->ProNam);
			if (getch() != 'Y') goto sy;
			else {
				system("cls");
				topinf();
				HIDECUR(1);
					printf("\n\n\tѡ���޸�����\n\n");
					printf("\t\t1.��Ʒ����\n");
					printf("\t\t2.��Ʒ���\n");
					printf("\t\t3.�ɹ��۸�\n");
					printf("\t\t4.���ۼ۸�\n");
					printf("\t\t5.�ۿۼ۸�\n");
					printf("\t\t6.��Ʒ����\n");
					printf("\t\t7.�ϴ����˳�\n");
					c_a = lllitem(6, 14, 11, 1, 7);
					system("cls");
					topinf();
					HIDECUR(1);
					printf("\n\n        ���      ��Ʒ����            �ɹ���      ���ۼ�      �ۿۼ�      ��Ʒ���      ���     �ϼ�����      �ϼ�ʱ��\n\n");
					printf("         %02d       %-18s %6.2lf      %6.2lf      %6.2lf         %-3d          %-3d        %-3d        %04d/%02d/%02d       \n"\
						, h5, (prod_ + czsz[lret])->ProNam, (prod_ + czsz[lret])->cPr, (prod_ + czsz[lret])->sPr, 0.75 * ((prod_ + czsz[lret])->sPr)\
						, (prod_ + czsz[lret])->ProNum, (prod_ + czsz[lret])->sto, (prod_ + czsz[lret])->toL, (prod_ + czsz[lret])->inDa / 10000, \
						((prod_ + czsz[lret])->inDa % 10000) / 100, (prod_ + czsz[lret])->inDa % 100);
					switch (c_a) {
					case 1:
						printf("\n\n\t\t�����������ƣ�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t�����ƣ�");
						fflush(stdin);
						scanf("%s", &((prod_ + czsz[lret])->ProNam));
						printf("\n\n\t\t�޸���ɣ������������");
						getchar();
						break;
					case 2:
						printf("\n\n\t\t���������ӻ���ٵĿ����ֵ��һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t��ֵ��");
						fflush(stdin);
						scanf("%d", &shuliang);
						//printf("lret=%d,",lret)
						c_a = ((prod_ + czsz[lret])->toL);
						((prod_ + czsz[lret])->toL) = shuliang + c_a;
						c_a = ((prod_ + czsz[lret])->sto);
						((prod_ + czsz[lret])->sto) = c_a + shuliang;
						lret = 0;
						printf("\n\n\t\t�޸���ɣ������������");
						getchar();
						break;
					case 3:
						printf("\n\n\t\t������Ĳɹ��۸�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t��ֵ��");
						fflush(stdin);
						scanf("%lf", &((prod_ + czsz[lret])->cPr));
						printf("\n\n\t\t�޸���ɣ������������");
						getchar();
						break;
					case 4:
						printf("\n\n\t\t����������ۼ۸�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t��ֵ��");
						fflush(stdin);
						scanf("%lf", &((prod_ + czsz[lret])->sPr));
						printf("\n\n\t\t�޸���ɣ������������");
						getchar();
						break;
					case 5:
						printf("\n\n\t\t��������ۿۼ۸�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t��ֵ��");
						fflush(stdin);
						scanf("%lf", &((prod_ + czsz[lret])->zpr));
						printf("\n\n\t\t�޸���ɣ������������");
						getchar();
						break;
					case 6:
						printf("\n\n\t\t��������Ʒ������ţ�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t��ֵ��");
						fflush(stdin);
						scanf("%d", &((prod_ + czsz[lret])->type));
						printf("\n\n\t\t�޸���ɣ������������");
						getchar();
						break;
					case 7:
						FILE * RE = fopen("D:\\cx4\\cominf.txt", "w+");
						fprintf(RE, "%06d,", p_zs - 1);
						for (int us = 0; us < p_zs; us++) {
							if (((prod_ + us)->ProNum) == czsz[lret]) continue;
							fprintf(RE, "%s,%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", ((prod_ + us)->ProNam), ((prod_ + us)->ProNum), \
								((prod_ + us)->sto), ((prod_ + us)->toL), ((prod_ + us)->inDa), ((prod_ + us)->cPr), \
								((prod_ + us)->sPr), ((prod_ + us)->mCnum), ((prod_ + us)->type), ((prod_ + us)->zpr));

						}
						fclose(RE);

					}
					printf("�޸ĳɹ����������������ҳˢ�����ݿ⣻");
					return 1;				
			}
		case 3:
			goto sy;
		}
		break;
	case 2:
		printf("\n\n      1.ɾ���û� ");
		printf("\n      2.�޸��û� ");
		printf("\n      3.�����ϼ� ");
		tr = lllitem(3, 4, 3, 1, 3);
		switch (tr) {
		case 1:
			system("cls");
			printf("�����û�ʶ�������ɾ�������� - 1�����ϼ�\n");
			fflush(stdin);
			scanf("%d", &tr);
			if (tr == -1) goto sy;
			printf("�ظ�Yȷ��ɾ������Ϊ%s���û������򷵻��ϼ���\n", (user_ + tr)->username);
			if (getch() != 'Y') goto sy;
			else {
				FILE* RE = fopen("D:\\cx4\\loginf.txt", "w+");
				fprintf(RE, "%06d,", p_zs - 1);
				for (int i = 0; i < p_zs; i++) {
					if (((user_ + i)->feature) == tr) continue;
					fprintf(RE, "%[^,],%[^,],%[^,],%d,%d,", ((user_ + i)->name), ((user_ + i)->username), \
						((user_ + i)->password), ((user_ + i)->feature), ((user_ + i)->feature2));
				}
				fclose(RE);
				printf("ɾ���ɹ����������������ҳˢ�����ݿ⣻");
				return 1;
			}
			break;
		case 2:
			system("cls");
			printf("�����û���ż����޸ģ����� - 1�����ϼ�\n");
			fflush(stdin);
			scanf("%d", &tr);
			printf("�ظ�Yȷ���޸�����Ϊ%s���û������򷵻��ϼ���\n", (user_ + tr)->username);
			if (getch() != 'Y') goto sy;
			else {
				aa:
				system("cls");
				topinf();
				HIDECUR(1);
				printf("\n\n\tѡ���޸�����\n\n");
				printf("\t\t1.�û�����\n");
				printf("\t\t2.�̻�����\n");
				printf("\t\t3.�ڶ�������\n");
				printf("\t\t4.�ϴ����˳�\n");
				c_a = lllitem(6, 14, 11, 1, 7);
				system("cls");
				topinf();
				HIDECUR(1);
				switch (c_a) {
				case 1:
					printf("\n\n\t\t�����������ƣ�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t�����ƣ�");
					fflush(stdin);
					scanf("%s", &((user_ + c_a)->name));
					printf("\n\n\t\t�޸���ɣ������������");
					getchar();
					goto aa;
					break;
				case 2:
					printf("\n\n\t\t�����������ƣ�һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t�����ƣ�");
					fflush(stdin);
					scanf("%s", &((user_ + c_a)->username));
					printf("\n\n\t\t�޸���ɣ������������");
					getchar();
					goto aa;
					break;
				case 3:
					printf("\n\n\t\t�����룬һ��ȷ�ϲ��ɸ��ģ�\n\n\t\t��ֵ��");
					fflush(stdin);
					scanf("%d", &((user_ + c_a)->feature2));
					printf("\n\n\t\t�޸���ɣ������������");
					getchar();
					goto aa;
					break;
				case 4:
				hhh:
					FILE * RE = fopen("D:\\cx4\\loginf.txt", "w+");
					fprintf(RE, "%06d,", p_zs - 1);
					for(int i = 0; i < p_zs; i++) {
						fprintf(RE, "%[^,],%[^,],%[^,],%d,%d,", ((user_ + i)->name), ((user_ + i)->username), \
							((user_ + i)->password), ((user_ + i)->feature), ((user_ + i)->feature2));
					}
					fclose(RE);

				}
				printf("�޸ĳɹ����������������ҳˢ�����ݿ⣻");
				getch();
				return 1;
			}
		case 3:
			goto sy;
		}
	case 3:
		return 0;
		break;
	case 4:
		return 1;
		break;
	}



	return 0;

}

	// ����ĺ����߶�����
		//���ع��
		void HIDECUR(int n) /*���ع��*/
	{
		CONSOLE_CURSOR_INFO cursor_info = { 1,n };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	}
	//���ù������
	static  void  SetPos(int  x, int  y)
	{
		COORD  point = { x ,  y }; //���Ҫ���õ�λ��x,y
		HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //ʹ��GetStdHandle(STD_OUTPUT_HANDLE)����ȡ��׼����ľ��
		SetConsoleCursorPosition(HOutput, point); //���ù��λ��
	}
	//��ͷ����
	static void arr(int x, int y) {
		SetPos(x, y);
		printf("->");
	}
	//��ͷ��ʧ
	static void ow(int x, int y) {
		SetPos(x, y);
		printf("  ");
	}
	//����ļ�ͷ
	static int topitem(int lx, int y, int width, int type) {
		int kv, lv = 1, tv, x = lx;
		HIDECUR(0);
		arr(x, y);
		while (1) {
			if (_kbhit()) {
				kv = _getch();
				if (kv == 224) {
					tv = _getch();
					switch (tv) {
					case 75:
						ow(x, y);
						if (x < width) {
							x = x + type * width;
							arr(x, y);
						}
						else {
							x -= width;
							arr(x, y);
						}
						break;
					case 77:
						ow(x, y);
						if (x > type * width) {
							x = x - type * width;
							arr(x, y);
						}
						else {
							x = x + width;
							arr(x, y);
						}
						break;
					default:
						//printf("��ʹ�÷����<-��->�ƶ���ꡣ\n");
						break;
					}
				}
				else if (kv <= 52 && kv >= 49) {
					ow(x, y);
					x = lx + (kv - 49) * width;
					arr(x, y);
				}
				else if (kv == 13) break;
			}
			Sleep(100);

		}
		HIDECUR(0);
		return x = (x + (width - lx)) / width;
	}
	//��Ʒ��Ϣչʾ//qy
	//static int ttfunction(USE* a, PROD* b, int c)
	//{
	//	system("cls");
	//	topinf();
	//	printf("\n\n           1.����Ӧ�̲���\n");
	//		printf("           2.�����ڻ������������\n");
	//		printf("           3.���۸��������\n");
	//		printf("           4.���������\n");
	//}
	//�����˵���
	static void topinf(void) {
		printf("\n      1.������Ʒ      2.�����û�      3.�˳�����      4.�˳�����      \n");
	}
	//������
	static int lllitem(int ly, int x, int y, int height, int type) {
		int kv, lv = 1, tv;
		y = ly;
		HIDECUR(0);
		arr(x, y);
		while (1) {
			if (_kbhit()) {
				kv = _getch();
				if (kv == 224) {
					tv = _getch();
					switch (tv) {
					case 72:
						ow(x, y);
						if (y == ly) {
							y = ly + (type - 1) * height;
							arr(x, y);
						}
						else {
							y -= height;
							arr(x, y);
						}
						break;
					case 80:
						ow(x, y);
						if (y == (ly + (type - 1) * height)) {
							y = ly;
							arr(x, y);
						}
						else {
							y = y + height;
							arr(x, y);
						}
						break;
					default:
						//printf("��ʹ�÷����<-��->�ƶ���ꡣ\n");
						break;
					}
				}
				else if (kv <= 48 + type && kv >= 49) {
					ow(x, y);
					y = ly + (kv - 49) * height;
					arr(x, y);
				}
				else if (kv == 13) break;
			}
			Sleep(100);

		}
		HIDECUR(0);
		return y = (y - ly) / height + 1;
	}