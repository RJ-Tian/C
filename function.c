#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>
#include"function.h"
#include"info.h"

//��ʽ���
//--------------------------------------------------------------------
//��ʽ���1,2
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
//�û�ѡ��˵�
//-------------------------------------------------------------------- 
void chooselist(int goodnumber){
    if(goodnumber == 0){
        printformat1();
        printf("3.����һ����Ʒ����Ϣ��\n");
        printf("�����������̲��˳�ϵͳ��\n");
        printformat1();
    }else{
        printformat1();
        printf("1.��ʾ������Ʒ����Ϣ��\n");
        printf("2.�޸�һ����Ʒ����Ϣ��\n");
        printf("3.����һ����Ʒ����Ϣ��\n");
        printf("4.ɾ��һ����Ʒ����Ϣ��\n");
        printf("5.����һ����Ʒ����Ϣ��\n");
        printf("6.��Ʒ���̲��˳�ϵͳ��\n");
        printf("7.����Ʒ�۸��������\n");
        printf("8.(����)ɾ���������ݣ�\n");
        printf("�����������̲��˳�ϵͳ��\n");
        printformat1();
    }
}



//�������
//--------------------------------------------------------------------
//�������ڵ���Ʒ��Ϣ�����ļ����ͷ�malloc�Ŀռ�
//--------------------------------------------------------------------
void info_flush(Goodlist **L, int *goodnumber){
    FILE *fp= fopen("goodinfo.txt","w");
    struct node *previous = NULL,*now = *L;

    if(*goodnumber == 0){
        fclose(fp);
        return;
    }

    if(fp == NULL){
        printf("�ļ���ʧ��");
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
//ɾ������������Ϣ
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
//�������������Ϣ
//--------------------------------------------------------------------
void outputall(Goodlist **L, int *goodnumber){
    struct node *show = *L;
    printf("��ǰ��%d����Ʒ\n\n",*goodnumber);
    if((*goodnumber) == 0){
        return;
    }else{
        for(;show!=NULL;show = show->next){
            info_output(show);
        }
    }
}

//--------------------------------------------------------------------
//���һ����Ʒ��Ϣ
//--------------------------------------------------------------------
void info_output(Goodlist *L){
    printformat2();
    printf("ID��%s",L->data.good_id);
    printf(" ���ƣ�%s",L->data.good_name);
    printf("\t�۸�%d",L->data.good_price);
    printf("\t�ۿۣ�%s",L->data.good_discount);
    printf("\t������%d",L->data.good_amount);
    printf(" ʣ�ࣺ%d\n",L->data.good_remain);
    printformat2();
    printf("\n");
}

//--------------------------------------------------------------------
//�޸�һ����Ʒ����Ϣ
//--------------------------------------------------------------------
void info_change(Goodlist **L, int *goodnumber){
    struct node *now = *L,*refer = *L;
    char id[MAX_ID_LEN];
    int i = 0;
    printf("������Ҫ�޸ĵ���ƷID��-1�˳����ң���");
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
        printf("�����µ���Ʒ��Ϣ\n");
        printf("��ƷID��"); 
        scanf("%s",&id);
            for(;refer != NULL;refer = refer->next){
                if(strcmp(id,refer->data.good_id) == 0){
                    printf("����ƷID�Ѵ���\n");
                    return;
                }
            }
            strcpy(now->data.good_id,id);
        printf("��Ʒ���ƣ�");
        scanf("%s",&now->data.good_name);
        printf("��Ʒ�۸�");
        scanf("%d",&now->data.good_price);
        printf("��Ʒ�ۿۣ�");
        scanf("%s",&now->data.good_discount);
        printf("��Ʒ������");
        scanf("%d",&now->data.good_amount);
        printf("��Ʒʣ�ࣺ");
        scanf("%d",&now->data.good_remain);
        printf("�޸���Ʒ��Ϣ�ɹ����޸ĺ����ƷΪ��\n");
        info_output(now);
    }else{
        printf("��Ʒ������\n");
    }

}

//--------------------------------------------------------------------
//ɾ��һ����Ʒ��Ϣ
//--------------------------------------------------------------------

void info_delete(Goodlist **L, int *goodnumber){
    Goodlist *previous = NULL,*now = *L;
    bool i = false; 
    char id[20],choose;

    if(*goodnumber == 0){
        return;
    } 
    

    printf("������Ҫɾ������ƷID��-1�˳�ɾ������");
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
        printf("�Ƿ�ɾ������Ʒ��Y/N����");
        scanf("%c",&choose);
        fflush(stdin);
        if(choose == 'y'||choose == 'Y'){
            if(now == *L){
                *L = now->next;
                free(now);
                (*goodnumber)--;
                printf("Tips:ɾ��IDΪ%s����Ʒ�ɹ�\n",id);
                printf("Tips:��ǰʣ����Ʒ%d��\n",(*goodnumber));
            }else{ 
                previous->next = now->next;
                free(now);
                (*goodnumber)--;
                printf("Tips:ɾ��IDΪ%s����Ʒ�ɹ�\n",id);
                printf("Tips:��ǰʣ����Ʒ%d��\n",(*goodnumber));
            }
        }else{
            return;
        }
    }else{
        printf("û�и���Ʒ\n");            
    }

}

//--------------------------------------------------------------------
//����һ����Ʒ��Ϣ�����
//--------------------------------------------------------------------
void info_search(Goodlist **L, int *goodnumber){
    int i = 0; 
    char id[MAX_ID_LEN];
    Goodlist *now = *L;

    printf("������Ҫ���ҵ���ƷID��-1�˳����ң���");
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
        printf("��Ʒ������\n");
    }

    
}


//--------------------------------------------------------------------
//����һ����Ʒ��list
//--------------------------------------------------------------------
void info_insert(Goodlist **L, int *goodnumber){
    int choose,i;
    struct node *new_good,*previous = NULL,*now = *L,*refer = *L;
    new_good = (Goodlist *)malloc(sizeof(Goodlist));

    if(new_good == NULL){
        printf("Error: malloc failed \n");
        return;
    }else{
        printf("������Ҫ�������Ʒ��Ϣ\n");
        printf("��ƷID��");
        scanf("%s",&new_good->data.good_id);
            for(;refer != NULL;refer = refer->next){
                if(strcmp(new_good->data.good_id,refer->data.good_id) == 0){
                    printf("����ƷID�Ѵ���\n");
                    free(new_good);
                    return;
                }
            }
        printf("��Ʒ���ƣ�");
        scanf("%s",&new_good->data.good_name);
        printf("��Ʒ�۸�");
        scanf("%d",&new_good->data.good_price);
        printf("��Ʒ�ۿۣ�");
        scanf("%s",&new_good->data.good_discount);
        printf("��Ʒ������");
        scanf("%d",&new_good->data.good_amount);
        printf("��Ʒʣ�ࣺ");
        scanf("%d",&new_good->data.good_remain);
        printf("�������ֱ�����Ҫ�������Ʒλ�ã�0.��Ʒ�б�β�� 1.��Ʒ�б�ͷ�� i.��Ʒ�б��м��i��λ�� ");
        fflush(stdin);

        //ѡ�����λ��
        while(1){
            scanf("%d",&choose);
            fflush(stdin);
            if((*goodnumber == 0) && (choose == 0 || choose == 1)){
                new_good->next = now;
                (*L) = new_good;
                (*goodnumber)++;
                break;
            }else if((*goodnumber == 0) && choose != 1 && choose != 0){
                printf("λ��������Ч�����������룺");
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
                    printf("λ��������Ч�����������룺");
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
//ð������ ��ָ����ʱ����ʵ�� ��ֵ
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
