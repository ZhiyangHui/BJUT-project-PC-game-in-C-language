#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<easyx.h>
#include<conio.h>
#include<stdlib.h>
#include <corecrt.h>
#include<time.h>
#include<string.h>
#pragma comment(lib,"winmm.lib")//���ؾ�̬��

struct player_element//������Ϸ��ɫ�������ԵĽṹ��
{
	char name[20];
	char password[20];
	struct player_element *next;
	int reststep;
	int ifhaveweapon;
	int score;
	int box;
	double enemyspeed;
	int ifkunkunon;
}typedef P_E;


void map(int check,int*pnt);//��ͼ����������
void maplist(int *pnt);
void enemy(int ran,double *px,double *py);
int Ehitbox(double* px, double* py, int ix, int iy);
void pausetime(time_t start_time, int* pnt);
void writefile();
void order();
void transparentimage(int x, int y, IMAGE* src, IMAGE* mask);

//���µ�ȫ�ֱ���Ϊ�����һЩͼ�α�����Ϊ���غ������ͼ,����������ȫ�ֱ��������ڼ���ͼƬ
IMAGE img_forest,img_grass,img_grassf,img_snow,img_sand;//����͵�ͼ��ͼ�α���
IMAGE img_box,img_bush,img_bushM,img_tree,img_treeM,img_knife,img_knifeM,img_mushroom,img_mushroomM,img_chicken,img_chickenM,img_kunkun;//һЩ������ͼ
IMAGE img_BCR,img_BCRM,img_BCL,img_BCLM,img_BCS,img_BCSM,img_BCN,img_BCNM,img_enemyS,img_enemySM,img_enemyN,img_enemyNM,img_enemyR,img_enemyRM,img_enemyL,img_enemyLM,img_kunkunON;//������ͼ
IMAGE img_brick;//�嵥ǽֽ����ͼ
//player_element* h = (player_element*)malloc(sizeof(player_element));
player_element* h = NULL;
P_E* pe = (player_element*)malloc(sizeof(player_element));
int lessonnum = 1;
char usernow[20];
int scorenow=0;


player_element *creatfilelist()
{
	FILE* fp;
	fp = fopen("playerlist.txt", "r");
	player_element* p=h,*q=p;
	while(1)
	{
		p = (player_element*)malloc(sizeof(player_element));
		if(fscanf(fp,"%s %s %d",p->name,p->password,&p->score)==EOF)
		{
			free(p);
			break;
		}
		p->next = NULL;
		if (h == NULL)
		{
			//h->next = p;
			h = p;
		}
		else
			q->next = p;
		q = p;
	}
	fclose(fp);
	return h;
}


void writefile()
{
	FILE* fp;
	fp = fopen("playerlist.txt", "w");
	order();
	player_element* p = h;
	for(;p!=NULL;p=p->next)
	{
		fprintf(fp, "%s %s %d\n", p->name,p->password,p->score);
	}
	fclose(fp);
}

void order()
{
	P_E* p, * q,*temp;
	char tempname[100] = { '\0' };
	int tempscore = 0;
	char temppassword[100] = { '\0' };
	p = h;
	while (p != NULL)
	{
		q = p->next;
		while (q != NULL)
		{
			if (p->score <= q->score)
			{
				tempscore = q->score;
				q->score = p->score;
				p->score = tempscore;
				strcpy(tempname, q->name);
				strcpy(q->name, p->name);
				strcpy(p->name, tempname);
				strcpy(temppassword, q->password);
				strcpy(q->password, p->password);
				strcpy(p->password, temppassword);
			}
			q = q->next;
		}
		p = p->next;
	}
}

player_element* adduser()
{
	player_element* p;
	for (p = h; strcmp(p->name, usernow)!=0&&p!=NULL; p = p->next); 
	if(pe->score>p->score)
	{
		p->score = pe->score;
	}
	return h;
}

player_element *login(player_element*h)
{
	int input_password_chance = 3;
	int flag = 0;
	P_E* p = h,*q=NULL;
	char password[20] = { '\0' };
	char username[20] = { '\0' };
	char emptyname[20] = { '\0' };//��������û��ǲ�����û����������
	char emptypassword[20] = { '\0' };//��������û��ǲ���û����������
	do
	{
		InputBox(username, 20, "�������û�������û��������ע��ϵͳ", "��¼");
		if (strcmp(username, emptyname) == 0)
		{
			MessageBox(NULL, "�û�������Ϊ��", "��¼", MB_OK | MB_SETFOREGROUND);
		}
	} while (strcmp(username, emptyname) == 0);
	for(p=h;p!=NULL;p=p->next)
	{
		if(strcmp(p->name,username)==0)
		{
			scorenow = p->score;
			break;
		}
	}
	if (p== NULL)
	{
		q = (P_E*)malloc(sizeof(P_E));
		q->score = 0;
		MessageBox(NULL, "�û��������ڣ���ע��", "��¼", MB_OK | MB_SETFOREGROUND);
		do
		{
			InputBox(q->name, 20, "�������û���", "ע��");
			if (strcmp(q->name, emptyname) == 0)
			{
				MessageBox(NULL, "�û�������Ϊ��", "ע��", MB_OK | MB_SETFOREGROUND);
			}
		} while (strcmp(q->name, emptyname) == 0);
		do
		{
			InputBox(password, 20, "����������", "ע��");
			if (strcmp(password, emptyname) == 0)
			{
				MessageBox(NULL, "���벻��Ϊ��", "ע��", MB_OK | MB_SETFOREGROUND);
			}
		} while (strcmp(password, emptyname) == 0);
		strcpy(q->password, password);
		q->next = NULL;
		for (p = h; p->next!= NULL; p = p->next);
		p->next = q;
		p = p->next;
		flag = 1;
	}
	do{
		if(flag==0)
		{
			InputBox(password, 20, "���������룬���20λ", "��¼");
		}
		if (strcmp(p->password, password) == 0&&flag==0)

		{
			MessageBox(NULL, "��ӭ������ȥ��ս��", "��ӭ", MB_SETFOREGROUND);
			strcpy(usernow,username);
			return h;
		}
		if (strcmp(p->password, password) == 0 && flag == 1)
		{
			MessageBox(NULL, "��ӭ����һ�����汾��Ϸ��ȥ��ս��", "��ӭ", MB_SETFOREGROUND);
			strcpy(usernow, username);
			return h;
		}
		else
		{
			if(input_password_chance ==3)
			{
				MessageBox(NULL, "�������������3�λ���\n�������޶�������������ȷ��������Զ��ر�", "��¼", MB_SETFOREGROUND);
			}
			if (input_password_chance == 2)
			{
				MessageBox(NULL, "�������������2�λ���\n�������޶�������������ȷ��������Զ��ر�", "��¼", MB_SETFOREGROUND);
			}
			if (input_password_chance == 1)
			{
				MessageBox(NULL, "�������������1�λ���\n�������޶�������������ȷ��������Զ��ر�", "��¼", MB_SETFOREGROUND);
			}
			if (input_password_chance == 0)
			{
				MessageBox(NULL, "�Բ�����δ���ڹ涨�����ڳɹ���������\n��¼ʧ��", "��¼ʧ��", MB_SETFOREGROUND);
				exit(-1);
			}
			input_password_chance--;
		}
	} while ((strcmp(p->password, emptypassword) != 0));
}

void ifwin(int *pnt)
{
	static int firstpass1 = 6;
	static int firstpass2 = 13;
	static int firstpass3 = 21;
	static int lessoncount[3] = { '\0' };
	static char score[20] = { '\0' };
	static char s[100] = "��ϲ�㣬ͨ������Ϸ,����Ϊ��";
	if (pe->box == firstpass1)
	{
		if (lessoncount[0] == 0)
		{
			time_t start;
			time(&start);
			MessageBox(NULL, "��ϲ�㣬ͨ����һ��\n�ڶ���ÿ����������������", "ͨ��", MB_OK | MB_SETFOREGROUND);
			pausetime(start, pnt);
		}
		lessoncount[0] = 1;
		cleardevice();
		lessonnum = 2;
	}
	else if (pe->box == firstpass2)
	{
		if (lessoncount[1] == 0)
		{
			time_t start;
			time(&start);
			MessageBox(NULL, "��ϲ�㣬ͨ���ڶ���\n���������ʣ��ʱ�佫�����", "ͨ��", MB_OK | MB_SETFOREGROUND);
			pausetime(start, pnt);
		}
		lessoncount[1] = 1;
		cleardevice();
		lessonnum = 3;
	}
	else if (pe->box == firstpass3)
	{
		if (lessoncount[2] == 0)
		{
			time_t start;
			time(&start);
			h = adduser();
			writefile();
			sprintf(score, "%d", pe->score);
			strcat(s, score);
			MessageBox(NULL,s, "ͨ��", MB_OK | MB_SETFOREGROUND);
			exit(-1);
			pausetime(start, pnt);
		}
		lessoncount[2] = 1;
		cleardevice();
		lessonnum = 3;
	}

	if(pe->reststep<0)
	{
		h = adduser();
		writefile();
		MessageBox(NULL, "��Ĳ����þ�����Ϸʧ��", "��Ϸʧ��", MB_OK | MB_SETFOREGROUND);
		exit(-1);

	}
}

