#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#include "log_in_page.h"

//用户数据表单

typedef struct{
	char name[13];			//用户登录名（12个英语或数字字符）
	char username[24];		//用户中文特征名（在商品详情页面显示）
	char password[17];		//用户登录密码（16个数字或英文字符）
	int feature;			//0为管理员,其他为注册用户(数据拓展时使用）
	int feature2;			//第二特征码（0为商家，1为普通用户）
}USER;

/*登录界面函数 函数反回值为0或1，1表示登录正常，0表示登录失败
同时三个指针分别返回用户的中文标识，第一特征码和第二特征码，回传数值还存在问题需要解决。*/

/*命名空间的疑惑*/

int log_in_page( int* pfeature) {

	//登录信息录入

	int ret = 0, i;
	FILE* LOG;
	LOG = fopen("D:\\cx4\\loginf.txt", "r");//数据路径
	int zrs;
	
	//判断登录文件是否存在
	if (LOG == NULL) {
		printf("登录信息库加载失败");
		return ret;//提前结束本程序
	}

		//读取数据提示码，为结构体呼叫足够的空间
	fscanf(LOG, "%d,", &zrs);
	USER* pren = (USER*)malloc(zrs * sizeof(USER));//数据库pren
	//数据录入
	for (i = 0; i < zrs; i++) {
		//printf("第%d组数据已成功导入\n", i + 1);// 函数头和尾都有注译的为调试函数
		fscanf(LOG, "%[^,],%[^,],%[^,],%d,%d,", &((pren + i)->name), &((pren + i)->username), \
			& ((pren + i)->password), &((pren + i)->feature), &((pren + i)->feature2));
		/*printf("%s  %s %s %d %d\n", ((pren + i)->name), ((pren + i)->username), \
			((pren + i)->password), ((pren + i)->feature), ((pren + i)->feature2));*/
	}
	//用户登录

	char judge = '0',tp_pp[17];
	char tn[13] = "0", tp[17] = "0";
	char* tnp, * tpp;
	tnp = tn, tpp = tp;

	int j, j1 = 0, j2,j4=0,j5;//j用作比较判断,j4=1时跳出循环
	char j3;
	
	while (1) {
		system("cls");
		//输入用户名
		printf("用户名：");
		scanf("%s", &tn);
		getchar();
		//printf("你输入了%s\n", tn);
		for (i = 0; i < zrs; i++) {
			j = strcmp(tnp, (pren+i)->name);
			//printf("j=%d\n", j);
			if (j == 0) break;
		}
		//没有该用户的情况
		if (j != 0) {
			system("cls");
			printf("本系统没有这个用户.\nY：重新输入   N：退出系统   C：建立新函数\n");
			scanf("%c", &j3);
			getchar();
			if (j3 == 'C');
			if (j3 == 'N') j4=1;
		}
		else {
			for (j2 = 0; j2 < 3; j2++) {
				system("cls");//
				printf("用户 %s 你好，请输入你的密码。\n密码：", tn);
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
					printf("密码错误，请重新输入。");
					getch();
				}
			}
			if (j == 0) {
				//用户数据在这里写入
				system("cls");
				//pusername = pren->username;
				//strcpy(pusername, pren->username);
				*pfeature = i;
				
				//*pfeature2 = ;
				//printf("pusername=%s pfeature=%d pfeature2=%d\n", pusername, pfeature, pfeature2);
				ret = 1;//一切正常
				j4 = 1;
				*pfeature = i;
			}
			else {
				system("cls");//
				printf("你输错三次啦。请你重启本程序；\n");
				j4=1;
			}

		}
		if (j4 == 1) break;
		getchar();
	}
	free(pren);
	return ret;
}