#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>
#include"function.h"
#include"info.h"

//格式输出
//--------------------------------------------------------------------
//格式输出1,2
//--------------------------------------------------------------------
void printformat1(void){
    int i;
    for(i=0;i<=40;i++){
        printf("*");
    }
    printf("\n");
}

void printformat2(void){
    int i;
    for(i=0;i<=75;i++){
        printf("+");
    }
    printf("\n");
}

//--------------------------------------------------------------------
//用户选择菜单
//-------------------------------------------------------------------- 
void chooselist(int goodnumber){
    if(goodnumber == 0){
        printformat1();
        printf("3.插入一个商品的信息：\n");
        printf("其他，不存盘并退出系统：\n");
        printformat1();
    }else{
        printformat1();
        printf("1.显示所有商品的信息：\n");
        printf("2.修改一个商品的信息：\n");
        printf("3.插入一个商品的信息：\n");
        printf("4.删除一个商品的信息：\n");
        printf("5.查找一个商品的信息：\n");
        printf("6.商品存盘并退出系统：\n");
        printf("7.对商品价格进行排序：\n");
        printf("8.(慎用)删除所有内容：\n");
        printf("其他，不存盘并退出系统：\n");
        printformat1();
    }
}



//链表操作
//--------------------------------------------------------------------
//把链表内的商品信息存入文件，释放malloc的空间
//--------------------------------------------------------------------
void info_flush(Goodlist **L, int *goodnumber){
    FILE *fp= fopen("goodinfo.txt","w");
    struct node *previous = NULL,*now = *L;

    if(*goodnumber == 0){
        fclose(fp);
        return;
    }

    if(fp == NULL){
        printf("文件打开失败");
        exit(EXIT_FAILURE);
    }else if((*goodnumber) == 0){
        return;
    }else{ 
        bubble_sort(L,goodnumber);
        for(;now != NULL;){
            fprintf(fp,"%s",now->data.good_id);
            fprintf(fp,"\t%s",now->data.good_name);
            fprintf(fp,"\t%d",now->data.good_price);
            fprintf(fp,"\t%s",now->data.good_discount);
            fprintf(fp,"\t%d",now->data.good_amount);
            fprintf(fp,"\t%d\n",now->data.good_remain);
            previous = now;
            free(previous);
            previous = NULL;
            now = now->next;
        }
    }
    fclose(fp);
}

//--------------------------------------------------------------------
//删除所有链表信息
//--------------------------------------------------------------------
void deleteAll(Goodlist **L, int *goodnumber){
    struct node *now = *L ,*previous;
    
    while(now != NULL){
        previous = now;
        free(previous);
        previous = NULL;
        now = now->next;
    }
    *L = NULL;
    (*goodnumber) = 0;
}

//--------------------------------------------------------------------
//输出所有链表信息
//--------------------------------------------------------------------
void outputall(Goodlist **L, int *goodnumber){
    struct node *show = *L;
    printf("当前有%d个商品\n\n",*goodnumber);
    if((*goodnumber) == 0){
        return;
    }else{
        for(;show!=NULL;show = show->next){
            info_output(show);
        }
    }
}

//--------------------------------------------------------------------
//输出一个商品信息
//--------------------------------------------------------------------
void info_output(Goodlist *L){
    printformat2();
    printf("ID：%s",L->data.good_id);
    printf(" 名称：%s",L->data.good_name);
    printf("\t价格：%d",L->data.good_price);
    printf("\t折扣：%s",L->data.good_discount);
    printf("\t数量：%d",L->data.good_amount);
    printf(" 剩余：%d\n",L->data.good_remain);
    printformat2();
    printf("\n");
}

//--------------------------------------------------------------------
//修改一个商品的信息
//--------------------------------------------------------------------
void info_change(Goodlist **L, int *goodnumber){
    struct node *now = *L,*refer = *L;
    char id[MAX_ID_LEN];
    int i = 0;
    printf("输入需要修改的商品ID（-1退出查找）：");
    scanf("%s",&id);

    if(strcmp(id,"-1") == 0){
        return;
    }
    fflush(stdin);

    for(;now != NULL;now = now->next){
        if(strcmp(id,now->data.good_id) == 0){
            i = 1;
            break;
        }
    }

    if(i){
        info_output(now);
        printf("输入新的商品信息\n");
        printf("商品ID："); 
        scanf("%s",&id);
            for(;refer != NULL;refer = refer->next){
                if(strcmp(id,refer->data.good_id) == 0){
                    printf("该商品ID已存在\n");
                    return;
                }
            }
            strcpy(now->data.good_id,id);
        printf("商品名称：");
        scanf("%s",&now->data.good_name);
        printf("商品价格：");
        scanf("%d",&now->data.good_price);
        printf("商品折扣：");
        scanf("%s",&now->data.good_discount);
        printf("商品数量：");
        scanf("%d",&now->data.good_amount);
        printf("商品剩余：");
        scanf("%d",&now->data.good_remain);
        printf("修改商品信息成功，修改后的商品为：\n");
        info_output(now);
    }else{
        printf("商品不存在\n");
    }

}

//--------------------------------------------------------------------
//删除一个商品信息
//--------------------------------------------------------------------

