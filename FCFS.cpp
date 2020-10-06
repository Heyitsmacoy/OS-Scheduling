#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

void SetColor(int ForgC);

int main()
{
    int bt[10]={0},at[10] ={0},tat[10] ={0},wt[10] ={0},rt[10] ={0};
    int n, sum = 0;
    float totalTAT=0,totalWT=0;

    cout<< "\n\t\t FIRST COME - FIRST SERVE SCHEDULING \n";
    cout<< "\n\tEnter number of processes: ";
    cin >> n;

    cout<< "\n\n\t   [ Enter arrival time & burst time for each process ]\n\n";

    for(int i = 0; i< n;i++)
    {
            printf("\tArrival time of process [%d] : ", i+1);
            scanf("%d", &at[i]);

            printf("\tBurst time of process [%d] : ", i+1);
            scanf("%d",&bt[i]);

            printf("\n");
    }

    /// response time

    for (int j=0;j<n;j++)
    {
            sum+=bt[j];
            rt[j]+=sum;
    }

    /// turn around

    for(int k=0;k<n;k++)
    {
            tat[k]=rt[k]-at[k];
            totalTAT+=tat[k];
    }

    for(int k=0;k<n;k++)
    {
            wt[k]=tat[k]-bt[k];
            totalWT+=wt[k];
    }

    printf("\n\t\t\t[ FIRST-COME-FIRST-SERVE TABLE ]  \n\n");
    printf("\tP#\t BT\t AT\t WT\t RT\t TAT\t\n\n");

    for(int i=0;i<n;i++)
    {
            printf("\tP%d\t %d\t %d\t %d\t %d\t %d\n",i+1,bt[i],at[i],wt[i],wt[i],tat[i]);

    }
    printf("\n\n\n");
    printf("\n\t\t[ First-Come-First-Serve Gantt Chart ]\n\n");
      for(int i=0;i<n;i++)
    {
            SetColor(i+2);
            printf(" P[%d]",i+1);
              for(int t=0;t<bt[i];t++)
            {
                SetColor(i+2);
                printf("\xDB");
            }
    }

    SetColor(15);
    printf("\n\n\n\tAverage Waiting Time = %.2f\n",totalWT/n);
    printf("\tAverage Response Time = %.2f\n",totalWT/n);
    printf("\tAverage Turn Around Time = %.2f\n",totalTAT/n);

    printf("\n\n\n");

    printf("\t\t\t Press [ ENTER ] key to return to Menu \n");
    getch();
    system("cls");
    printf(" \n\t\t [ Proceeding to Main Menu ] \n");
    Sleep(1000);
    system("Main.exe");


}

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


