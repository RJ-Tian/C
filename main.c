#include"function.h"
#include"info.h"
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>



int main(int argc, char const *argv[]){
    int goodnumber = 0;
    Goodlist *list = NULL;
    
    //读入文件中商品信息到链表中并切换到stdin流
    info_init(&list, &goodnumber);

    //提示信息
    printf("商品链表文件已建立，有%d个商品记录\n", goodnumber);
    printf("超市商品管理系统\n");

    //用户输入指令
    for(;;){
        chooselist(goodnumber);
        printf("输入您的选择：");
        char i;
        scanf(" %c",&i);
        fflush(stdin);
        if(goodnumber == 0){
            switch(i){
                case '3': info_insert(&list, &goodnumber); break;
                default: return 0;
            }
        }else{ 
            switch(i){
                case '1': outputall(&list, &goodnumber); break;
                case '2': info_change(&list, &goodnumber); break;
                case '3':
                    if(goodnumber == MAX){
                        printf("已达到商品存储数量上限，无法继续存储\n");
                        break;
                    }else{ 
                        info_insert(&list, &goodnumber); break;
                    }
                case '4': info_delete(&list, &goodnumber); break;
                case '5': info_search(&list, &goodnumber); break;
                case '6': info_flush(&list, &goodnumber); return 0;
                case '7': bubble_sort(&list, &goodnumber); break;
                case '8': deleteAll(&list, &goodnumber); break;
                default: return 0;
            }
        }
    }

    
}
