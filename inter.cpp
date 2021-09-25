#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#include "inter.h"

void HideCursor(int n);
static  void  SetPos(int  x, int  y);
static void arr(int x, int y);
static void ow(int x, int y);
static int topitem(int lx, int y, int width, int type);
static int merchandise(int x, int y, int order);
static int lllitem(int ly, int x, int y, int height, int type);
//static int ttfunction(USE* a, PROD* b, int c);
static void topinf(void);


typedef struct{
	int ProNum;
	char ProNam[30];
	double cPr;
	double sPr;
	double zpr;
	int sto;
	int toL;
	int inDa;
	int mCnum;
	int type;//这个忘记了
}PROD;

typedef struct {
	char name[13];			//用户登录名（12个英语或数字字符）
	char username[24];		//用户中文特征名（在商品详情页面显示）
	char password[17];		//用户登录密码（16个数字或英文字符）
	int feature;			//0为管理员,其他为注册用户(数据拓展时使用）
	int feature2;			//第二特征码（0为商家，1为普通用户）
}USE;

int inter(int feature)
{
	time_t timep;
	struct tm* ptime;
	time(&timep);
	ptime = gmtime(&timep);

	int times,day;
	int nowuser=feature;
	int p_zs, u_zs,j3;
	int bpn,bun,buj;
	int x = 4, y = 1, width = 12, type = 3, tr = 0, use_code = 0, badin = 0, h5 = 0;
	int* usde = &use_code;

	int lret, c_a;
	char check[24];
	double c1, c2;
	//查找
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
		fscanf(P, "%[^,],%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", &((prod_ + us)->ProNam), &((prod_ + us)->ProNum),\
			& ((prod_ + us)->sto), &((prod_ + us)->toL), &((prod_ + us)->inDa), &((prod_ + us)->cPr),\
			&((prod_ + us)->sPr), &((prod_ + us)->mCnum), &((prod_ + us)->type), &((prod_ + us)->zpr));
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
		fscanf(bP,"%d,", (bpnp + j1));
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
inital1:
	system("cls");
	HideCursor(0);
	SetPos(0, 0);
	h5 = 0;
	printf("\n      1.搜索      2.排序      3.刷新      4.管理      \n");
	//tr = merchandise(x, y, tr);
	printf("\n\n        序号      商品名称            采购价      销售价      折扣价      商品编号      库存     上架总数      上架时间            供应商\n\n");
	if (display == 0) printf("\n\n\n            这里什么都没有。");
	else
	for (int ij = 0; ij < display; ij++) {
		if (*(a+ij) == *(bpnp + badin)) {
			badin++;
			continue;
		}
		*usde = (prod_ + *(a + ij))->mCnum;
	printf("         %02d       %-18s %6.2lf      %6.2lf      %6.2lf         %-3d          %-3d        %-3d        %04d/%02d/%02d       %s\n"\
			,h5+1,(prod_ +*(a + ij))->ProNam, (prod_ + *(a + ij))->cPr, (prod_ + *(a + ij))->sPr,0.75 * ((prod_ + *(a + ij))->sPr)\
			, (prod_ + *(a + ij))->ProNum, (prod_ + *(a + ij))->sto, (prod_ + *(a + ij))->toL, (prod_ + *(a + ij))->inDa/10000,\
		((prod_ + *(a + ij))->inDa%10000)/100, (prod_ + *(a + ij))->inDa%100,(user_+use_code)->username);

	h5++;

	if ((h5 % 5) == 0) printf("\n");
	}
	getch();

	tr = topitem(x, y, width, type);
	switch (tr)
	{
	case 1://查找
		system("cls");
		topinf();
		printf("\n      1.按供应商查找\n");
		printf("      2.按日期或日期区间查找\n");
		printf("      3.按价格区间查找\n");
		printf("      4.按种类查找\n");//这个还没做
		printf("      5.返回上一级\n");//这个还没做
		lret = lllitem(3, 4, 3, 1, 5);
		switch (lret) {
		case 1:
		check1start:
			SetPos(0, 0);
			system("cls");//忽视了供应商已清除的情况
			topinf();
			printf("\n      1.按供应商查找\n");
			printf("\n                   1.按供应商专属编号查找");
			printf("\n                   2.按供应商名称查找");
			printf("\n                   3.返回上一级");
			printf("\n                   4.返回顶栏");
			lret = lllitem(5, 17, 6, 1, 4);
			switch (lret) {
			case 1:
				system("cls");
				topinf();
				printf("\n                   请输入商户专属编号:");
				fflush(stdin);
				scanf("%d", &c_a);
			check1start1:
				display = 0;

				for (int i = 0; i < p_zs; i++)
				{
					if (c_a == ((prod_ + i)->mCnum)) {
						*(a + display) = (prod_ + i)->ProNum;
						display++;
					}
				}
				goto inital1;
				break;
			case 2:
				system("cls");
				topinf();
				printf("\n                   请输入商户名称:");
				scanf("%s", &check);
				for (c_a = 0; c_a < u_zs; c_a++) {
					if (!strcmp(check, (user_ + c_a)->username)) goto check1start1;
				}
				display = 0;
				goto inital1;
				break;
			case 3: goto check1start; break;
			case 4: goto inital0; break;

			}
		case 2:
			system("cls");
			topinf();
			printf("\n    \n");
			printf("      2.按日期或日期区间查找\n\n");
			printf("                           1.按日期查找\n");
			printf("                           2.按日期区间查找\n");
			printf("                           3.返回上一级");
			printf("\n                           4.返回顶栏");
			lret = lllitem(6, 25, 6, 1, 4);
			switch (lret) {
			case 1:
				system("cls");
				topinf();
				HideCursor(1);
				printf("\n    \n");
				printf("      2.按日期查找\n\n");
				printf("        查找日期:");
				printf("\n\n\n      示例： 查询2021年2月19日的商品请输入 20210219");
				SetPos(17, 6);
				fflush(stdin);
				scanf("%d", &c_a);
				display = 0;

				for (int i = 0; i < p_zs; i++)
				{
					if (c_a == ((prod_ + i)->inDa)) {
						*(a + display) = (prod_ + i)->ProNum;
						display++;
					}
				}
				goto inital1;
				break;
			case 2:
				system("cls");
				topinf();
				HideCursor(1);
				printf("\n    \n");
				printf("      2.按日期查找\n\n");
				printf("        查找日期:");
				printf("\n\n\n      示例： 查询2021年2月19日-2021年5月14日的商品请输入 20210219-20210514");
				SetPos(17, 6);
				fflush(stdin);
				scanf("%d-%d", &c_a, &lret);
				display = 0;

				for (int i = 0; i < p_zs; i++)
				{
					if (c_a <= ((prod_ + i)->inDa) && lret >= ((prod_ + i)->inDa)) {
						*(a + display) = (prod_ + i)->ProNum;
						display++;
					}
				}
				goto inital1;
				break;
			case 3: goto check1start; break;
			case 4: goto inital0; break;

			}
		case 3:
			system("cls");
			topinf();
			printf("\n     \n");
			printf("      \n");
			printf("      3.按价格区间查找\n");
			printf("                     1.按采购价查询\n");
			printf("                     2.按销售价查询\n");
			printf("                     3.按折扣价查询\n");
			printf("                     4.返回上级\n");
			lret = lllitem(6, 19, 6, 1, 4);
			if (lret == 4) goto check1start;
			system("cls");
			topinf();
			HideCursor(1);
			printf("\n    \n");
			printf("      \n\n");
			printf("      3.按价格区间查找\n \n");
			printf("        价格查找:");
			printf("\n\n\n      示例： 查询15.43-16.17元之间的商品请输入 15.43-16.17\n");
			SetPos(17, 8);
			fflush(stdin);
			scanf("%lf-%lf", &c1, &c2);
			display = 0;

			for (int i = 0; i < p_zs; i++)//这段代码真恶心
			{
				if (lret == 1)
					if (c1 <= ((prod_ + i)->cPr) && c2 >= ((prod_ + i)->cPr)) {
						*(a + display) = (prod_ + i)->ProNum;
						display++;
					}
					else if (lret == 2)
						if (c1 <= ((prod_ + i)->sPr) && c2 >= ((prod_ + i)->sPr)) {
							*(a + display) = (prod_ + i)->ProNum;
							display++;
						}
						else if (lret == 3)
							if (c1 <= ((prod_ + i)->zpr) && c2 >= ((prod_ + i)->zpr)) {//zpr我是没有初始值的
								*(a + display) = (prod_ + i)->ProNum;
								display++;
							}
			}
			goto inital1;
			break;
		case 5: goto inital1;

		}
		break;
	case 2://排序
		system("cls");
		topinf();
		HideCursor(1);
		printf("\n      1.按价格排序\n");
		printf("      2.按日期排序\n");
		printf("      3.按库存排序\n");
		printf("      4.按种类排序\n");
		printf("      5.按商户名称排序\n");
		printf("      6.返回上一级");
		lret = lllitem(3, 4, 3, 1, 6);
		switch (lret) {
		case 1:
			SetPos(0, 0);
			system("cls");//忽视了供应商已清除的情况
			topinf();
			printf("\n      1.按价格排序\n");
			printf("\n                 1.按采购价格排序");
			printf("\n                 2.按销售价格排序");
			printf("\n                 3.按促销价格排序");
			printf("\n                 4.返回上级");
			lret = lllitem(5, 15, 6, 1, 4);
			switch (lret) {
			case 1:
				for (int i = 0; i < display - 1; i++)
					for (int j = 0; j < display - 1 - i; j++) {
						if (((prod_ +*(a+j))->cPr) > ((prod_ + *(a + j + 1))->cPr)) {
							c_a = *(a + j);
							*(a + j) = *(a + j + 1);
							*(a + j + 1) = c_a;
						}
					}
				break;
			case 2:
				for (int i = 0; i < display - 1; i++)
					for (int j = 0; j < display - 1 - i; j++) {
						if (((prod_ + *(a + j))->sPr) > ((prod_ + *(a + j + 1))->sPr)) {
							c_a = *(a + j);
							*(a + j) = *(a + j + 1);
							*(a + j + 1) = c_a;
						}
					}
				break;
			case 3:
				for (int i = 0; i < display - 1; i++)
					for (int j = 0; j < display - 1 - i; j++) {
						if (((prod_ + *(a + j))->zpr) > ((prod_ + *(a + j + 1))->zpr)) {
							c_a = *(a + j);
							*(a + j) = *(a + j + 1);
							*(a + j + 1) = c_a;
						}
					}
				break;
			case 4:
				goto inital1;
			}
			break;
		case 2:
			for (int i = 0; i < display - 1; i++)
				for (int j = 0; j < display - 1 - i; j++) {
					if (((prod_ + *(a + j))->inDa) > ((prod_ + *(a + j + 1))->inDa)) {
						c_a = *(a + j);
						*(a + j) = *(a + j + 1);
						*(a + j + 1) = c_a;
					}
				}
			break;

		case 3:
			system("cls");
			topinf();
			HideCursor(1);
			printf("\n      \n");
			printf("     \n");
			printf("      3.按库存排序\n");
			printf("                 1.剩余库存\n");
			printf("                 2.总库存");
			printf("\n                 3.返回上级");
			lret = lllitem(6, 15, 6, 1, 3);
			switch (lret) {
			case 1:
				for (int i = 0; i < display - 1; i++)
					for (int j = 0; j < display - 1 - i; j++) {
						if (((prod_ + *(a + j))->sto) > ((prod_ + *(a + j + 1))->sto)) {
							c_a = *(a + j);
							*(a + j) = *(a + j + 1);
							*(a + j + 1) = c_a;
						}

					}
				break;
			case 2:
				for (int i = 0; i < display - 1; i++)
					for (int j = 0; j < display - 1 - i; j++) {
						if (((prod_ + *(a + j))->toL) > ((prod_ + *(a + j + 1))->toL)) {
							c_a = *(a + j);
							*(a + j) = *(a + j + 1);
							*(a + j + 1) = c_a;
						}

					}
				break;
			case 3:
				goto inital1; break;
			}
		case 4:
			for (int i = 0; i < display - 1; i++)
				for (int j = 0; j < display - 1 - i; j++) {
					if (((prod_ + *(a + j))->type) > ((prod_ + *(a + j + 1))->type)) {
						c_a = *(a + j);
						*(a + j) = *(a + j + 1);
						*(a + j + 1) = c_a;
					}
				}
			break;
		case 5:
			for (int i = 0; i < display - 1; i++)
				for (int j = 0; j < display - 1 - i; j++) {
					if (((prod_ + *(a + j))->mCnum) > ((prod_ +  * (a + j + 1))->mCnum)) {
						c_a = *(a + j);
						*(a + j) = *(a + j + 1);
						*(a + j + 1) = c_a;
					}
				}
			break;
		case 6: goto inital1;
		}
	order:
		system("cls");
		topinf();
		HideCursor(1);
		printf("\n      \n");
		//for (int i = 0; i < p_zs; i++)  printf("%d ", *(a + i));
		printf("请选择正序或逆序。y:正序，n：逆序");
		if (getch() == 'n') 
			for (int i = 0; i < display / 2; i++) {
				c_a = *(a + i);
				*(a + i) = *(a + display - 1 - i);
				*(a + display - 1 - i) = c_a;
			}
		goto inital1;
		break;
	case 3: goto inital0; break;
	case 4:
		
		chose4managemenu:	
		system("cls");
		/*if ((user_ + feature) != 0) {
			printf("您没有权限操作，按任意键返回。");
			getch();
			goto inital1;
		}*/
		topinf();
		HideCursor(1);
		printf("\n                                          1.上架商品");
		printf("\n                                          2.管理商品");
		printf("\n                                          3.返回上级");
		lret = lllitem(3, 39, 3, 1, 3);
		switch (lret) {			
		case 1:
			reinput_product:
			system("cls");
			topinf();
			HideCursor(1);
		printf("\n                                          1.上架商品\n\n");
			printf("\t\t商品名称：\n");
			printf("\t\t商品库存：\n");
			printf("\t\t采购价格：\n");
			printf("\t\t销售价格：\n");
			printf("\t\t商品种类：\n"); 
			SetPos(26,5);
			scanf("%s", &proname);
			fflush(stdin);
			SetPos(26, 6);
			scanf("%d", &shuliang);
			fflush(stdin);
			SetPos(26, 7);
			scanf("%lf", &cgj);
			fflush(stdin);
			SetPos(26, 8);
			scanf("%lf", &fsj);
			fflush(stdin);
			SetPos(26, 9);
			scanf("%d", &ctype);
			fflush(stdin);
			printf("\n\n\t\t确认上传\n\t\t重新输入\n\t\t取消上传");
			lret=lllitem(12, 14, 12, 1, 3);
			if (lret == 2) goto reinput_product;
			else if (lret == 3) goto chose4managemenu;
			else {
				day = ptime->tm_mday;
				if (8 + ptime->tm_hour >= 24)day++;
				times = 10000 * (1900 + ptime->tm_year) + (ptime->tm_mon+1) * 100 + day;
				printf("%d", times);
				
				FILE* wrP = fopen("D:\\cx4\\cominf.txt", "a+");
				fprintf(wrP, "%s,%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", proname, p_zs + 1, shuliang, shuliang, \
					times, cgj, fsj, nowuser, ctype, 0);
				fclose(wrP);
				FILE* wP = fopen("D:\\cx4\\cominf.txt", "r+");
				fseek(wP, 0, SEEK_SET);
				fprintf(wP, "%06d", p_zs + 1);
				fclose(wP);
				system("cls");
				topinf();
				HideCursor(1);
				printf("\n                                          1.上架商品\n\n");
				printf("\n                              创建成功，按任意键刷新界面。\n\n");
				getch();
				fclose(wrP);
				goto inital0;//返回主函数哦，重新打开本函数
			}
			break;
		case 2:
			system("cls");
			topinf();
			HideCursor(1);
			printf("\n                                          2.管理商品\n\n");

			printf("\n\n        序号      商品名称            采购价      销售价      折扣价      商品编号      库存     上架总数      上架时间\n\n");
			display = p_zs;
			h5 = 0;
			for (int i = 0; i < p_zs; i++) {
				*(a + i) = i;
			}
			if (display == 0) printf("\n\n\n            这里什么都没有。");
			else
				for (int ij = 0; ij < display; ij++) {
					if (nowuser == (prod_ + *(a + ij))->mCnum) {
						
							*usde = (prod_ + *(a + ij))->mCnum;
							printf("         %02d       %-18s %6.2lf      %6.2lf      %6.2lf         %-3d          %-3d        %-3d        %04d/%02d/%02d       %s\n"\
								, h5, (prod_ + *(a + ij))->ProNam, (prod_ + *(a + ij))->cPr, (prod_ + *(a + ij))->sPr, 0.75 * ((prod_ + *(a + ij))->sPr)\
								, (prod_ + *(a + ij))->ProNum, (prod_ + *(a + ij))->sto, (prod_ + *(a + ij))->toL, (prod_ + *(a + ij))->inDa / 10000, \
								((prod_ + *(a + ij))->inDa % 10000) / 100, (prod_ + *(a + ij))->inDa % 100, (user_ + use_code)->username);
							czsz[h5] = (prod_ + *(a + ij))->ProNum;
							h5++;
						
						//if ((h5 % 5) == 0) printf("\n");
					}
				}
			printf("         返回上一级\n");

			lret = lllitem(9,6,9,1,h5+1)-1;//阔选的bug


			if (lret> h5) goto chose4managemenu;
			else {
				dangespzs:
				system("cls");
				topinf();
				HideCursor(1);
				printf("\n\n        序号      商品名称            采购价      销售价      折扣价      商品编号      库存     上架总数      上架时间\n\n");
				printf("         %02d       %-18s %6.2lf      %6.2lf      %6.2lf         %-3d          %-3d        %-3d        %04d/%02d/%02d       \n"\
					, h5, (prod_ + czsz[lret])->ProNam, (prod_ + czsz[lret ])->cPr, (prod_ + czsz[lret ])->sPr, 0.75 * ((prod_ + czsz[lret])->sPr)\
					, (prod_ + czsz[lret ])->ProNum, (prod_ + czsz[lret ])->sto, (prod_ + czsz[lret ])->toL, (prod_ + czsz[lret ])->inDa / 10000, \
					((prod_ + czsz[lret ])->inDa % 10000) / 100, (prod_ + czsz[lret])->inDa % 100);
				printf("\n\n\t\t1.查看最接近销量\n");
				printf("\t\t2.修改信息\n");
				printf("\t\t3.删除商品\n");
				printf("\t\t4.返回上一级\n");
				
				c_a = lllitem(9, 13, 9, 1, 4);

				system("cls");
				topinf();
				HideCursor(1);
				printf("\n\n        序号      商品名称            采购价      销售价      折扣价      商品编号      库存     上架总数      上架时间\n\n");
				printf("         %02d       %-18s %6.2lf      %6.2lf      %6.2lf         %-3d          %-3d        %-3d        %04d/%02d/%02d       \n"\
					, h5, (prod_ + czsz[lret])->ProNam, (prod_ + czsz[lret])->cPr, (prod_ + czsz[lret])->sPr, 0.75 * ((prod_ + czsz[lret])->sPr)\
					, (prod_ + czsz[lret])->ProNum, (prod_ + czsz[lret])->sto, (prod_ + czsz[lret])->toL, (prod_ + czsz[lret])->inDa / 10000, \
					((prod_ + czsz[lret])->inDa % 10000) / 100, (prod_ + czsz[lret])->inDa % 100);
				//修改信息
				switch (c_a) {
				case 1:
					sprintf(midcha, "%d", czsz[lret]);

					strcat(filename, midcha);
					strcat(filename, backic);
					printf("%s", filename);
					getch();
					goto dangespzs;
					break;
				case 2:
					printf("\n\n\t选择修改内容\n\n");
					printf("\t\t1.商品名称\n");
					printf("\t\t2.商品库存\n");
					printf("\t\t3.采购价格\n");
					printf("\t\t4.销售价格\n");
					printf("\t\t5.折扣价格\n");
					printf("\t\t6.商品种类\n");
					printf("\t\t7.返回上级\n");
					c_a = lllitem(11, 14, 11, 1, 7);
					system("cls");
					topinf();
					HideCursor(1);
					printf("\n\n        序号      商品名称            采购价      销售价      折扣价      商品编号      库存     上架总数      上架时间\n\n");
					printf("         %02d       %-18s %6.2lf      %6.2lf      %6.2lf         %-3d          %-3d        %-3d        %04d/%02d/%02d       \n"\
						, h5, (prod_ + czsz[lret])->ProNam, (prod_ + czsz[lret])->cPr, (prod_ + czsz[lret])->sPr, 0.75 * ((prod_ + czsz[lret])->sPr)\
						, (prod_ + czsz[lret])->ProNum, (prod_ + czsz[lret])->sto, (prod_ + czsz[lret])->toL, (prod_ + czsz[lret])->inDa / 10000, \
						((prod_ + czsz[lret])->inDa % 10000) / 100, (prod_ + czsz[lret])->inDa % 100);
					switch (c_a) {
					case 1:
						printf("\n\n\t\t请输入新名称，一经确认不可更改！\n\n\t\t新名称：");
						fflush(stdin);
						scanf("%s", &((prod_ + czsz[lret])->ProNam));
						printf("\n\n\t\t修改完成，按任意键继续");
						getchar();
						break;
					case 2:
						printf("\n\n\t\t请输入增加或减少的库存数值，一经确认不可更改！\n\n\t\t数值：");
						fflush(stdin);
						scanf("%d", &shuliang);
						//printf("lret=%d,",lret)
						c_a = ((prod_ + czsz[lret])->toL);
						((prod_ + czsz[lret])->toL) = shuliang+c_a;
						c_a = ((prod_ + czsz[lret])->sto);
						((prod_ + czsz[lret])->sto) =c_a + shuliang;
						lret = 0;
						printf("\n\n\t\t修改完成，按任意键继续");
						getchar();
						break;
					case 3:
						printf("\n\n\t\t请输入的采购价格，一经确认不可更改！\n\n\t\t数值：");
						fflush(stdin);
						scanf("%lf", &((prod_ + czsz[lret])->cPr));
						printf("\n\n\t\t修改完成，按任意键继续");
						getchar();
						break;
					case 4:
						printf("\n\n\t\t请输入的销售价格，一经确认不可更改！\n\n\t\t数值：");
						fflush(stdin);
						scanf("%lf", &((prod_ + czsz[lret])->sPr));
						printf("\n\n\t\t修改完成，按任意键继续");
						getchar();
						break;
					case 5:
						printf("\n\n\t\t请输入的折扣价格，一经确认不可更改！\n\n\t\t数值：");
						fflush(stdin);
						scanf("%lf", &((prod_ + czsz[lret])->zpr));
						printf("\n\n\t\t修改完成，按任意键继续");
						getchar();
						break;
					case 6:
						printf("\n\n\t\t请输入商品种类代号，一经确认不可更改！\n\n\t\t数值：");
						fflush(stdin);
						scanf("%d", &((prod_ + czsz[lret])->type));
						printf("\n\n\t\t修改完成，按任意键继续");
						getchar();
						break;
					case 7: goto dangespzs; break;
					 
					}
					lret = 2736;
					goto rewrite;
				case 3:
					printf("输入Y确认删除！否者返回上一级。\n\n");
					if (getch() == 'Y') {
						c_a = 2773;
						goto rewrite;
					}
					else goto chose4managemenu;
					break;
				case 4:
					goto dangespzs;
					
				}
		
			}
					
		}

	}

	//管理函数删除和添加		
rewrite:
	if (lret == 2736) {
		FILE* RE = fopen("D:\\cx4\\cominf.txt", "w+");
		fprintf(RE, "%06d,", p_zs);
		for (int us = 0; us < p_zs; us++) {
			fprintf(RE, "%s,%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", ((prod_ + us)->ProNam), ((prod_ + us)->ProNum), \
				 ((prod_ + us)->sto), ((prod_ + us)->toL), ((prod_ + us)->inDa), ((prod_ + us)->cPr), \
				 ((prod_ + us)->sPr), ((prod_ + us)->mCnum), ((prod_ + us)->type), ((prod_ + us)->zpr));
			
		}
		fclose(RE);
		goto reenter;
	}
	if (c_a == 2773) {
		FILE* RE = fopen("D:\\cx4\\cominf.txt", "w+");
		fprintf(RE, "%06d,", p_zs-1);
		for (int us = 0; us < p_zs; us++) {
			if (((prod_ + us)->ProNum) == czsz[lret]) continue;
			fprintf(RE, "%s,%d,%d,%d,%d,%lf,%lf,%d,%d,%lf,", ((prod_ + us)->ProNam), ((prod_ + us)->ProNum), \
				((prod_ + us)->sto), ((prod_ + us)->toL), ((prod_ + us)->inDa), ((prod_ + us)->cPr), \
				((prod_ + us)->sPr), ((prod_ + us)->mCnum), ((prod_ + us)->type), ((prod_ + us)->zpr));

		}
		fclose(RE);
		goto reenter;
	}
			
reenter:
		


	

	
	
	return 0;
}

