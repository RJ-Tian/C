#ifndef INFO_H
#define INFO_H

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>

//��Ʒ�洢���ֵ
//--------------------------------------------------------------------
#define MAX 100 

//--------------------------------------------------
//����������󳤶�
//--------------------------------------------------
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 10
#define MAX_DISCOUNT_LEN 30


typedef struct {
    char good_id[MAX_ID_LEN];
    char good_name[MAX_NAME_LEN];
    int  good_price;
    char good_discount[MAX_DISCOUNT_LEN];
    int  good_amount;
    int  good_remain;
}GoodInfo;

//-------------------------------------------------
//��Ʒ����ڵ㶨��
//-------------------------------------------------

typedef struct node{
    GoodInfo data;
    struct node *next;
}Goodlist;

//-------------------------------------------------
//�����ļ��Ƿ���� ���������½�һ��
//-------------------------------------------------

bool check_nullfile(void);

//-------------------------------------------------
//����һ����Ʒ��Ϣ
//-------------------------------------------------

void readline(FILE *p,Goodlist *now);

//-------------------------------------------------
//�����ļ�����Ʒ��Ϣ�������в��л���stdin��
//-------------------------------------------------

void info_init(Goodlist **L , int *goodnumber);

#endif