void lessonjudge( )
{
	static int count = 0;
	if(lessonnum==1&&count==0)
	{
		pe->reststep = 25;
		pe->ifhaveweapon = 0;
		pe->score = 0;
		pe->box = 0;
		pe->enemyspeed = 0.25;
		count++;
	}
	if(lessonnum==2&&count==1)
	{
		
		
		//pe->box = 0;
		if(pe->ifkunkunon==1)
		{
			pe->reststep = 2000;
		}
		else
		{
			pe->reststep = 50;
		}
		pe->ifhaveweapon = 0;
		pe->enemyspeed = 0.35;
		count++;
	}
	if (lessonnum ==3  && count == 2)
	{
		//pe->box = 0
		if (pe->ifkunkunon == 1)
		{
			pe->reststep = 2000;
		}
		else
		{
			pe->reststep = 25;
		}
		pe->ifhaveweapon = 0;
		pe->enemyspeed = 0.45;
	}
}

void pausetime(time_t start_time,int *pnt)
{
	struct tm start_time_tm;
	localtime_s(&start_time_tm, &start_time);
	int sum_start_time = 3600 * start_time_tm.tm_hour + 60 * start_time_tm.tm_min + start_time_tm.tm_sec;

	time_t current_time;
	time(&current_time);
	struct tm current_time_tm; 
	localtime_s(&current_time_tm, &current_time);
	int sum_current_time = 3600 * current_time_tm.tm_hour + 60 * current_time_tm.tm_min + current_time_tm.tm_sec;
	* pnt = * pnt + sum_current_time - sum_start_time;
}

void transparentimage(int x, int y, IMAGE* src, IMAGE* mask)//��������͸����ͼ
{
	putimage(x, y, mask,SRCAND);
	putimage(x, y, src,SRCINVERT);
}

void setbutton(int x, int y, int w, int h, const char* text)//��������һЩ��ť
{
	setbkmode(TRANSPARENT);//��Щsetһ��Ҫ����ǰ��
	setfillcolor(BROWN);
	settextcolor(BLACK);
	settextstyle(30, 0, "����");
	char text_[50] = " ";
	strcpy_s(text_, text);
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	fillroundrect(x, y, x + w, y + h, 10, 10);
	outtextxy(tx, ty, text);
}

void maplist(int *pnt)//���Ƶ�ͼ�Ҳ���嵥
{
	static int count = 0;
	ExMessage msg;
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(35, 0, "��������");
	putimage(920, 0, &img_brick);
	outtextxy(935, 45, "�ĵ�����");
	setbutton(940, 650, 120, 50, "�˳���Ϸ");//ע��˳��,����ǰ���������
	setbutton(940, 560, 120, 50, "��ͣ��Ϸ");

	settextcolor(WHITE);//�����ʣ���ʱ���Լ�����������
	settextstyle(15, 0, "����");
	setfillcolor(BLACK);
	fillroundrect(940, 110, 1060, 160,10,10);
	outtextxy(945, 115, "ʣ�ಽ��");
	fillroundrect(940, 200, 1060, 250, 10, 10);
	outtextxy(945, 205, "ʣ��ʱ��");

	setfillcolor(RGB(153,53,103));//����ǹ�������Ļ��������Լ�����û����ͷ���������
	settextstyle(12, 0, "����");
	fillroundrect(940, 290, 1060, 520, 10, 10);
	outtextxy(945, 295, "���������");
	outtextxy(945, 335, "��ǰ�÷֣�");
	outtextxy(945, 375, "��ʷ��߷֣�");
	outtextxy(945, 415, "�Ƿ�������: ");
	outtextxy(945, 455, "��ͨ�ص�����Ŀ��");

	if(count==0)
	{
		putimage(120, 0, &img_kunkun);
	}
	else if(count==1)
	{
		putimage(120, 0, &img_kunkunON);
	}
	if(peekmessage(&msg,EX_MOUSE))
	{
		switch(msg.message)
		{
		case WM_LBUTTONDOWN:
			if (msg.x >= 945 && msg.x <= 945 + 120 && msg.y >= 650 && msg.y <= 650 + 50)
			{
				h = adduser();
				MessageBox(NULL, "��Ϸ�����ˣ���л��������", "��Ϸ����", MB_OK | MB_SETFOREGROUND);
				writefile();
				exit(-1);
			}
			if(msg.x>=945&&msg.x<=945+120&&msg.y>=560&&msg.y<=560+50)
			{
				time_t start;
				time(&start);
				MessageBox(NULL, "��Ϸ����ͣ", "��ͣ��Ϸ", MB_OK | MB_SETFOREGROUND);
				pausetime(start, pnt);
			}
			if(msg.x>=120&&msg.x<=120+120&&msg.y>=0&&msg.y<=40&&count==0)
			{
				pe->score -= 5000;
				pe->reststep = 2000;
				pe->ifkunkunon = 1;
				count++;
			}
		}
	}
}

void iload()//��������ͼƬ
{
	loadimage(&img_forest, "./gamemap\\forest.png",1080,720);
	loadimage(&img_grass, "./gamemap\\grass.png", 1080, 720);
	loadimage(&img_snow, "./gamemap\\snow.png", 1080, 720);
	loadimage(&img_sand, "./gamemap\\sand.png", 1080, 720);
	loadimage(&img_box, "./gamemap\\box.png",40,40);
	loadimage(&img_BCR, "./gamemap\\BC_R.png",40,40);
	loadimage(&img_BCRM, "./gamemap\\BC_RM.png", 40, 40);
	loadimage(&img_BCLM, "./gamemap\\BC_LM.png", 40, 40);
	loadimage(&img_BCL, "./gamemap\\BC_L.png", 40, 40);
	loadimage(&img_BCS, "./gamemap\\BC_S.png", 40, 40);
	loadimage(&img_BCSM, "./gamemap\\BC_SM.png", 40, 40);
	loadimage(&img_BCN, "./gamemap\\BC_N.png", 40, 40);
	loadimage(&img_BCNM, "./gamemap\\BC_NM.png", 40, 40);
	loadimage(&img_brick, "./gamemap\\brick.jpg",180,720);
	loadimage(&img_bush, "./gamemap\\bush.png", 40, 40);
	loadimage(&img_bushM, "./gamemap\\bushM.png", 40, 40);
	loadimage(&img_tree, "./gamemap\\tree.png", 40, 40);
	loadimage(&img_treeM, "./gamemap\\treeM.png", 40, 40);
	loadimage(&img_enemyS, "./gamemap\\enemy_S.png", 40, 40);
	loadimage(&img_enemySM, "./gamemap\\enemy_SM.png", 40, 40);
	loadimage(&img_enemyN, "./gamemap\\enemy_N.png", 40, 40);
	loadimage(&img_enemyNM, "./gamemap\\enemy_NM.png", 40, 40);
	loadimage(&img_enemyR, "./gamemap\\enemy_R.png", 40, 40);
	loadimage(&img_enemyRM, "./gamemap\\enemy_RM.png", 40, 40);
	loadimage(&img_enemyL, "./gamemap\\enemy_L.png", 40, 40);
	loadimage(&img_enemyLM, "./gamemap\\enemy_LM.png", 40, 40);
	loadimage(&img_knife, "./gamemap\\knife.png", 40, 40);
	loadimage(&img_knifeM, "./gamemap\\knife_M.png", 40, 40);
	loadimage(&img_mushroom, "./gamemap\\mushroom.png", 40, 40);
	loadimage(&img_mushroomM, "./gamemap\\mushroom_M.png", 40, 40);
	loadimage(&img_chicken, "./gamemap\\chicken.png", 40, 40);
	loadimage(&img_chickenM, "./gamemap\\chicken_M.png", 40, 40);
	loadimage(&img_kunkun, "./gamemap\\kunkun.png", 120, 40);
	loadimage(&img_kunkunON, "./gamemap\\kunkun_on.png", 120, 40);
}

void creatmenu()//�����˵�ҳ��
{
	iload();//����ͼƬ
	setbkmode(TRANSPARENT);//��������
	settextcolor(YELLOW);
	settextstyle(130, 0, "��������");
	HWND hnd = GetHWnd();//��ȡ���ھ��
	SetWindowText(hnd, "�ĵ�����");//���ô��ڱ���
	putimage(0, 0, &img_forest);
	outtextxy(300, 100, "�ĵ�����");
	setbutton(450, 580, 150, 75, "���а�");
	setbutton(450, 280, 150, 75, "��ʼ��Ϸ");//��ʼ��Ϸ��ť
	setbutton(450, 380, 150, 75, "�˳���Ϸ");//������Ϸ��ť
	setbutton(450, 480, 150, 75, "��Ϸ���");//��Ϸ��鰴ť
}