//下面的函数高度依赖
//隐藏光标
void HideCursor(int n) /*隐藏光标*/
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,n };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//设置光标坐标
static  void  SetPos(int  x, int  y)
{
	COORD  point = { x ,  y }; //光标要设置的位置x,y
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
	SetConsoleCursorPosition(HOutput, point); //设置光标位置
}
//箭头出现
static void arr(int x, int y) {
	SetPos(x, y);
	printf("->");
}
//箭头消失
static void ow(int x, int y) {
	SetPos(x, y);
	printf("  ");
}
//横向的箭头
static int topitem(int lx, int y, int width, int type) {
	int kv, lv = 1, tv,x=lx;
	HideCursor(0);
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
						x = x + type  * width;
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
						x = x - type  * width;
						arr(x, y);
					}
					else {
						x = x + width;
						arr(x, y);
					}
					break;
				default:
					//printf("请使用方向键<-和->移动光标。\n");
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
	HideCursor(0);
	return x = (x + (width - lx)) / width;
}
//商品信息展示//qy
//static int ttfunction(USE* a, PROD* b, int c)
//{
//	system("cls");
//	topinf();
//	printf("\n\n           1.按供应商查找\n");
//		printf("           2.按日期或日期区间查找\n");
//		printf("           3.按价格区间查找\n");
//		printf("           4.按种类查找\n");
//}
//顶部菜单栏
static void topinf(void) {
	printf("\n      1.搜索      2.排序      3.刷新      4.管理      \n");
}
//这是树
static int lllitem(int ly, int x, int y, int height, int type) {
	int kv, lv = 1, tv;
	y = ly;
	HideCursor(0);
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
					//printf("请使用方向键<-和->移动光标。\n");
					break;
				}
			}
			else if (kv <= 48+type && kv >= 49) {
				ow(x, y);
				y = ly + (kv - 49) * height;
				arr(x, y);
			}
			else if (kv == 13) break;
		}
		Sleep(100);

	}
	HideCursor(0);
	return y = (y - ly) / height + 1;
}