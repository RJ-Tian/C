#include"info.h"
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>
//--------------------------------------------------------------------
//读入一个商品信息
//--------------------------------------------------------------------
void readline(FILE *p,Goodlist *now){
    fscanf(p," %s",&now->data.good_id);
    fscanf(p," %s",&now->data.good_name);
    fscanf(p," %d",&now->data.good_price);
    fscanf(p," %s",&now->data.good_discount);
    fscanf(p," %d",&now->data.good_amount);
    fscanf(p," %d\n",&now->data.good_remain);
}

//--------------------------------------------------------------------
//查找文件是否存在 不存在则新建一个
//--------------------------------------------------------------------
bool check_nullfile(void){
    FILE *fp = fopen("goodinfo.txt", "r");
    //file not exist
    if (!fp) {
        printf("该目标文件不存在，将为您新建一个.\n");
        FILE *fp = fopen("goodinfo.txt", "w");
        fclose(fp);
        return false;
    }
        //file already exist
    else {
        int temp;
        //res for try to read file if file null feof() can't determine whether file is null or not
        int res = fscanf(fp, "%d", &temp);
        fclose(fp);
        if (res <= 0)
            return false;
        else
            return true;
    }
}

//--------------------------------------------------------------------
//读入文件中商品信息到链表中并切换到stdin流
//--------------------------------------------------------------------
void info_init(Goodlist **L, int *goodnumber){
    FILE *fp;
    Goodlist *first = NULL;
    Goodlist *new_good = NULL;

    if(!check_nullfile()){
        return;
    }else{
        fp = (FILE*)fopen("goodinfo.txt", "r");
        for(;!feof(fp);(*goodnumber)++){
            new_good = (Goodlist*)malloc(sizeof(struct node));
            if(new_good == NULL){
                printf("Error: malloc failed \n");
                return;
            }else{
                readline(fp,new_good);
                new_good->next = first;
                first = new_good;
            }
        }
        fclose(fp);
        *L = first;
    }
}
