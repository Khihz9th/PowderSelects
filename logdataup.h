#pragma once
void logdataup(void);//��Ϣ�⵼����jian
#pragma once
extern struct user {
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

//extern struct user ren[3];
//extern struct user* pren;


