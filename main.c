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
    
    //�����ļ�����Ʒ��Ϣ�������в��л���stdin��
    info_init(&list, &goodnumber);

    //��ʾ��Ϣ
    printf("��Ʒ�����ļ��ѽ�������%d����Ʒ��¼\n", goodnumber);
    printf("������Ʒ����ϵͳ\n");

    //�û�����ָ��
    for(;;){
        chooselist(goodnumber);
        printf("��������ѡ��");
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
                        printf("�Ѵﵽ��Ʒ�洢�������ޣ��޷������洢\n");
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
