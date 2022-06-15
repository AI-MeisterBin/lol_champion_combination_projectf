//���� ���� ���α׷� - ���� ���Ḯ��Ʈ
//���� ������ ���� ����Ʈ�� ����
//�ߺ� ������ ó�� ����
//�Է� ������ ���� ���� ó�� ����

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <string.h> 

#define MAX_NLEN    30 //�ִ� �̸� ����
#define MAX_SPEC 5 //Ư�� ��
typedef struct Champion {//è�Ǿ� ����ü ����
    char name[MAX_NLEN + 1];//�̸�
    int num; //��ȣ
    int ability[MAX_SPEC];//�ɷ�ġ

    struct Champion* next;
    struct Champion* prev;

}Champion;


const char* ability_List[MAX_SPEC] = { "��ŷ��","������","���ӵ�", "cc���", "ĳ����" };


Champion* head, * tail;
void set_Cham();
void Initialize();//�ʱ�ȭ
void Run();
void Exit();//�����ϱ� ���� �Ҵ��� �޸� ����
int main(void)
{
    Initialize();//�ʱ�ȭ
    //set_Cham(); �޸��忡 �ִ� �����͸� �����ͼ� ���� -> ����
    Run();
    Exit();//�����ϱ� ���� �Ҵ��� �޸� ����
    return 0;
}
/*
void set_Cham()
{
    FILE* fp;
    fopen_s(&fp, "Champion_List", "r");
    if (fp == NULL)
    {
        printf("����");
        return 0;
    }
    char buff[100];
    while (!feof(fp))
    {
        fgets(buff, 100, fp);

        char* context = NULL;
        char* cut_buff = strtok_s(buff, " ",&context); // buff �� �ڸ� �̸� ��ŷ�� ������ ���ӵ� cc��� ĳ����

        while (cut_buff != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
        {
            int num = 0;
            Champion* cham = 0;
            int s = 0;

            cham = (Champion*)malloc(sizeof(Champion));
            cham->num = num;
            strcpy_s(cham->name,sizeof(cham->name), cut_buff);
            printf(cham->name);
            /*for (s = 0; s < MAX_SPEC; s++)
            {
                strcpy_s(cham->ability + s, sizeof(cham->ability), cut_buff[s+1]);
            }
            cut_buff = strtok_s(NULL, " ", &context);      // ���� ���ڿ��� �߶� �����͸� ��ȯ
        }
        
        int num = 0;
        Champion* cham = 0;

        cham = (Champion*)malloc(sizeof(Champion));
        cham->num = num;
        strcpy(cham->name, cut_buff[0])
    }
    fclose(fp);
}
*/


void Initialize()
{
    head = (Champion*)malloc(sizeof(Champion));//���� ��� ����
    tail = (Champion*)malloc(sizeof(Champion));//���� ��� ����
    head->next = tail;//�� �� ���̳�� next�� tail�� ����
    tail->prev = head;//�� �� ���̳�� prev�� head�� ����
    head->prev = tail->next = NULL;
}

int SelectMenu();//�޴� ��� �� ����
void AddChampion();//è�Ǿ� ������ �Է�
void RemoveChampion();//è�Ǿ� ������ ����
void FindChampion();//è�Ǿ� �˻�
void ListChampion();//��� ����
void combination_judge();//�� ���� �Ǵ�
void Run()
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        switch (key)//������ Ű�� ���� ��� ����
        {
        case 1: AddChampion(); break;
        case 2: RemoveChampion(); break;
        case 3: ListChampion(); break;
        case 4: combination_judge(); break;
        default: printf("�߸� �����Ͽ����ϴ�.\n"); break;
        }
    }
    printf("���α׷� ����\n");
}

int SelectMenu()
{
    int key = 0;

    printf("�� ���� �Ǵ� ���α׷� 0:����\n");
    printf("1: è�Ǿ� ������ �Է� 2: è�Ǿ� ������ ���� 3: è�Ǿ� ��� ���� 4: �� ���� ���� �� ��� \n"); // +è�Ǿ� ��ȣ �Է�
    scanf_s("%d", &key);

    return key;
}

int IsAvailNum(int num);//��ȿ�� ��ȣ���� �Ǻ�
int IsAvailScore(int score);//��ȿ�� �ɷ�ġ���� �Ǻ�
void AddChampion()
{
    int num = 0;
    Champion* cham = 0;
    int s = 0;

    printf("�߰��� è�Ǿ� ��ȣ: ");
    scanf_s("%d", &num);


    cham = (Champion*)malloc(sizeof(Champion));//è�Ǿ� ����ü ���� �޸� �Ҵ�    
    cham->num = num;
    printf("�̸�: ");
    scanf_s("%s", cham->name, sizeof(cham->name));

    for (s = 0; s < MAX_SPEC; s++)
    {
        printf("%s :", ability_List[s]);
        scanf_s("%d", cham->ability + s);

        if (IsAvailScore(cham->ability[s]) == 0)//��ȿ�� ������ �ƴ� ��
        {
            cham->ability[s] = -1;
            printf("�Է��� �ɷ�ġ�� ��ȿ���� �ʾƼ� %s �ɷ�ġ�� �Է� ó������ �ʾҽ��ϴ�.\n", ability_List[s]);
        }
    }

    //���� ������ ��带 tail �տ� �Ŵޱ�
    cham->next = tail;
    cham->prev = tail->prev;
    tail->prev->next = cham;
    tail->prev = cham;
}