void checkitemap_step_time(int x, int y, double* px, double* py, int sum_start_time, int* pnt)//��������ͼ�е���Ʒ�Ƿ񻹴����Լ�ʣ��Ĳ�����ʣ��ʱ��ĺ����ĺ���
{
	ExMessage msg;
	char num[20];
	char timenum[100];
	char weapon[4] = { 'N','O' };
	char score[20] = { '\0' };
	char historyscore[20] = { '\0' };
	char lack_of_box[10] = { '\0' };
	static int count[100]={0};//ע�����static
	static int requiredbox1 = 8;
	static int requiredbox2 = 11;
	static int requiredbox3 = 10;
	static int boxlack1 = 6;
	static int boxlack2 = 7;
	static int boxlack3 = 8;


	time_t current_time;
	time(&current_time);
	struct tm current_time_tm;
	localtime_s(&current_time_tm, &current_time);
	int sum_current_time = 3600 * current_time_tm.tm_hour + 60 * current_time_tm.tm_min + current_time_tm.tm_sec;
	int totaltime = sum_start_time + *pnt - sum_current_time;
	static int lessontime=240;
	int now_time = lessontime + totaltime;
	static int timecount = 0;
	if(lessonnum==3&&timecount==0)
	{
		now_time/=2;
		timecount == 1;
	}
	
	if(now_time<0)
	{
		h = adduser();
		writefile();
		MessageBox(NULL, "���ʱ��ľ��ˣ���Ϸ����", "��Ϸʧ��", MB_OK | MB_SETFOREGROUND);
		exit(-1);
	}


	settextstyle(12, 0, "΢���ź�");
	setbkmode(TRANSPARENT);
	map(900,pnt);
	if(lessonnum==1&&requiredbox1<6)
	{
		h = adduser();
		writefile();
		MessageBox(NULL, "������ӱ���������������ͨ��������", "��Ϸʧ��", MB_OK | MB_SETFOREGROUND);
		exit(-1);
	}
	if(lessonnum==2&&requiredbox2<7)
	{
		h = adduser();
		writefile();
		MessageBox(NULL, "������ӱ���������������ͨ��������", "��Ϸʧ��", MB_OK | MB_SETFOREGROUND);
		exit(-1);
	}
	if (lessonnum == 3 && requiredbox3 < 8)
	{
		h = adduser();
		writefile();
		MessageBox(NULL, "������ӱ���������������ͨ��������", "��Ϸʧ��", MB_OK | MB_SETFOREGROUND);
		exit(-1);
	}
	if (lessonnum == 1)
	{
		if ((x >= 120 && x < 160 && y >= 120 && y < 160) || Ehitbox(px, py, 120.0, 120.0))//x��y���ж�����һ��>=һ��<=
		{
			map(0, pnt);
			if (count[0] == 0 && Ehitbox(px, py, 120.0, 120.0) == 1)
			{
				requiredbox1--;
				count[0] = 1;
			}
			if (count[0] == 0 && Ehitbox(px, py, 120.0, 120.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[0] = 1;
			}
		}
		if ((x >= 200 && x < 240 && y >= 200 && y < 240) || Ehitbox(px, py, 200.0, 200.0))
		{
			map(1, pnt);
			if (count[1] == 0 && Ehitbox(px, py, 200.0, 200.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[1] = 1;
			}
			if (count[1] == 0 && Ehitbox(px, py, 200.0, 200.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[1] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 560 && y < 600) || Ehitbox(px, py, 560.0, 560.0))
		{
			map(2, pnt);
			if (count[2] == 0 && Ehitbox(px, py, 560.0, 560.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[2] = 1;
			}
			if (count[2] == 0 && Ehitbox(px, py, 560.0, 560.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[2] = 1;
			}
		}
		if ((x >= 280 && x < 320 && y >= 80 && y < 120) || Ehitbox(px, py, 280.0, 80.0))
		{
			if (Ehitbox(px, py, 280.0, 80.0) == 1)
			{
				map(3, pnt);
			}
			if (count[3] == 0 && Ehitbox(px, py, 280.0, 80.0) == 0&&pe->ifhaveweapon==0)
			{
				map(3, pnt);
				pe->ifhaveweapon += 1;
				count[3] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 280 && y < 320) || Ehitbox(px, py, 160.0, 280.0))
		{
			map(4, pnt);
			if (count[4] == 0 && Ehitbox(px, py, 160.0, 280.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[4] = 1;
			}
			if (count[4] == 0 && Ehitbox(px, py, 160.0, 280.0) == 0)
			{
				pe->reststep -= 10;
				count[4] = 1;
			}
		}
		if ((x >= 0 && x < 40 && y >= 80 && y < 120) || Ehitbox(px, py, 0.0, 80.0))
		{
			map(5, pnt);
			if (count[5] == 0 && Ehitbox(px, py, 0.0, 80.0) == 1)
			{
				requiredbox1--;
				count[5] = 1;
			}
			if (count[5] == 0 && Ehitbox(px, py, 0.0, 80.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[5] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 240 && y < 280) || Ehitbox(px, py, 560.0, 240.0))
		{
			if(Ehitbox(px, py, 560.0, 240.0)==1)
			{
				map(6, pnt);
			}
			if (count[6] == 0 && Ehitbox(px, py, 280.0, 80.0) == 0&&pe->ifhaveweapon==0)
			{
				map(6, pnt);
				pe->ifhaveweapon += 1;
				count[6] = 1;
			}
		}
		if ((x >= 640 && x < 680 && y >= 560 && y < 600) || Ehitbox(px, py, 640.0, 560.0))
		{
			if (Ehitbox(px, py, 640.0, 560.0) == 1)
			{
				map(7, pnt);
			}
			if (count[7] == 0 && Ehitbox(px, py, 640.0, 560.0) == 0 && pe->ifhaveweapon == 0)
			{
				map(7, pnt);
				pe->ifhaveweapon += 1;
				count[7] = 1;
			}
		}
		if ((x >= 400 && x < 440 && y >= 480 && y < 520) || Ehitbox(px, py, 400.0, 480.0))//x��y���ж�����һ��>=һ��<=
		{
			map(8, pnt);
			if (count[8] == 0 && Ehitbox(px, py, 400.0, 480.0) == 1)
			{
				requiredbox1--;
				count[8] = 1;
			}
			if (count[8] == 0 && Ehitbox(px, py, 400.0, 480.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[8] = 1;
			}
		}
		if ((x >= 360 && x < 400 && y >= 680 && y < 720) || Ehitbox(px, py, 360.0, 680.0))//x��y���ж�����һ��>=һ��<=
		{
			map(9, pnt);
			if (count[9] == 0 && Ehitbox(px, py, 360.0, 680.0) == 1)
			{
				requiredbox1--;
				count[9] = 1;
			}
			if (count[9] == 0 && Ehitbox(px, py, 360.0, 680.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[9] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 560 && y < 600) || Ehitbox(px, py, 160.0, 560.0))//x��y���ж�����һ��>=һ��<=
		{
			map(10, pnt);
			if (count[10] == 0 && Ehitbox(px, py, 160.0, 560.0) == 1)
			{
				requiredbox1--;
				count[10] = 1;
			}
			if (count[10] == 0 && Ehitbox(px, py, 160.0, 560.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[10] = 1;
			}
		}
		if ((x >= 720 && x < 760 && y >= 160 && y < 200) || Ehitbox(px, py, 720.0, 160.0))//x��y���ж�����һ��>=һ��<=
		{
			map(11, pnt);
			if (count[11] == 0 && Ehitbox(px, py, 720.0, 160.0) == 1)
			{
				requiredbox1--;
				count[11] = 1;
			}
			if (count[11] == 0 && Ehitbox(px, py, 720.0, 160.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[11] = 1;
			}
		}
		if ((x >= 760 && x < 800 && y >= 320 && y < 360) || Ehitbox(px, py, 760.0, 320.0))//x��y���ж�����һ��>=һ��<=
		{
			map(12, pnt);
			if (count[12] == 0 && Ehitbox(px, py, 760.0, 320.0) == 1)
			{
				requiredbox1--;
				count[12] = 1;
			}
			if (count[12] == 0 && Ehitbox(px, py, 760.0, 320.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[12] = 1;
			}
		}
		if ((x >= 640 && x < 680 && y >= 640 && y < 680) || Ehitbox(px, py, 640.0, 640.0))//x��y���ж�����һ��>=һ��<=
		{
			map(13, pnt);
			if (count[13] == 0 && Ehitbox(px, py, 640.0, 640.0) == 1)
			{
				requiredbox1--;
				count[13] = 1;
			}
			if (count[13] == 0 && Ehitbox(px, py, 640.0, 640.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[13] = 1;
			}
		}
		if ((x >= 280 && x < 320 && y >= 520 && y < 560) || Ehitbox(px, py, 280.0, 520.0))
		{
			map(14, pnt);
			if (count[14] == 0 && Ehitbox(px, py, 280.0, 520.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[14] = 1;
			}
			if (count[14] == 0 && Ehitbox(px, py, 280.0, 520.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[14] = 1;
			}
		}
		if ((x >= 440 && x < 480 && y >= 480 && y < 520) || Ehitbox(px, py, 440.0,480.0))
		{
			map(15, pnt);
			if (count[15] == 0 && Ehitbox(px, py, 440.0, 580.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[15] = 1;
			}
			if (count[15] == 0 && Ehitbox(px, py, 440.0, 580.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[15] = 1;
			}
		}
		if ((x >= 400 && x < 440 && y >= 280 && y < 320) || Ehitbox(px, py, 400.0, 280.0))
		{
			map(16, pnt);
			if (count[16] == 0 && Ehitbox(px, py, 400.0, 280.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[16] = 1;
			}
			if (count[16] == 0 && Ehitbox(px, py, 400.0, 280.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[16] = 1;
			}
		}
		if ((x >= 0 && x < 40 && y >= 480 && y < 520) || Ehitbox(px, py, 0.0, 480.0))
		{
			map(17, pnt);
			if (count[17] == 0 && Ehitbox(px, py, 0.0, 480.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[17] = 1;
			}
			if (count[17] == 0 && Ehitbox(px, py, 0.0, 480.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[17] = 1;
			}
		}
		if ((x >= 860 && x < 900 && y >= 40 && y < 80) || Ehitbox(px, py, 860.0, 40.0))
		{
			map(18, pnt);
			if (count[18] == 0 && Ehitbox(px, py, 860.0, 40.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[18] = 1;
			}
			if (count[18] == 0 && Ehitbox(px, py, 860.0, 40.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[18] = 1;
			}
		}
		if ((x >= 740 && x < 780 && y >= 0 && y < 40) || Ehitbox(px, py, 740.0, 0.0))//�����
		{
			map(19, pnt);
			if (count[19] == 0 && Ehitbox(px, py, 740.0, 0.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[19] = 1;
			}
			if (count[19] == 0 && Ehitbox(px, py, 740.0, 0.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[19] = 1;
			}
		}
		if ((x >= 600 && x < 640 && y >= 320 && y < 360) || Ehitbox(px, py, 600.0, 320.0))//�����
		{
			map(20, pnt);
			if (count[20] == 0 && Ehitbox(px, py, 600.0, 320.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[20] = 1;
			}
			if (count[20] == 0 && Ehitbox(px, py, 600.0, 320.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[20] = 1;
			}
		}
		if ((x >= 320 && x < 360 && y >= 200 && y < 240) || Ehitbox(px, py, 320.0, 200.0))//�����
		{
			map(21, pnt);
			if (count[21] == 0 && Ehitbox(px, py, 320.0, 200.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[21] = 1;
			}
			if (count[21] == 0 && Ehitbox(px, py, 320.0, 200.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[21] = 1;
			}
		}
		if ((x >= 40 && x < 80 && y >= 680 && y < 720) || Ehitbox(px, py, 40.0, 680.0))
		{
			map(22, pnt);
			if (count[22] == 0 && Ehitbox(px, py, 40.0, 680.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[22] = 1;
			}
			if (count[22] == 0 && Ehitbox(px, py, 40.0, 680.0) == 0)
			{
				pe->reststep -= 10;
				count[22] = 1;
			}
		}
		if ((x >= 360 && x < 400 && y >= 120 && y < 160) || Ehitbox(px, py, 360.0, 120.0))
		{
			map(23, pnt);
			if (count[23] == 0 && Ehitbox(px, py, 360.0, 120.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[23] = 1;
			}
			if (count[23] == 0 && Ehitbox(px, py, 360.0, 120.0) == 0)
			{
				pe->reststep -= 10;
				count[23] = 1;
			}
		}
		if ((x >= 440 && x < 480 && y >= 120 && y < 160) || Ehitbox(px, py, 440.0, 120.0))//x��y���ж�����һ��>=һ��<=
		{
			map(24, pnt);
			if (count[24] == 0 && Ehitbox(px, py, 440.0, 120.0) == 1)
			{
				requiredbox1--;
				count[24] = 1;
			}
			if (count[24] == 0 && Ehitbox(px, py, 440.0, 120.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack1--;
				count[24] = 1;
			}
		}
	}
	if (lessonnum == 2)
	{
		
		if ((x >= 400 && x < 440 && y >= 120 && y < 160) || Ehitbox(px, py, 400.0, 120.0))//x��y���ж�����һ��>=һ��<=
		{
			map(25, pnt);
			if (count[25] == 0 && Ehitbox(px, py, 400.0, 120.0) == 1)
			{
				requiredbox2--;
				count[25] = 1;
			}
			if (count[25] == 0 && Ehitbox(px, py, 400.0, 120.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[25] = 1;
			}
		}
		if ((x >= 120 && x < 160 && y >= 640 && y < 680) || Ehitbox(px, py, 120.0, 640.0))//x��y���ж�����һ��>=һ��<=
		{
			map(26, pnt);
			if (count[26] == 0 && Ehitbox(px, py, 120.0, 640.0) == 1)
			{
				requiredbox2--;
				count[26] = 1;
			}
			if (count[26] == 0 && Ehitbox(px, py, 120.0, 640.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[26] = 1;
			}
		}
		if ((x >= 0 && x < 40 && y >= 440 && y < 480) || Ehitbox(px, py, 0.0, 440.0))//x��y���ж�����һ��>=һ��<=
		{
			map(27, pnt);
			if (count[27] == 0 && Ehitbox(px, py, 0.0, 440.0) == 1)
			{
				requiredbox2--;
				count[27] = 1;
			}
			if (count[27] == 0 && Ehitbox(px, py, 0.0, 440.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[27] = 1;
			}
		}
		if ((x >= 560&& x < 600 && y >= 440 && y < 480) || Ehitbox(px, py, 560.0, 440.0))//x��y���ж�����һ��>=һ��<=
		{
			map(28, pnt);
			if (count[28] == 0 && Ehitbox(px, py, 560.0, 440.0) == 1)
			{
				requiredbox2--;
				count[28] = 1;
			}
			if (count[28] == 0 && Ehitbox(px, py, 560.0, 440.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[28] = 1;
			}
		}
		if ((x >= 680 && x < 720 && y >= 160 && y < 200) || Ehitbox(px, py, 680.0, 160.0))//x��y���ж�����һ��>=һ��<=
		{
			map(29, pnt);
			if (count[29] == 0 && Ehitbox(px, py, 680.0, 160.0) == 1)
			{
				requiredbox2--;
				count[29] = 1;
			}
			if (count[29] == 0 && Ehitbox(px, py, 680.0, 160.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[29] = 1;
			}
		}
		if ((x >= 200 && x < 240 && y >= 200 && y < 240) || Ehitbox(px, py, 200.0, 200.0))//x��y���ж�����һ��>=һ��<=
		{
			map(30, pnt);
			if (count[30] == 0 && Ehitbox(px, py, 200.0, 200.0) == 1)
			{
				requiredbox2--;
				count[30] = 1;
			}
			if (count[30] == 0 && Ehitbox(px, py, 200.0, 200.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[30] = 1;
			}
		}
		if ((x >= 360 && x < 400 && y >= 280 && y < 320) || Ehitbox(px, py, 360.0, 280.0))//x��y���ж�����һ��>=һ��<=
		{
			map(31, pnt);
			if (count[31] == 0 && Ehitbox(px, py, 360.0, 280.0) == 1)
			{
				requiredbox2--;
				count[31] = 1;
			}
			if (count[31] == 0 && Ehitbox(px, py, 360.0, 280.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[31] = 1;
			}
		}
		if ((x >= 760 && x < 800 && y >= 600 && y < 640) || Ehitbox(px, py, 760.0, 600.0))//x��y���ж�����һ��>=һ��<=
		{
			map(32, pnt);
			if (count[32] == 0 && Ehitbox(px, py, 760.0, 600.0) == 1)
			{
				requiredbox2--;
				count[32] = 1;
			}
			if (count[32] == 0 && Ehitbox(px, py, 760.0, 600.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[32] = 1;
			}
		}
		if ((x >= 160 && x <200 && y >= 520 && y < 560) || Ehitbox(px, py, 160.0, 520.0))//x��y���ж�����һ��>=һ��<=
		{
			map(33, pnt);
			if (count[33] == 0 && Ehitbox(px, py, 160.0, 520.0) == 1)
			{
				requiredbox2--;
				count[33] = 1;
			}
			if (count[33] == 0 && Ehitbox(px, py, 160.0, 520.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[33] = 1;
			}
		}
		if ((x >= 800 && x < 840 && y >= 120 && y < 160) || Ehitbox(px, py, 800.0, 120.0))//x��y���ж�����һ��>=һ��<=
		{
			map(34, pnt);
			if (count[34] == 0 && Ehitbox(px, py, 800.0, 120.0) == 1)
			{
				requiredbox2--;
				count[34] = 1;
			}
			if (count[34] == 0 && Ehitbox(px, py, 800.0, 120.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[34] = 1;
			}
		}
		if ((x >= 120 && x < 160 && y >= 120 && y < 160) || Ehitbox(px, py, 120.0, 120.0))//x��y���ж�����һ��>=һ��<=
		{
			map(35, pnt);
			if (count[35] == 0 && Ehitbox(px, py, 120.0, 120.0) == 1)
			{
				requiredbox2--;
				count[35] = 1;
			}
			if (count[35] == 0 && Ehitbox(px, py, 120.0, 120.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack2--;
				count[35] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 280 && y < 320) || Ehitbox(px, py, 160.0, 280.0))
		{
			map(36, pnt);
			if (count[36] == 0 && Ehitbox(px, py, 160.0, 280.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[36] = 1;
			}
			if (count[36] == 0 && Ehitbox(px, py, 160.0, 280.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[36] = 1;
			}
		}
		if ((x >= 280 && x < 320 && y >= 80 && y < 120) || Ehitbox(px, py, 280.0, 80.0))
		{
			map(37, pnt);
			if (count[37] == 0 && Ehitbox(px, py, 280.0, 80.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[37] = 1;
			}
			if (count[37] == 0 && Ehitbox(px, py, 280.0, 80.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[37] = 1;
			}
		}
		if ((x >= 280 && x < 320 && y >= 320 && y < 360) || Ehitbox(px, py, 280.0, 320.0))
		{
			map(38, pnt);
			if (count[38] == 0 && Ehitbox(px, py, 280.0, 320.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[38] = 1;
			}
			if (count[38] == 0 && Ehitbox(px, py, 280.0, 320.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[38] = 1;
			}
		}
		if ((x >= 440 && x < 480 && y >= 480 && y < 520) || Ehitbox(px, py, 440.0, 480.0))
		{
			map(39, pnt);
			if (count[39] == 0 && Ehitbox(px, py, 440.0, 480.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[39] = 1;
			}
			if (count[39] == 0 && Ehitbox(px, py, 440.0, 480.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[39] = 1;
			}
		}
		if ((x >= 400 && x < 440 && y >= 520 && y < 560) || Ehitbox(px, py, 400.0, 520.0))
		{
			map(40, pnt);
			if (count[40] == 0 && Ehitbox(px, py, 400.0, 520.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[40] = 1;
			}
			if (count[40] == 0 && Ehitbox(px, py, 400.0, 520.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[40] = 1;
			}
		}
		if ((x >= 600 && x < 640 && y >= 320 && y < 360) || Ehitbox(px, py, 600.0, 320.0))
		{
			map(41, pnt);
			if (count[41] == 0 && Ehitbox(px, py, 600.0, 320.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[41] = 1;
			}
			if (count[41] == 0 && Ehitbox(px, py, 600.0, 320.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[41] = 1;
			}
		}
		if ((x >= 0 && x < 40 && y >= 80 && y < 120) || Ehitbox(px, py,0.0,80.0))
		{
			map(42, pnt);
			if (count[42] == 0 && Ehitbox(px, py, 0.0, 80.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[42] = 1;
			}
			if (count[42] == 0 && Ehitbox(px, py, 0.0, 80.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[42] = 1;
			}
		}
		if ((x >= 320 && x < 360 && y >= 120 && y < 160) || Ehitbox(px, py, 320.0, 120.0))
		{
			map(43, pnt);
			if (count[43] == 0 && Ehitbox(px, py, 320.0, 120.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[43] = 1;
			}
			if (count[43] == 0 && Ehitbox(px, py, 320.0, 120.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[43] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 160 && y < 200) || Ehitbox(px, py, 160.0, 160.0))
		{
			map(44, pnt);
			if (count[44] == 0 && Ehitbox(px, py, 160.0, 160.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[44] = 1;
			}
			if (count[44] == 0 && Ehitbox(px, py, 160.0, 160.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[44] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 400 && y < 440) || Ehitbox(px, py, 560.0, 400.0))
		{
			map(45, pnt);
			if (count[45] == 0 && Ehitbox(px, py, 560.0, 400.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[45] = 1;
			}
			if (count[45] == 0 && Ehitbox(px, py, 560.0, 400.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[45] = 1;
			}
		}
		if ((x >= 760 && x < 800 && y >= 520 && y < 560) || Ehitbox(px, py, 760.0, 520.0))
		{
			map(46, pnt);
			if (count[46] == 0 && Ehitbox(px, py, 760.0, 520.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[46] = 1;
			}
			if (count[46] == 0 && Ehitbox(px, py, 760.0, 520.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[46] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 640 && y < 680) || Ehitbox(px, py, 560.0, 640.0))
		{
			map(47, pnt);
			if (count[47] == 0 && Ehitbox(px, py, 560.0, 640.0) == 1)
			{
				pe->enemyspeed += 0.02;
				count[47] = 1;
			}
			if (count[47] == 0 && Ehitbox(px, py, 560.0, 640.0) == 0)
			{
				pe->reststep += 10;
				pe->score += 40;
				count[47] = 1;
			}
		}
		if ((x >= 640 && x < 680 && y >= 40 && y < 80) || Ehitbox(px, py, 640.0, 40.0))
		{
			if (Ehitbox(px, py, 640.0, 40.0) == 1)
			{
				map(48, pnt);
			}
			if (count[48] == 0 && Ehitbox(px, py, 640.0, 40.0) == 0 && pe->ifhaveweapon == 0)
			{
				map(48, pnt);
				pe->ifhaveweapon += 1;
				count[48] = 1;
			}
		}
		if ((x >= 400 && x < 440 && y >= 400 && y < 440) || Ehitbox(px, py, 400.0, 400.0))
		{
			if (Ehitbox(px, py, 400.0, 400.0) == 1)
			{
				map(49, pnt);
			}
			if (count[49] == 0 && Ehitbox(px, py, 400.0, 400.0) == 0 && pe->ifhaveweapon == 0)
			{
				map(49, pnt);
				pe->ifhaveweapon += 1;
				count[49] = 1;
			}
		}
		if ((x >= 40 && x < 80 && y >= 680 && y < 720) || Ehitbox(px, py, 40.0, 680.0))
		{
			map(50, pnt);
			if (count[50] == 0 && Ehitbox(px, py, 40.0, 680.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[50] = 1;
			}
			if (count[50] == 0 && Ehitbox(px, py, 40.0, 680.0) == 0)
			{
				pe->reststep -= 10;
				count[50] = 1;
			}
		}
		if ((x >= 0 && x < 80 && y >= 480 && y < 520) || Ehitbox(px, py, 0.0, 480.0))
		{
			map(51, pnt);
			if (count[51] == 0 && Ehitbox(px, py, 0.0, 480.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[51] = 1;
			}
			if (count[51] == 0 && Ehitbox(px, py, 0.0, 480.0) == 0)
			{
				pe->reststep -= 10;
				count[51] = 1;
			}
		}
		if ((x >= 520 && x < 560 && y >= 120 && y < 160) || Ehitbox(px, py, 520.0, 120.0))
		{
			map(52, pnt);
			if (count[52] == 0 && Ehitbox(px, py, 520.0, 120.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[52] = 1;
			}
			if (count[52] == 0 && Ehitbox(px, py, 520.0, 120.0) == 0)
			{
				pe->reststep -= 10;
				count[52] = 1;
			}
		}
		if ((x >= 720 && x < 760 && y >= 400 && y < 440) || Ehitbox(px, py, 720.0, 400.0))
		{
			map(53, pnt);
			if (count[53] == 0 && Ehitbox(px, py, 720.0, 400.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[53] = 1;
			}
			if (count[53] == 0 && Ehitbox(px, py, 720.0, 400.0) == 0)
			{
				pe->reststep -= 10;
				count[53] = 1;
			}
		}
	}
	if(lessonnum==3)
	{
		if ((x >= 400 && x < 440 && y >= 480 && y < 520) || Ehitbox(px, py, 400.0, 480.0))//x��y���ж�����һ��>=һ��<=
		{
			map(53, pnt);
			if (count[53] == 0 && Ehitbox(px, py, 400.0, 480.0) == 1)
			{
				requiredbox3--;
				count[53] = 1;
			}
			if (count[53] == 0 && Ehitbox(px, py, 400.0, 480.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[53] = 1;
			}
		}
		if ((x >= 360 && x < 400 && y >= 680 && y < 720) || Ehitbox(px, py, 360.0, 680.0))//x��y���ж�����һ��>=һ��<=
		{
			map(54, pnt);
			if (count[54] == 0 && Ehitbox(px, py, 360.0, 680.0) == 1)
			{
				requiredbox3--;
				count[54] = 1;
			}
			if (count[54] == 0 && Ehitbox(px, py, 360.0, 680.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[54] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 560 && y < 600) || Ehitbox(px, py, 160.0, 560.0))//x��y���ж�����һ��>=һ��<=
		{
			map(55, pnt);
			if (count[55] == 0 && Ehitbox(px, py, 160.0, 560.0) == 1)
			{
				requiredbox3--;
				count[55] = 1;
			}
			if (count[55] == 0 && Ehitbox(px, py, 160.0, 560.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[55] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 440 && y < 480) || Ehitbox(px, py, 560.0, 440.0))//x��y���ж�����һ��>=һ��<=
		{
			map(56, pnt);
			if (count[56] == 0 && Ehitbox(px, py, 560.0, 440.0) == 1)
			{
				requiredbox3--;
				count[56] = 1;
			}
			if (count[56] == 0 && Ehitbox(px, py, 560.0, 440.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[56] = 1;
			}
		}
		if ((x >= 680 && x < 720 && y >= 160 && y < 200) || Ehitbox(px, py, 680.0, 160.0))//x��y���ж�����һ��>=һ��<=
		{
			map(57, pnt);
			if (count[57] == 0 && Ehitbox(px, py, 680.0, 160.0) == 1)
			{
				requiredbox3--;
				count[57] = 1;
			}
			if (count[57] == 0 && Ehitbox(px, py, 680.0, 160.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[57] = 1;
			}
		}
		if ((x >= 200 && x < 240 && y >= 200 && y < 240) || Ehitbox(px, py, 200.0, 200.0))//x��y���ж�����һ��>=һ��<=
		{
			map(58, pnt);
			if (count[58] == 0 && Ehitbox(px, py, 200.0, 200.0) == 1)
			{
				requiredbox3--;
				count[58] = 1;
			}
			if (count[58] == 0 && Ehitbox(px, py, 200.0, 200.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[58] = 1;
			}
		}
		if ((x >= 0 && x < 40 && y >= 200 && y < 240) || Ehitbox(px, py, 0.0, 200.0))//x��y���ж�����һ��>=һ��<=
		{
			map(59, pnt);
			if (count[59] == 0 && Ehitbox(px, py, 0.0, 200.0) == 1)
			{
				requiredbox3--;
				count[59] = 1;
			}
			if (count[59] == 0 && Ehitbox(px, py, 0.0, 200.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[59] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 640 && y < 680) || Ehitbox(px, py, 560.0, 640.0))//x��y���ж�����һ��>=һ��<=
		{
			map(60, pnt);
			if (count[60] == 0 && Ehitbox(px, py, 560.0, 640.0) == 1)
			{
				requiredbox3--;
				count[60] = 1;
			}
			if (count[60] == 0 && Ehitbox(px, py, 560.0, 640.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[60] = 1;
			}
		}
		if ((x >= 640 && x < 680 && y >= 120 && y < 160) || Ehitbox(px, py, 640.0, 120.0))//x��y���ж�����һ��>=һ��<=
		{
			map(61, pnt);
			if (count[61] == 0 && Ehitbox(px, py, 640.0, 120.0) == 1)
			{
				requiredbox3--;
				count[61] = 1;
			}
			if (count[61] == 0 && Ehitbox(px, py, 640.0, 120.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[61] = 1;
			}
		}
		if ((x >= 680 && x < 720 && y >= 680 && y < 720) || Ehitbox(px, py, 680.0, 720.0))//x��y���ж�����һ��>=һ��<=
		{
			map(62, pnt);
			if (count[62] == 0 && Ehitbox(px, py, 680.0, 720.0) == 1)
			{
				requiredbox3--;
				count[62] = 1;
			}
			if (count[62] == 0 && Ehitbox(px, py, 680.0, 720.0) == 0)
			{
				pe->score += 20;
				pe->box++;
				boxlack3--;
				count[62] = 1;
			}
		}
		if ((x >= 280 && x < 320 && y >= 520 && y < 560) || Ehitbox(px, py, 280.0, 520.0))
		{
			map(63, pnt);
			if (count[63] == 0 && Ehitbox(px, py, 280.0, 520.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[63] = 1;
			}
			if (count[63] == 0 && Ehitbox(px, py, 280.0, 520.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[63] = 1;
			}
		}
		if ((x >= 80 && x < 120 && y >= 80 && y < 120) || Ehitbox(px, py, 80.0, 80.0))
		{
			map(64, pnt);
			if (count[64] == 0 && Ehitbox(px, py, 80.0, 80.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[64] = 1;
			}
			if (count[64] == 0 && Ehitbox(px, py, 80.0, 80.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[64] = 1;
			}
		}
		if ((x >= 480 && x < 520 && y >= 480 && y < 520) || Ehitbox(px, py, 480.0, 480.0))
		{
			map(65, pnt);
			if (count[65] == 0 && Ehitbox(px, py, 480.0,480.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[65] = 1;
			}
			if (count[65] == 0 && Ehitbox(px, py, 480.0, 480.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[65] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 480 && y < 520) || Ehitbox(px, py, 160.0, 480.0))
		{
			map(66, pnt);
			if (count[66] == 0 && Ehitbox(px, py, 160.0, 480.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[66] = 1;
			}
			if (count[66] == 0 && Ehitbox(px, py, 160.0, 480.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[66] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 240 && y < 280) || Ehitbox(px, py, 560.0, 240.0))
		{
			map(67, pnt);
			if (count[67] == 0 && Ehitbox(px, py, 560.0, 240.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[67] = 1;
			}
			if (count[67] == 0 && Ehitbox(px, py, 560.0, 240.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[67] = 1;
			}
		}
		if ((x >= 280 && x < 320 && y >= 280 && y < 320) || Ehitbox(px, py, 280.0, 280.0))
		{
			map(68, pnt);
			if (count[68] == 0 && Ehitbox(px, py, 280.0, 280.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[68] = 1;
			}
			if (count[68] == 0 && Ehitbox(px, py, 280.0, 280.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[68] = 1;
			}
		}
		if ((x >= 320 && x < 360 && y >= 160 && y < 200) || Ehitbox(px, py, 320.0, 160.0))
		{
			map(69, pnt);
			if (count[69] == 0 && Ehitbox(px, py, 320.0, 160.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[69] = 1;
			}
			if (count[69] == 0 && Ehitbox(px, py, 320.0, 160.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[69] = 1;
			}
		}
		if ((x >= 720 && x < 760 && y >= 280 && y < 320) || Ehitbox(px, py, 720.0, 280.0))
		{
			map(70, pnt);
			if (count[70] == 0 && Ehitbox(px, py, 720.0, 280.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[70] = 1;
			}
			if (count[70] == 0 && Ehitbox(px, py, 720.0, 280.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[70] = 1;
			}
		}
		if ((x >= 160 && x < 200 && y >= 440 && y < 480) || Ehitbox(px, py, 160.0, 440.0))
		{
			map(71, pnt);
			if (count[71] == 0 && Ehitbox(px, py, 160.0, 440.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[71] = 1;
			}
			if (count[71] == 0 && Ehitbox(px, py, 160.0, 440.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[71] = 1;
			}
		}
		if ((x >= 760 && x < 800 && y >= 600 && y < 640) || Ehitbox(px, py, 760.0, 600.0))
		{
			map(72, pnt);
			if (count[72] == 0 && Ehitbox(px, py, 760.0, 600.0) == 1)//����������жϵ��˳Թ��Ӽ��ٶ�
			{
				pe->enemyspeed += 0.02;
				count[72] = 1;
			}
			if (count[72] == 0 && Ehitbox(px, py, 760.0, 600.0) == 0)//����������ж�ֻ�Թ���һ�β��Ҳ��ǵ��˳ԵĲ��ܼӲ���
			{
				pe->reststep += 5;
				pe->score += 10;
				count[72] = 1;
			}
		}
		if ((x >= 400 && x < 440 && y >= 400 && y < 440) || Ehitbox(px, py, 400.0, 400.0))
		{
			if (Ehitbox(px, py, 400.0, 400.0) == 1)
			{
				map(73, pnt);
			}
			if (count[73] == 0 && Ehitbox(px, py, 400.0, 400.0) == 0 && pe->ifhaveweapon == 0)
			{
				map(73, pnt);
				pe->ifhaveweapon += 1;
				count[73] = 1;
			}
		}
		if ((x >= 40 && x < 80 && y >= 680 && y < 720) || Ehitbox(px, py, 40.0, 680.0))
		{
			map(74, pnt);
			if (count[74] == 0 && Ehitbox(px, py, 40.0, 680.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[74] = 1;
			}
			if (count[74] == 0 && Ehitbox(px, py, 40.0, 680.0) == 0)
			{
				pe->reststep -= 10;
				count[74] = 1;
			}
		}
		if ((x >= 360 && x < 400 && y >= 120 && y < 160) || Ehitbox(px, py, 360.0, 120.0))
		{
			map(75, pnt);
			if (count[75] == 0 && Ehitbox(px, py, 360.0, 120.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[75] = 1;
			}
			if (count[75] == 0 && Ehitbox(px, py, 360.0, 120.0) == 0)
			{
				pe->reststep -= 10;
				count[75] = 1;
			}
		}
		if ((x >= 120 && x < 160 && y >= 440 && y < 480) || Ehitbox(px, py, 120.0, 440.0))
		{
			map(76, pnt);
			if (count[76] == 0 && Ehitbox(px, py, 120.0, 440.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[76] = 1;
			}
			if (count[76] == 0 && Ehitbox(px, py, 120.0, 440.0) == 0)
			{
				pe->reststep -= 10;
				count[76] = 1;
			}
		}
		if ((x >= 560 && x < 600 && y >= 40 && y < 80) || Ehitbox(px, py, 560.0, 40.0))
		{
			map(77, pnt);
			if (count[77] == 0 && Ehitbox(px, py, 560.0, 40.0) == 1)
			{
				pe->enemyspeed -= 0.02;
				count[77] = 1;
			}
			if (count[77] == 0 && Ehitbox(px, py, 560.0, 40.0) == 0)
			{
				pe->reststep -= 10;
				count[77] = 1;
			}
		}
		
	}
	if(lessonnum==1)
	{
		sprintf(lack_of_box, "%d", boxlack1);
		outtextxy(1045, 455, lack_of_box);
	}
	if (lessonnum == 2)
	{
		sprintf(lack_of_box, "%d", boxlack2);
		outtextxy(1045, 455, lack_of_box);
	}
	if (lessonnum == 3)
	{
		sprintf(lack_of_box, "%d", boxlack3);
		outtextxy(1045, 455, lack_of_box);
	}
	sprintf(timenum, "%d", now_time);
	sprintf(score, "%d", pe->score);
	if(pe->ifhaveweapon!=0)
	{
		weapon[0] = 'Y';
		weapon[1] = 'E';
		weapon[2] = 'S';
	}
	sprintf(num, "%d", pe->reststep);//����sprintf������intת�����ַ���
	sprintf(historyscore, "%d", scorenow);
	outtextxy(1010, 375, historyscore);
	outtextxy(1000, 295, usernow);
	outtextxy(945, 135, num);
	outtextxy(1000, 335, score);
	outtextxy(945, 225, timenum);
	outtextxy(1010, 415, weapon);
	
}

void enemy(int ran,double *px,double *py)
{
	static double xe = 0, ye = 600;
	static int count = 0;
	if (lessonnum == 2 && count == 0)
	{
		xe = 0;
		ye = 600;
		count++;
	}
	switch (ran)
	{
	case 0:
		if(ye>=0)
		{
			ye -=pe->enemyspeed;
		}
		transparentimage(xe, ye, &img_enemyS, &img_enemySM);
		break;
	case 1:
		if(ye>=0)
		{
			ye -= pe->enemyspeed;
		}
		transparentimage(xe, ye, &img_enemyS, &img_enemySM);
		break;
	case 2:
		if(ye<=680)
		{
			ye += pe->enemyspeed;
		}
		transparentimage(xe,ye,&img_enemyN, &img_enemyNM);
		break;
	case 3:
		if (ye <= 680)
		{
			ye += pe->enemyspeed;
		}
		transparentimage(xe,ye,&img_enemyN, &img_enemyNM);
		break;
	case 4:
		if(xe<=860)
		{
			xe += pe->enemyspeed;
		}
		transparentimage(xe,ye,&img_enemyR, &img_enemyRM);
		break;
	case 5:
		if (xe <= 860)
		{
			xe += pe->enemyspeed;
		}
		transparentimage(xe, ye, &img_enemyR, &img_enemyRM);
		break;
	case 6:
		if (xe >=0)
		{
			xe -= pe->enemyspeed;
		}
		transparentimage(xe,ye,&img_enemyL, &img_enemyLM);
		break;
	case 7:
		if (xe >= 0)
		{
			xe -= pe->enemyspeed;
		}
		transparentimage(xe,ye,&img_enemyL, &img_enemyLM);
		break;
	case 8:
		xe -= 120;
		break;
	case 9:
		xe += 160;
	case 10:
		xe += 120;
	case 11:
		xe -= 160;
	default:
		transparentimage(xe,ye,&img_enemyL, &img_enemyLM);
		break;
	}
	*px = xe;
	*py = ye;

}

int Ehitbox(double* px, double* py,int ix,int iy)
{
	double x0 = *px, y0 = *py, x1 = *px + 40.0, y1 = *py + 40.0;
	int ix1 = ix + 40, iy1 = iy + 40;
	if ((x1 >= ix && x0 <= ix &&x1<=ix1&& y1 >= iy && y1 <= iy1 && y0 <= iy) || (x1 >= ix && x0 <= ix &&x1<=ix1&& y1 >= iy1 && y0 >= iy && y0 <= iy1) || (x0 <= ix1 && x1 >= ix1&&x0>=ix && y1 >= iy && y1 <= iy1 && y0 <= iy) || (x0 <= ix1 && x1 >= ix1 &&x0>=ix&& y1 >= iy1 && y0 >= iy && y0 <= iy1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void ifenemyhit(double *px,double *py,int x,int y)
{
	static int count = 0;
	if(Ehitbox(px,py,x,y) == 1&&pe->ifhaveweapon!=0)
	{
		if(count==0)
		{
			mciSendString("open ./BGM\\hitbyenemy.mp3 alias BGM1", NULL, 0, NULL);
			mciSendString("play BGM1", NULL, 0, NULL);
			count++;
		}
		else if(count!=0)
		{
			mciSendString("close BGM1", NULL, 0, NULL);
			mciSendString("open ./BGM\\hitbyenemy.mp3 alias BGM1", NULL, 0, NULL);
			mciSendString("play BGM1", NULL, 0, NULL);
		}
		pe->ifhaveweapon--;
		pe->score += 200;
		if(*px-120>=0&&x>*px)
		{
			enemy(8, px, py);
		}
		else
		{
			if(*px-120<=0)
			{
				enemy(9, px, py);
			}
			else
			{
				enemy(10, px, py);
				if(*px+120>=920&&*px>x)
				{
					enemy(11, px, py);
				}
			}
		}
	}
	else if (Ehitbox(px, py, x, y) == 1 && pe->ifhaveweapon == 0)
	{
		h = adduser();
		writefile();
		MessageBox(NULL, "�㱻����ץס�ˣ����� ��Ϸʧ��", "��Ϸʧ��", MB_OK | MB_SETFOREGROUND);
		
		exit(-1);
	}
}

void gamecontrol()//��������Ŀ���
{
	int x = 0, y = 0, ret = 0, ran = 0,xe=0,ye=600;

	double* px = (double*)malloc(sizeof(double));//�������λ�������ָ��
	double* py = (double*)malloc(sizeof(double));
	static int count = 0;

	time_t start_time;//����time_t���ͱ���
	time(&start_time);//��ȡϵͳ����ʱ��
	struct tm start_time_tm;	//tm�ṹָ��
	localtime_s(&start_time_tm, &start_time);//��ȡ��������ʱ��
	int sum_start_time = 3600 * start_time_tm.tm_hour + 60 * start_time_tm.tm_min + start_time_tm.tm_sec;
	int pause_time = 0;//��¼��ͣ��ʱ��
	int* pnt = &pause_time;//ָ��pause_time��ָ�룬����֮���޸�

	mciSendString("open ./BGM\\mapbgm.mp3 alias BGM", 0, 0, 0);//��ͼ�ı�������
	mciSendString("play BGM repeat", 0, 0, 0);

	BeginBatchDraw();
	while(1)
	{
		if(lessonnum==2&&count==0)
		{
			x = 0, y = 0;
			count++;
		}
		if(lessonnum==3&&count==1)
		{
			x = 0, y = 0;
			count++;
		}
		lessonjudge();
		ifwin(pnt);
		cleardevice();
		//checkitemap_step_time(x, y, pe, px, py, sum_start_time, pnt);
		checkitemap_step_time(x, y, px, py, sum_start_time, pnt);
		switch (ret)//���ж�����ķ�λ
		{
		case 0:
			transparentimage(0, 0, &img_BCR, &img_BCRM);//��ʼ��λ��
			enemy(ran,px,py);//�õ�������ƶ�
			break;
		case 1:
			transparentimage(x, y, &img_BCN, &img_BCNM);
			enemy(ran,px,py);
			break;
		case 2:
			transparentimage(x, y, &img_BCS, &img_BCSM);
			enemy(ran,px,py);
			break;
		case 3:
			transparentimage(x, y, &img_BCL, &img_BCLM);
			enemy(ran,px,py);
			break;
		case 4:
			transparentimage(x, y, &img_BCR, &img_BCRM);
			enemy(ran,px,py);
			break;
		}
		FlushBatchDraw();//ֻ����flushbatchdraw������endbatchdraw
		ifenemyhit(px, py, x, y);
		if (_kbhit())//�жϼ�������
		{
			char key = _getch();//����������������һֱ�ȣ�
			switch (key)
			{
			case 72:
			case 'w':
			case 'W':
				if(y<=0)//�жϱ߽�
				{
					break;
				}
				ret = 1;
				if(lessonnum==2)
				{
					pe->reststep-=2;
				}
				if(lessonnum==1||lessonnum==3)
				{
					pe->reststep--;
				}
				y -= 40;
				ran = rand() % 10 - 2;//�����õ�������ƶ�
				//printf("��\n");//�ⶼ���������Ե�print����
				break;
			case 80:
			case 's':
			case 'S':
				if (y >= 680)
				{
					break;
				}
				ret = 2;
				if (lessonnum == 2)
				{
					pe->reststep -= 2;
				}
				if (lessonnum == 1 || lessonnum == 3)
				{
					pe->reststep--;
				}
				y += 40;
				ran = rand() % 10 - 2;
				//printf("��\n");
				break;
			case 75:
			case 'a':
			case 'A':
				if(x<=0)
				{
					break;
				}
				ret = 3;
				if (lessonnum == 2)
				{
					pe->reststep -= 2;
				}
				if (lessonnum == 1 || lessonnum == 3)
				{
					pe->reststep--;
				}
				x -= 40;
				ran = rand() % 10 - 2;
				//printf("��\n");
				break;
			case 77:
			case 'd':
			case 'D':
				if(x>=860)
				{
					break;
				}
				ret = 4;
				if (lessonnum == 2)
				{
					pe->reststep -= 2;
				}
				if (lessonnum == 1 || lessonnum == 3)
				{
					pe->reststep--;
				}
				x += 40;
				ran = rand() % 10 - 2;
				//printf("��\n");
				break;
			}
		}
		
	}
}

void map(int check,int *pnt)//���Ƶ�ͼ�ĺ���
{
	static int isexist[1000] = { '\0'};//����static֮���ֻ��ʼ��һ����
	isexist[check] = 1;
	cleardevice();
	//putimage(0, 0, &img_grass);

	if (lessonnum == 1) 
	{
		putimage(0, 0, &img_grass);
		transparentimage(80, 0, &img_chicken, &img_chickenM);
		if (isexist[0] == 0)
		{
			putimage(120, 120, &img_box);
		}
		if (isexist[1] == 0)
		{
			transparentimage(200, 200, &img_bush, &img_bushM);
		}
		if (isexist[2] == 0)
		{
			transparentimage(560, 560, &img_tree, &img_treeM);
		}
		if (isexist[3] == 0)
		{
			transparentimage(280, 80, &img_knife, &img_knifeM);
		}
		if (isexist[4] == 0)
		{
			transparentimage(160, 280, &img_mushroom, &img_mushroomM);
		}
		if (isexist[5] == 0)
		{
			putimage(0, 80, &img_box);
		}
		if(isexist[6]==0)
		{
			transparentimage(560, 240, &img_knife, &img_knifeM);
		}
		if (isexist[7] == 0)
		{
			transparentimage(640, 560, &img_knife, &img_knifeM);
		}
		if(isexist[8]==0)
		{
			putimage(400, 480, &img_box);
		}
		if (isexist[9] == 0)
		{
			putimage(360, 680, &img_box);
		}
		if (isexist[10] == 0)
		{
			putimage(160, 560, &img_box);
		}
		if (isexist[11] == 0)
		{
			putimage(720, 160, &img_box);
		}
		if (isexist[12] == 0)
		{
			putimage(760, 320, &img_box);
		}
		if (isexist[13] == 0)
		{
			putimage(640, 640, &img_box);
		}
		if (isexist[14] == 0)
		{
			transparentimage(280, 520, &img_bush, &img_bushM);
		}
		if (isexist[15] == 0)
		{
			transparentimage(440, 480, &img_bush, &img_bushM);
		}
		if (isexist[16] == 0)
		{
			transparentimage(400, 280, &img_bush, &img_bushM);
		}
		if (isexist[17] == 0)
		{
			transparentimage(0, 480, &img_bush, &img_bushM);
		}
		if (isexist[18] == 0)
		{
			transparentimage(860, 40, &img_bush, &img_bushM);
		}
		if (isexist[19] == 0)
		{
			transparentimage(740,0, &img_tree, &img_treeM);
		}
		if (isexist[20] == 0)
		{
			transparentimage(600, 320, &img_tree, &img_treeM);
		}
		if (isexist[21] == 0)
		{
			transparentimage(320, 200, &img_tree, &img_treeM);
		}
		if (isexist[22] == 0)
		{
			transparentimage(40, 680, &img_mushroom, &img_mushroomM);
		}
		if (isexist[23] == 0)
		{
			transparentimage(360, 120, &img_mushroom, &img_mushroomM);
		}
		if (isexist[24] == 0)
		{
			putimage(440, 120, &img_box);
		}
	}
	if(lessonnum==2)
	{
		putimage(0, 0, &img_snow);
		transparentimage(80, 0, &img_chicken, &img_chickenM);
		if (isexist[25] == 0)
		{
			putimage(400, 120, &img_box);
		}
		if (isexist[26] == 0)
		{
			putimage(120, 640, &img_box);
		}
		if (isexist[27] == 0)
		{
			putimage(0, 440, &img_box);
		}
		if (isexist[28] == 0)
		{
			putimage(560, 440, &img_box);
		}
		if (isexist[29] == 0)
		{
			putimage(680, 160, &img_box);
		}
		if (isexist[30] == 0)
		{
			putimage(200, 200, &img_box);
		}
		if (isexist[31] == 0)
		{
			putimage(360, 280, &img_box);
		}
		if (isexist[32] == 0)
		{
			putimage(760, 600, &img_box);
		}
		if (isexist[33] == 0)
		{
			putimage(160, 520, &img_box);
		}
		if (isexist[34] == 0)
		{
			putimage(800, 120, &img_box);
		}
		if (isexist[35] == 0)
		{
			putimage(120, 120, &img_box);
		}
		if (isexist[36] == 0)
		{
			transparentimage(160, 280, &img_bush, &img_bushM);
		}
		if (isexist[37] == 0)
		{
			transparentimage(280, 80, &img_bush, &img_bushM);
		}
		if (isexist[38] == 0)
		{
			transparentimage(280,320, &img_bush, &img_bushM);
		}
		if (isexist[39] == 0)
		{
			transparentimage(440, 480, &img_bush, &img_bushM);
		}
		if (isexist[40] == 0)
		{
			transparentimage(400, 520, &img_bush, &img_bushM);
		}
		if (isexist[41] == 0)
		{
			transparentimage(600, 320, &img_tree, &img_treeM);
		}
		if (isexist[42] == 0)
		{
			transparentimage(0, 80, &img_tree, &img_treeM);
		}
		if (isexist[43] == 0)
		{
			transparentimage(320, 120, &img_tree, &img_treeM);
		}
		if (isexist[44] == 0)
		{
			transparentimage(160, 160, &img_tree, &img_treeM);
		}
		if (isexist[45] == 0)
		{
			transparentimage(560, 400, &img_tree, &img_treeM);
		}
		if (isexist[46] == 0)
		{
			transparentimage(760, 520, &img_tree, &img_treeM);
		}
		if (isexist[47] == 0)
		{
			transparentimage(560, 640, &img_tree, &img_treeM);
		}
		if (isexist[48] == 0)
		{
			transparentimage(640, 40, &img_knife, &img_knifeM);
		}
		if (isexist[49] == 0)
		{
			transparentimage(400, 400, &img_knife, &img_knifeM);
		}
		if (isexist[50] == 0)
		{
			transparentimage(40, 680, &img_mushroom, &img_mushroomM);
		}
		if (isexist[51] == 0)
		{
			transparentimage(0, 480, &img_mushroom, &img_mushroomM);
		}
		if (isexist[52] == 0)
		{
			transparentimage(520, 120, &img_mushroom, &img_mushroomM);
		}
		if (isexist[53] == 0)
		{
			transparentimage(720, 400, &img_mushroom, &img_mushroomM);
		}

	}
	if (lessonnum == 3)
	{
		putimage(0, 0, &img_sand);
		transparentimage(80, 0, &img_chicken, &img_chickenM);
		if (isexist[53] == 0)
		{
			putimage(400, 480, &img_box);
		}
		if (isexist[54] == 0)
		{
			putimage(360, 680, &img_box);
		}
		if (isexist[55] == 0)
		{
			putimage(160, 560, &img_box);
		}
		if (isexist[56] == 0)
		{
			putimage(560, 440, &img_box);
		}
		if (isexist[57] == 0)
		{
			putimage(680, 160, &img_box);
		}
		if (isexist[58] == 0)
		{
			putimage(200, 200, &img_box);
		}
		if (isexist[59] == 0)
		{
			putimage(0, 200, &img_box);
		}
		if (isexist[60] == 0)
		{
			putimage(560, 640, &img_box);
		}
		if (isexist[61] == 0)
		{
			putimage(640, 120, &img_box);
		}
		if (isexist[62] == 0)
		{
			putimage(680, 680, &img_box);
		}
		if (isexist[63] == 0)
		{
			transparentimage(280, 520, &img_bush, &img_bushM);
		}
		if (isexist[64] == 0)
		{
			transparentimage(80, 80, &img_bush, &img_bushM);
		}
		if (isexist[65] == 0)
		{
			transparentimage(480, 480, &img_bush, &img_bushM);
		}
		if (isexist[66] == 0)
		{
			transparentimage(160, 480, &img_bush, &img_bushM);
		}
		if (isexist[67] == 0)
		{
			transparentimage(560, 240, &img_bush, &img_bushM);
		}
		if (isexist[68] == 0)
		{
			transparentimage(280, 280, &img_tree, &img_treeM);
		}
		if (isexist[69] == 0)
		{
			transparentimage(320, 160, &img_tree, &img_treeM);
		}
		if (isexist[70] == 0)
		{
			transparentimage(720, 280, &img_tree, &img_treeM);
		}
		if (isexist[71] == 0)
		{
			transparentimage(160, 440, &img_tree, &img_treeM);
		}
		if (isexist[72] == 0)
		{
			transparentimage(760, 600, &img_tree, &img_treeM);
		}
		if (isexist[73] == 0)
		{
			transparentimage(400, 400, &img_knife, &img_knifeM);
		}
		if (isexist[74] == 0)
		{
			transparentimage(40, 680, &img_mushroom, &img_mushroomM);
		}
		if (isexist[75] == 0)
		{
			transparentimage(360, 120, &img_mushroom, &img_mushroomM);
		}
		if (isexist[76] == 0)
		{
			transparentimage(120, 440, &img_mushroom, &img_mushroomM);
		}
		if (isexist[77] == 0)
		{
			transparentimage(560, 40, &img_mushroom, &img_mushroomM);
		}
	}
	maplist(pnt);
}

void titlemousecheck()//�йس�ʼ�˵���һЩ����
{
	ExMessage msg;
	mciSendString("open ./BGM\\menubgm.mp3 alias BGM", 0, 0, 0);//�������ֲ���
	mciSendString("play BGM repeat", 0, 0, 0);
	while(1)
	{
		if(peekmessage(&msg,EX_MOUSE))
		{
			switch(msg.message)
			{
			case WM_LBUTTONDOWN:
				if(msg.x>=450&&msg.x<=450+150&&msg.y>=380&&msg.y<=380+75)//������Ϸ��ť��������
				{
					h = adduser();
					writefile(); 
					MessageBox(NULL, "��Ϸ�����ˣ���л��������", "��Ϸ����", MB_OK | MB_SETFOREGROUND);
					mciSendString("close BGM",0,0,0);
					exit(-1);//��������
				}
				if(msg.x>=450&&msg.x<=450+150&&msg.y>=480&&msg.y<=480+75)
				{
					MessageBox(NULL, "��ӭ������Ϸ�ĵ�����������\n�ڱ�����Ϸ��㽫����һ������ĵ��Ŀ�ѧ�ң����ڱ�����׷��������Ҫ���ռ����Լ������ڻĵ��Ŀ�ѧ���ϲ�����\n\n��Ϸ�Ĳ���Ϊ������԰�ס�����е�WASD���������ҷ�������ƶ���ͬʱ���Ե���Ҳ��嵥�ϵİ�ť����һϵ�в���\n\n��Ϸ�������µ��ߣ�\n���ӣ�����������Ŀ�ѧ���ϣ���Ҫ�ռ�����ͨ��\nֲ��������ӻ�������ʣ�ಽ����������Ϊ��Ĳ���������Ҳ����Σ��Ӵ\nذ����������������������������һ�ε��˵Ĺ���\n\nע�⣺����Ҳ��ʰȡ��ͼ�ϵ�����ʹ���޷�ͨ�أ�ͬʱҲ��ʰȡ������������������Ի�õ�����", "��Ϸ���", MB_OK | MB_SETFOREGROUND);
				}
				if(msg.x>=450&&msg.x<=450+150&&msg.y>=280&&msg.y<=280+75)
				{
					mciSendString("close BGM", 0, 0, 0);
					map(90,NULL);
					gamecontrol();
					break;
				}
				if(msg.x>=450&&msg.x<=450+150&&msg.y>=580&&msg.y<=580+75)
				{
					int i = 1;
					P_E* p = h,*q=NULL;
					char filemessage[1000] = {'\0'};
					char filescore[100];
					char inum[10];
					for(p=h;p!=NULL;p=p->next)
					{
						sprintf(inum, "%d", i);
						sprintf(filescore, "%d", p->score);
						strcat(filemessage, inum);
						strcat(filemessage, "   ");
						strcat(filemessage, p->name);
						strcat(filemessage, "   ");
						strcat(filemessage, filescore);
						strcat(filemessage, "\n");
						i++;
					}
					MessageBox(NULL,filemessage , "���а�", MB_OK | MB_SETFOREGROUND);
				}
			}
		}
	}
}

int main()
{
	h=creatfilelist();
	login(h);

	time_t now = time(NULL);

	initgraph(1080,720,EX_SHOWCONSOLE);
	creatmenu();
	titlemousecheck();
	getchar();
	closegraph();
	return 0;
}