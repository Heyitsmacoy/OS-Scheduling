#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

typedef struct CPUsched {
    int p,at,bt,wt,rt,tat,st,ct,cbt,pri;
}CPUS;

void SetColor(int);
void sort_rr(CPUS a[],int);
void makenull(CPUS a[],int);


/// RR Functions ///

void sort_rr(CPUS a[],int pro){
       int i,j;
       CPUS temp;
       for(i=0;i<pro;i++){
              for(j=i+1;j<pro;j++){
                     if(a[i].at > a[j].at){
                           temp = a[i];
                           a[i] = a[j];
                           a[j] = temp;
                     }
              }
       }
       return;
}

void makenull(CPUS a[],int pro){
	int i;
	for(i=0;i<pro;i++){
		a[i].p = 0;
		a[i].at = 0;
		a[i].bt = 0;
		a[i].wt = 0;
		a[i].rt = 0;
		a[i].tat = 0;
		a[i].st = 0;
	}
}
///

int main()
{
    int i,j,pro,time,remain,flag=0,tq;
    CPUS a[100];
    float avgwt=0,avgtt=0;
    cout<< "\n\t\t\t   ROUND-ROBIN SCHEDULING \n";
    printf("\n\t Enter Number of Process: ");
    scanf("%d",&pro);
    remain=pro;
    cout<< "\n\n\t   [ Enter arrival time & burst time for each process ]\n\n";
    printf("\n");
    for(i=0;i<pro;i++){
        printf("\t\t Arrival Time [%d]: ",i+1);
        scanf("%d",&a[i].at);
        printf("\t\t Burst Time [%d]: ",i+1);
        scanf("%d",&a[i].bt);
        a[i].p = i;
        a[i].rt = a[i].bt;
        printf("\n");
    }
    sort_rr(a,pro);
    printf("\n\t Enter time quantum: ");
    scanf("%d",&tq);

    cout<<endl<<"\n\t\t\t[ ROUND-ROBIN SCHEDULING GANTT CHART ]  \n"<<endl;
    SetColor(1);
    printf("0");
    for(time=0,i=0;remain!=0;)
    {
        if(a[i].rt<=tq && a[i].rt > 0){
            time = time + a[i].rt;
            SetColor(15);
            printf(" -->");
            SetColor(a[i].p+2);
            printf(" P[%d]",a[i].p+1);
            SetColor(15);
            printf(" ---");
            SetColor(1);
            printf(" %d",time);
            SetColor(15);
            a[i].rt = 0;
            flag = 1;
        }
        else if(a[i].rt > 0){
            a[i].rt = a[i].rt - tq;
            time = time + tq;
            printf(" -->");
            SetColor(a[i].p+2);
            printf(" P[%d]",a[i].p+1);
            SetColor(15);
            printf(" ---");
            SetColor(1);
            printf(" %d",time);
            SetColor(15);
        }
        if(a[i].rt==0 && flag == 1){
            remain--;
            a[i].tat = time-a[i].at;
            a[i].wt = time-a[i].at-a[i].bt;
            avgwt = avgwt + time-a[i].at-a[i].bt;
            avgtt = avgtt + time-a[i].at;
            flag=0;
        }
        if(i==pro-1)
            i=0;
        else if(a[i+1].at <= time)
            i++;
        else
            i=0;
    }
    cout<<"\n\n\t\t\t[ ROUND-ROBIN SCHEDULING TABLE ] "<<endl;

    printf("\n\tP\tAT\tBT\tWT\tRT\tTaT\n");

    for(i=0;i<pro;i++){
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n",a[i].p+1,a[i].at,a[i].bt,a[i].wt,a[i].rt,a[i].tat);
    }
    SetColor(15);
    avgwt = avgwt/pro;
    avgtt = avgtt/pro;

    printf("\n\n\tAverage Waiting Time : %.2f\n",avgwt*1.0);
    printf("\tAverage Response Time : %.2f\n",avgwt*1.0);
    printf("\tAverage Turnaround Time : %.2f\n\n",avgtt*1.0);
    printf("\n\n\t\t\t Press [ ENTER ] key to return to Menu \n");
    getch();
    system("cls");
    printf(" \n\t\t [ Proceeding to Main Menu ] \n");
    Sleep(1000);
    system("Main.exe");
    makenull(a,pro);
}


void SetColor(int ForgC){
     WORD wColor;
     //This handle is needed to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
      }
}