int IsAvailScore(int score)
{
    return (score >= 0) && (score <= 100);
}
void RemoveChampion()
{
    int num;
    Champion* seek;

    printf("������ è�Ǿ� ��ȣ: ");
    scanf_s("%d", &num);

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        if (seek->num == num)
        {
            //���Ḯ��Ʈ���� ��ũ ����
            seek->prev->next = seek->next;
            seek->next->prev = seek->prev;
            free(seek);//�޸� ����
            printf("�����Ͽ����ϴ�.\n");
            return;
        }
    }
    printf("�����Ͱ� �����ϴ�.\n");

}
void ViewchamData(Champion* cham);
void FindChampion()
{
    int num = 0;
    Champion* seek = 0;

    printf("�˻��� è�Ǿ� ��ȣ: ");
    scanf_s("%d", &num);

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        if (seek->num == num)
        {
            ViewchamData(seek);
            return;
        }
    }
    printf("�����Ͱ� �����ϴ�.\n");

}
void ViewchamData(Champion* cham)
{
    int i = 0;
    int s = 0;

    printf("%4d %15s ", cham->num, cham->name);
    for (s = 0; s < MAX_SPEC; s++)
    {
        printf("%6d ", cham->ability[s]);
    }
    printf("\n");
}
void ListChampion()
{
    int s = 0;
    Champion* seek = 0;

    printf("%4s %15s ", "��ȣ", "�̸�");
    for (s = 0; s < MAX_SPEC; s++)
    {
        printf("%4s ", ability_List[s]);
    }
    printf("�ɷ�ġ�� -1�� ���� ���Է�\n");

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        ViewchamData(seek);
    }
}
void combination_judge()
{   
    int num = 0;
    int s = 0;
    Champion* seek = 0;
    int tanking = 0;
    int keeping = 0;
    int con_dam = 0;
    int cc = 0;
    int carry = 0;
    printf("������ �Ǵ��� ���� ĳ���� ��ȣ�� �ϳ��� �Է����ּ���\n��ȣ : ");
    for (int i = 0; i < 5; i++) 
    {
        scanf_s("%d", &num);
        for (seek = head->next; seek != tail; seek = seek->next)
        {
            if (seek->num == num)
            {
                ViewchamData(seek);
                printf("%4s %15s ", "��ȣ", "�̸�");
                for (s = 0; s < MAX_SPEC; s++)
                {
                    printf("%4s ", ability_List[s]);
                }
                printf("�ɷ�ġ�� -1�� ���� ���Է�\n");
                for (s = 0; s < MAX_SPEC; s++)
                {
                    tanking += seek->ability[0];
                    keeping += seek->ability[1];
                    con_dam += seek->ability[2];
                    cc += seek->ability[3];
                    carry += seek->ability[4];
                }
            }
        }
    }
    printf("��ŷ�� : %d\n������ : %d\n���ӵ� : %d\ncc��� : %d\nĳ���� : %d\n", tanking/5, keeping/5, con_dam/5, cc/5, carry/5);
    int result_ability[5] = { tanking / 5, keeping / 5, con_dam / 5, cc / 5, carry / 5 };
    int max = 1;
    for (int j = 0; j < 5; j++)
    {
        if (result_ability[j] > result_ability[max])
        {
            max = j;
        }
    }
    if (max == 0)
    {
        printf("�� ���� ���� �پ ���� ��ŷ���̸� ");
    }
    else if (max == 1)
    {
        printf("�� ���� ���� �پ ���� �������̸� ");
    }
    else if (max == 2)
    {
        printf("�� ���� ���� �پ ���� ���ӵ��̸� ");
    }
    else if (max == 3)
    {
        printf("�� ���� ���� �پ ���� cc����̸� ");
    }
    else if (max == 4)
    {
        printf("�� ���� ���� �پ ���� ĳ�����̸�");
    }

    if (result_ability[0] <= 200)
    {
        printf(" ��ŷ��");
    }
    else if (result_ability[1] <= 200)
    {
        printf(" ������");
    }
    else if (result_ability[2] <= 200)
    {
        printf(" ���ӵ�");
    }
    else if (result_ability[3] <= 200)
    {
        printf(" cc���");
    }
    else if (result_ability[4] <= 200)
    {
        printf(" ĳ����");
    }
    if ((result_ability[0] > 200) && (result_ability[1] > 200) && (result_ability[2] > 200) && (result_ability[3] > 200) && (result_ability[4] > 200))
    {
        printf("������ �ɷ� ���� ���� �����Դϴ�!");
    }
    else
    {
        printf("�� �����մϴ�.\n");
    }
}
void Exit()
{
    Champion* seek = head;

    while (seek->next)
    {
        seek = seek->next;
        free(seek->prev);
    }
    free(seek);
}