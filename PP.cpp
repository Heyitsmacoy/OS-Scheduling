#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<windows.h>
# define MAX_VALUE 9999;


using namespace std;

void SetColor(int ForgC);

void sort_pp(int* a, int *b,int* pt,int *pro,int n){
	int j,key1,key2,key3,key4;
	for(int i=1; i<n; i++){
		j=i-1;
		key1=a[i];
		key2=b[i];
		key3=pt[i];
		key4=pro[i];
		while(j>=0 && key1<a[j]){
			a[j+1]=a[j];
			b[j+1]=b[j];
			pro[j+1]=pro[j];
			pt[j+1]=pt[j];
			j--;
		}
		a[j+1]=key1;
		b[j+1]=key2;
		pt[j+1]=key3;
		pro[j+1]=key4;
	}
}

int findLeastPriority(int* priority, int* at, int ct,int n){
	int min_value=priority[0];
	int min_index=0;
	for(int i=0; i<n && at[i]<=ct; i++){
		if(priority[i]<min_value){
			min_value=priority[i];
			min_index=i;
		}
	}
	return min_index;
}

int main(){
	int n;

	cout<< "\n\t\t PREEMPTIVE PRIORITY SCHEDULING \n";
    cout<< "\n\tEnter number of processes: ";
    cin >> n;

    cout<< "\n\n\t   [ Enter arrival time , burst time and priority level for each process ]\n\n";
	int at[n],bt[n],bt1[n],pt[n],pt1[n],ct[n],tat[n],wt[n],pro[n];

	for(int i=0; i<n; i++){
        printf("\tArrival time of process [%d] : ", i+1);
        scanf("%d", &at[i]);

        printf("\tBurst time of process [%d] : ", i+1);
        scanf("%d",&bt[i]);

        printf("\tPriority level of process [%d] : ", i+1);
        scanf("%d",&pt[i]);

        printf("\n");
		pro[i]=i+1;
	}

	sort(at,bt,pt,pro,n);
	for(int i=0; i<n; i++)
	{
		bt1[i]=bt[i];
		pt1[i]=pt[i];
	}


	printf("\n\n\t[ PREEMPTIVE PRIORITY SCHEDULING GANTT CHART ]\n\n\n");

	int prev_i,c,i,loop_count=n;
	i=findLeastPriority(pt,at,at[0],n);

	SetColor(34);
	printf(" P[%d] ",pro[i]);

    for(int t=0;t<bt[i];t++)
            {
                SetColor(t+34);
                printf("\xDB");
                printf("");
            }
	c=at[i]+1;
	ct[i]=c;
	bt[i]--;

	if(bt[i]==0)
	{
		pt[i]=MAX_VALUE;
		loop_count--;
	}

	while(loop_count>0)
	{
		prev_i=i;
		i=findLeastPriority(pt,at,c,n);
		if(prev_i!=i)
            SetColor(rand());
			printf(" P[%d] ",pro[i]);
			 for(int t=0;t<bt[i];t++)
            {
                printf("\xDB");
                //printf("");
            }
		c++;
		ct[i]=c;
		bt[i]--;
		if(bt[i]==0)
		{
			pt[i]=MAX_VALUE;
			loop_count--;
		}
	}


	float sum_tat=0.0,sum_wt=0.0;
	for(int i=0; i<n; i++){
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt1[i];
		sum_tat=sum_tat+tat[i];
		sum_wt=sum_wt+wt[i];
	}

    SetColor(15);
    printf("\n\n\n\t\t[ PREEMPTIVE PRIORITY SCHEDULING TABLE ]\n");
	printf("\n\nPN  |   PT  |   AT  |   BT  |   ET   |  WT  |  RT  |  TAT\n");
	for(int i=0; i<n; i++){
		printf("p%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pro[i],pt1[i],at[i],bt1[i],ct[i],wt[i],wt[i],tat[i]);
	}

	printf("\n\nAvg Turn Around Time: %.2f\nAvg Responce Time: %.2f\nAvg Wating Time: %.2f\n",sum_tat/n,sum_wt/n,sum_wt/n);

    printf("\n\n\n");

    printf("\t\t\t Press [ ENTER ] key to return to Menu \n");
    getch();
    system("cls");
    printf(" \n\t\t [ Proceeding to Main Menu ] \n");
    Sleep(500);
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


