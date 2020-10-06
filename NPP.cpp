#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<windows.h>
# define MAX_VALUE 9999;


using namespace std;

void SetColor(int ForgC);

void sort(int* a, int *b,int* pt,int *pro,int n){
	int k,j,key1,key2,key3,key4;
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

int findLeastPriority(int* priority,int n){
	int min_value=priority[0];
	int min_index=0;
	for(int i=1; i<n; i++){
		if(priority[i]<min_value){
			min_value=priority[i];
			min_index=i;
		}
	}
	return min_index;
}

int findLeastPriority(int* priority, int* at, int ct){
	int min_value=priority[0];
	int min_index=0;
	for(int i=0; at[i]<=ct; i++){
		if(priority[i]<min_value){
			min_value=priority[i];
			min_index=i;
		}
	}
	return min_index;
}

int main(){
	int n;
	cout<< "\n\t\t NON-PREEMPTIVE PRIORITY SCHEDULING \n";
    cout<< "\n\tEnter number of processes: ";
    cin >> n;

    cout<< "\n\n\t   [ Enter arrival time , burst time and priority level for each process ]\n\n";
	int at[n],bt[n],pt[n],pt1[n],ct[n],tat[n],wt[n],pro[n];

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

	int c,i=0,index=1;
	sort(at,bt,pt,pro,n);
	for(int i=0; i<n; i++)
		pt1[i]=pt[i];


	printf("\n\n\t[ NON-PREEMPTIVE PRIORITY SCHEDULING GANTT CHART ]\n\n\n");
	c=at[0]+bt[0];
	ct[0]=c;
	pt[0]=MAX_VALUE;
	SetColor(rand());
	printf(" P[%d] ",pro[0]);
	 for(int t=0;t<bt[i];t++)
            {
              //  SetColor(rand());
                printf("\xDB");
                printf("");
            }

	while(index<n){
		if(ct[i]>=at[n-1]){
			i=findLeastPriority(pt,n);
			pt[i]=MAX_VALUE;
			SetColor(rand());
			printf(" P[%d] ",pro[i]);
			 for(int t=0;t<bt[i];t++)
            {
               // SetColor(rand());
                printf("\xDB");
                printf("");
            }
			 for(int t=0;t<bt[i];t++)
            {
               // SetColor(t+5);
                printf("\xDB");
                printf("");
            }
			c+=bt[i];
			ct[i]=c;
		}
		else{
			i=findLeastPriority(pt,at,c);
			pt[i]=MAX_VALUE;
			SetColor(rand());
			printf(" P[%d] ",pro[i]);
			 for(int t=0;t<bt[i];t++)
            {
                //SetColor(t+9);
                printf("\xDB");
                printf("");
            }
			c+=bt[i];
			ct[i]=c;
		}
		index++;
	}

	// ito yung WT and TAT
	float sum_tat=0,sum_wt=0;
	for(int i=0; i<n; i++){
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt[i];
		sum_tat+=tat[i];
		sum_wt+=wt[i];
	}

	SetColor(15);
    printf("\n\n\n\t[ NON-PREEMPTIVE PRIORITY SCHEDULING TABLE ]\n\n");
	printf("\n\nPN  |   PT  |   AT  |   BT  |   ET   |  WT  |  RT  |  TAT\n");
	for(int i=0; i<n; i++){
		printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pro[i],pt1[i],at[i],bt[i],ct[i],wt[i],wt[i],tat[i]);

	}

	printf("\n\nAvg Turn Around Time: %.2f\nAvg Responce Time: %.2f\nAvg Wating Time: %.2f\n",sum_tat/n,sum_wt/n,sum_wt/n);

    cout<< "\n\n\n";
    cout << "\t\t\t Press [ ENTER ] key to return to Menu \n";
    getch();
    system("cls");
    cout<< " \n\t\t [ Proceeding to Main Menu ] \n";
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



