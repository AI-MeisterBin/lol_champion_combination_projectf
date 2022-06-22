
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <string.h> 

#define MAX_NLEN    30 //최대 이름 길이
#define MAX_SPEC 5 //특성 수
typedef struct Champion {//챔피언 구조체 정의
    char name[MAX_NLEN + 1];//이름
    int num; //번호
    int ability[MAX_SPEC];//능력치

    struct Champion* next;
    struct Champion* prev;

}Champion;


const char* ability_List[MAX_SPEC] = { "탱킹력","유지력","지속딜", "cc기력", "캐리력" };


Champion* head, * tail;
void set_Cham();
void Initialize();//초기화
void Run();
void Exit();//종료하기 전에 할당한 메모리 해제
int main(void)
{
    Initialize();//초기화
    //set_Cham(); 메모장에 있는 데이터를 가져와서 설정 -> 실패
    Run();
    Exit();//종료하기 전에 할당한 메모리 해제
    return 0;
}
/*
void set_Cham()
{
    FILE* fp;
    fopen_s(&fp, "Champion_List", "r");
    if (fp == NULL)
    {
        printf("실패");
        return 0;
    }
    char buff[100];
    while (!feof(fp))
    {
        fgets(buff, 100, fp);

        char* context = NULL;
        char* cut_buff = strtok_s(buff, " ",&context); // buff 를 자름 이름 탱킹력 유지력 지속딜 cc기력 캐리력

        while (cut_buff != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
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
            cut_buff = strtok_s(NULL, " ", &context);      // 다음 문자열을 잘라서 포인터를 반환
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
    head = (Champion*)malloc(sizeof(Champion));//더미 노드 생성
    tail = (Champion*)malloc(sizeof(Champion));//더미 노드 생성
    head->next = tail;//맨 앞 더미노드 next를 tail로 설정
    tail->prev = head;//맨 뒤 더미노드 prev를 head로 설정
    head->prev = tail->next = NULL;
}

int SelectMenu();//메뉴 출력 및 선택
void AddChampion();//챔피언 데이터 입력
void RemoveChampion();//챔피언 데이터 삭제
void FindChampion();//챔피언 검색
void ListChampion();//목록 보기
void combination_judge();//팀 조합 판단
void Run()
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: AddChampion(); break;
        case 2: RemoveChampion(); break;
        case 3: ListChampion(); break;
        case 4: combination_judge(); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
    }
    printf("프로그램 종료\n");
}

int SelectMenu()
{
    int key = 0;

    printf("롤 조합 판단 프로그램 0:종료\n");
    printf("1: 챔피언 데이터 입력 2: 챔피언 데이터 삭제 3: 챔피언 목록 보기 4: 팀 조합 최종 평가 출력 \n"); // +챔피언 번호 입력
    scanf_s("%d", &key);

    return key;
}

int IsAvailNum(int num);//유효한 번호인지 판별
int IsAvailScore(int score);//유효한 능력치인지 판별
void AddChampion()
{
    int num = 0;
    Champion* cham = 0;
    int s = 0;

    printf("추가할 챔피언 번호: ");
    scanf_s("%d", &num);


    cham = (Champion*)malloc(sizeof(Champion));//챔피언 구조체 동적 메모리 할당    
    cham->num = num;
    printf("이름: ");
    scanf_s("%s", cham->name, sizeof(cham->name));

    for (s = 0; s < MAX_SPEC; s++)
    {
        printf("%s :", ability_List[s]);
        scanf_s("%d", cham->ability + s);

        if (IsAvailScore(cham->ability[s]) == 0)//유효한 성적이 아닐 때
        {
            cham->ability[s] = -1;
            printf("입력한 능력치가 유효하지 않아서 %s 능력치를 입력 처리하지 않았습니다.\n", ability_List[s]);
        }
    }

    //새로 생성한 노드를 tail 앞에 매달기
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

    printf("삭제할 챔피언 번호: ");
    scanf_s("%d", &num);

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        if (seek->num == num)
        {
            //연결리스트에서 링크 조절
            seek->prev->next = seek->next;
            seek->next->prev = seek->prev;
            free(seek);//메모리 해제
            printf("삭제하였습니다.\n");
            return;
        }
    }
    printf("데이터가 없습니다.\n");

}
void ViewchamData(Champion* cham);
void FindChampion()
{
    int num = 0;
    Champion* seek = 0;

    printf("검색할 챔피언 번호: ");
    scanf_s("%d", &num);

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        if (seek->num == num)
        {
            ViewchamData(seek);
            return;
        }
    }
    printf("데이터가 없습니다.\n");

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

    printf("%4s %15s ", "번호", "이름");
    for (s = 0; s < MAX_SPEC; s++)
    {
        printf("%4s ", ability_List[s]);
    }
    printf("능력치가 -1인 곳은 미입력\n");

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
    printf("조합을 판단할 팀의 캐릭터 번호를 하나씩 입력해주세요\n번호 : ");
    for (int i = 0; i < 5; i++) 
    {
        scanf_s("%d", &num);
        for (seek = head->next; seek != tail; seek = seek->next)
        {
            if (seek->num == num)
            {
                ViewchamData(seek);
                printf("%4s %15s ", "번호", "이름");
                for (s = 0; s < MAX_SPEC; s++)
                {
                    printf("%4s ", ability_List[s]);
                }
                printf("능력치가 -1인 곳은 미입력\n");
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
    printf("탱킹력 : %d\n유지력 : %d\n지속딜 : %d\ncc기력 : %d\n캐리력 : %d\n", tanking/5, keeping/5, con_dam/5, cc/5, carry/5);
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
        printf("이 팀의 가장 뛰어난 것은 탱킹력이며 ");
    }
    else if (max == 1)
    {
        printf("이 팀의 가장 뛰어난 것은 유지력이며 ");
    }
    else if (max == 2)
    {
        printf("이 팀의 가장 뛰어난 것은 지속딜이며 ");
    }
    else if (max == 3)
    {
        printf("이 팀의 가장 뛰어난 것은 cc기력이며 ");
    }
    else if (max == 4)
    {
        printf("이 팀의 가장 뛰어난 것은 캐리력이며");
    }

    if (result_ability[0] <= 200)
    {
        printf(" 탱킹력");
    }
    else if (result_ability[1] <= 200)
    {
        printf(" 유지력");
    }
    else if (result_ability[2] <= 200)
    {
        printf(" 지속딜");
    }
    else if (result_ability[3] <= 200)
    {
        printf(" cc기력");
    }
    else if (result_ability[4] <= 200)
    {
        printf(" 캐리력");
    }
    if ((result_ability[0] > 200) && (result_ability[1] > 200) && (result_ability[2] > 200) && (result_ability[3] > 200) && (result_ability[4] > 200))
    {
        printf("부족한 능력 없이 좋은 조합입니다!");
    }
    else
    {
        printf("이 부족합니다.\n");
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
