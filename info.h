#ifndef INFO_H
#define INFO_H

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>

//商品存储最大值
//--------------------------------------------------------------------
#define MAX 100 

//--------------------------------------------------
//各变量的最大长度
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
//商品链表节点定义
//-------------------------------------------------

typedef struct node{
    GoodInfo data;
    struct node *next;
}Goodlist;

//-------------------------------------------------
//查找文件是否存在 不存在则新建一个
//-------------------------------------------------

bool check_nullfile(void);

//-------------------------------------------------
//读入一个商品信息
//-------------------------------------------------

void readline(FILE *p,Goodlist *now);

//-------------------------------------------------
//读入文件中商品信息到链表中并切换到stdin流
//-------------------------------------------------

void info_init(Goodlist **L , int *goodnumber);

#endif