void info_delete(Goodlist **L, int *goodnumber){
    Goodlist *previous = NULL,*now = *L;
    bool i = false; 
    char id[20],choose;

    if(*goodnumber == 0){
        return;
    } 
    

    printf("输入需要删除的商品ID（-1退出删除）：");
    scanf("%s",id);
    fflush(stdin);

    if(strcmp(id,"-1") == 0){
        return;
    }

    for(;now != NULL;){
        if(strcmp(id,now->data.good_id) == 0){
            i = true;
            break;
        }            
        previous = now;
        now = now->next;
    }


    if(i){         
        info_output(now);
        printf("是否删除该商品（Y/N）：");
        scanf("%c",&choose);
        fflush(stdin);
        if(choose == 'y'||choose == 'Y'){
            if(now == *L){
                *L = now->next;
                free(now);
                (*goodnumber)--;
                printf("Tips:删除ID为%s的商品成功\n",id);
                printf("Tips:当前剩余商品%d个\n",(*goodnumber));
            }else{ 
                previous->next = now->next;
                free(now);
                (*goodnumber)--;
                printf("Tips:删除ID为%s的商品成功\n",id);
                printf("Tips:当前剩余商品%d个\n",(*goodnumber));
            }
        }else{
            return;
        }
    }else{
        printf("没有该商品\n");            
    }

}

//--------------------------------------------------------------------
//查找一个商品信息并输出
//--------------------------------------------------------------------
void info_search(Goodlist **L, int *goodnumber){
    int i = 0; 
    char id[MAX_ID_LEN];
    Goodlist *now = *L;

    printf("输入需要查找的商品ID（-1退出查找）：");
    scanf("%s",id);
    fflush(stdin);
    if(strcmp(id,"-1") == 0){
        return;
    }

    for(;now != NULL;now = now->next){
        if(strcmp(id,now->data.good_id) == 0){
            i = 1;
            break;
        }
    }
    fflush(stdin);

    if(i){
       info_output(now);
    }else{
        printf("商品不存在\n");
    }

    
}


//--------------------------------------------------------------------
//插入一个商品到list
//--------------------------------------------------------------------
void info_insert(Goodlist **L, int *goodnumber){
    int choose,i;
    struct node *new_good,*previous = NULL,*now = *L,*refer = *L;
    new_good = (Goodlist *)malloc(sizeof(Goodlist));

    if(new_good == NULL){
        printf("Error: malloc failed \n");
        return;
    }else{
        printf("输入你要插入的商品信息\n");
        printf("商品ID：");
        scanf("%s",&new_good->data.good_id);
            for(;refer != NULL;refer = refer->next){
                if(strcmp(new_good->data.good_id,refer->data.good_id) == 0){
                    printf("该商品ID已存在\n");
                    free(new_good);
                    return;
                }
            }
        printf("商品名称：");
        scanf("%s",&new_good->data.good_name);
        printf("商品价格：");
        scanf("%d",&new_good->data.good_price);
        printf("商品折扣：");
        scanf("%s",&new_good->data.good_discount);
        printf("商品数量：");
        scanf("%d",&new_good->data.good_amount);
        printf("商品剩余：");
        scanf("%d",&new_good->data.good_remain);
        printf("输入数字表明你要插入的商品位置：0.商品列表尾部 1.商品列表头部 i.商品列表中间第i号位置 ");
        fflush(stdin);

        //选择插入位置
        while(1){
            scanf("%d",&choose);
            fflush(stdin);
            if((*goodnumber == 0) && (choose == 0 || choose == 1)){
                new_good->next = now;
                (*L) = new_good;
                (*goodnumber)++;
                break;
            }else if((*goodnumber == 0) && choose != 1 && choose != 0){
                printf("位置输入无效，请重新输入：");
                continue;
            }

            if(choose == 0){ 
                while(now->next != NULL){
                    now = now->next;
                }
                now->next = new_good;
                new_good->next = NULL;
                (*goodnumber)++;
                break;
            }else if(choose == 1){
                new_good->next = now;
                (*L) = new_good;
                (*goodnumber)++;
                break;
            }else{ 
                if(choose < 0 || choose > *goodnumber){
                    printf("位置输入无效，请重新输入：");
                    continue;
                }else{
                    for(i=1;now->next != NULL && i != choose;i++){
                        previous = now;
                        now = now->next;
                    }
                    previous->next = new_good;
                    new_good->next = now;
                    (*goodnumber)++;
                    break;
                }
            }
        }
    }
}

//--------------------------------------------------------------------
//冒泡排序 传指针暂时不能实现 传值
//--------------------------------------------------------------------
/*
void bubble_sort(Goodlist **L, int *goodnumber){
    struct node *head = NULL,*end = NULL,*previous = NULL;
    head = *L; previous->next = head;
    if(*goodnumber == 0||*goodnumber == 1){
        return;
    }else if(*goodnumber == 2){
        previous = head; 
        head = head->next;
        head->next = previous;
        previous->next =NULL;
    }
    while(head != end){
        while(head->next != end){
            if(head->data.good_price > head->next->data.good_price){
                previous->next = head->next;
                head->next = head->next->next;
                previous->next->next = head; 
                //
            }
                previous = head;
                head = head->next;
        }
        end = head;
        head = *L;
        previous = NULL;
        previous->next = head;
    }
    outputall(L,goodnumber);
}
*/
void bubble_sort(Goodlist **L, int *goodnumber){
    Goodlist *previous = *L,*head = (*L)->next,*end = NULL;
    Goodlist *temp = (Goodlist*)malloc(sizeof(Goodlist));

    if((*goodnumber) == 0 || (*goodnumber) == 1){
        free(temp);
        return;
    }else{
        while(head != end){
            while(head != end){
                if(previous->data.good_price > head->data.good_price){
                    temp->data = head->data;
                    head->data = previous->data;
                    previous->data = temp->data;
                }
                    previous = head;
                    head = head->next;
            }
            end = previous;
            previous = *L;
            head = (*L)->next;
        }
        free(temp);
    }
    outputall(L,goodnumber);
}
