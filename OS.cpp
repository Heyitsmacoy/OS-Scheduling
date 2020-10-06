#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<windows.h>
#define MAX_VALUE 9999;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13


using namespace std;

typedef struct CPUsched {
    int p,at,bt,wt,rt,tat,st,ct,cbt,pri;
}CPUS;


/// For Setting of Color ///
void SetColor(int ForgC)
{
     WORD wColor;

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


/// For Button ///

void chooser();
void listenArrowKeys();
void chooserValidation();
int checkChoosen();

int curSelection = 0;
int length = 6;
char commands[256][256] = {
    "(FCFS) FIRST-COME-FIRST-SERVE SCHEDULING",
    "(SJF)  SHORTEST-JOB-FIRST SCHEDULING",
    "(SRTF) SHORTEST-REMAINING-TIME-FIRST SCHEDULING",
    "(NPP)  NON-PREEMPTIVE-PRIORITY SCHEDULING",
    "(PP)   PREEMPTIVE-PRIORITY SCHEDULING",
    "(RR)   ROUND-ROBIN SCHEDULING",
    "EXIT "
    };

void listenArrowKeys(){
    int c = 0;
    while(1)
    {
        chooser();
        c = 0;
        c = getch();

        if(c == KEY_UP || c == KEY_LEFT){
            curSelection--;
        }else if(c == KEY_DOWN || c == KEY_RIGHT){
            curSelection++;
        }else if(c == KEY_ENTER){
            break;
        }
        chooserValidation();

    }

    checkChoosen();
}

void chooserValidation(){
    if(curSelection <= 0){
        curSelection = 0;
    }else if(curSelection > length){
        curSelection = length;
    }
}


/// SJF Code ///

int count = 0;
int mat[10][6];
int se[10][6];

void SetColor(int ForgC);
int custom();
int valArrival(int num, int mat[][6]);
void arrangeBurstTime(int num, int mat[][6]);
void calculate();
void gantChart();
void average();
void showResult(int num, int mat[][6]);
void getStartAndEnd(int count, int mat[][6]);

/// SJF Functions ///
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrangeArrival(int num, int mat[][6])
{
    for(int i=0; i<num; i++)
    {
        for(int j=0; j<num-i-1; j++)
        {
            if(mat[j][1] > mat[j+1][1])
            {
                for(int k=0; k<5; k++)
                {
                    swap(mat[j][k], mat[j+1][k]);
                }
            }
        }
    }
}

void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for(int i=1; i<num; i++)
    {
        temp = mat[i-1][3];
        int low = mat[i][2];
        for(int j=i; j<num; j++)
        {
            if(temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for(int k=0; k<6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}

int custom(){
    count = 5;
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 5;

    mat[1][0] = 2;
    mat[1][1] = 2;
    mat[1][2] = 2;

    mat[2][0] = 3;
    mat[2][1] = 3;
    mat[2][2] = 1;

    mat[3][0] = 4;
    mat[3][1] = 8;
    mat[3][2] = 2;

    mat[4][0] = 5;
    mat[4][1] = 9;
    mat[4][2] = 3;
}


int valArrival(int num, int mat[][6]){

    for(int i=0; i<num; i++)
    {
        if (mat[i][1] != 0)
        {
           return 1;
        }

    }
    arrangeBurstTime(count, mat);

}

void arrangeBurstTime(int num, int mat[][6])
{
    int temp = 0;

    for(int i = 0; i<num; i++)
    {
        for (int j = 0; j < num - 1; j++)
        {
            if(mat[j][2] > mat[j + 1][2])
                {
                    swap(mat[j][2], mat[j + 1][2]);
                    swap (mat[j][0], mat[j + 1][0]);
                }
        }

    }
}

void calculate(){
    cout<<" \n\t\t SHORTEST-JOB FIRST SCHEDULING \n";
    cout<<"\n\tEnter number of Process: ";
    cin>>count;

    cout<< "\n\n\t   [ Enter arrival time & burst time for each process ]\n\n";

    for(int i=0; i<count; i++)
    {
        mat[i][0] = i + 1;
        cout<<"\tArrival Time of Process ["<<mat[i][0]<<"]: ";
        cin>>mat[i][1];
        cout<<"\tBurst Time of Process ["<<mat[i][0]<<"]: ";
        cin>>mat[i][2];
        cout<<"\n";
    }

}

void getStartAndEnd(int count, int mat[][6]){
    int i;
    for(i = 0; i < count; i++){
        if(i != 0){
            se[i][1] = se[i - 1][1] + mat[i][2] ;
            se[i][0] = se[i - 1][1];
        }else{
            se[i][0] = 0;
            se[i][1] = mat[i][2];
        }
    }
}

void showResult(int num, int mat[][6]){
    cout<<"\n\t\t\t\t [ Shortest Job First Table ]\n\n\n";
    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tResponse Time\tTurnaround Time\n";

    for(int i=0; i<count; i++)
    {
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\n";
    }
}

void average(){
    float aveWT = 0, aveRT = 0, aveTAT = 0;


    for(int i = 0; i <= count; i++){
        aveWT += mat[i][4];
        aveRT += mat[i][4];
        aveTAT += mat[i][5];
    }
    aveWT = aveWT / count;
    aveRT = aveRT / count;
    aveTAT = aveTAT / count;

    SetColor(15);
    cout<<"\n\n\n\tAverage Waiting Time: "<< aveWT << endl;
    cout<<"\tAverage Response Time: "<< aveRT << endl;
    cout<<"\tAverage Turn Around Time: "<< aveTAT << endl;

}

void gantChart(){

    cout<<"\n\n\n";
    for(int i = 0; i < count; i++ ){
        SetColor(i+2);
        cout<<"P["<< mat[i][0] <<"]";
        for(int e = 0; e < se[i][1] - se[i][0]; e++){
          SetColor(i+2);
          cout<<"\xDB";
       }
    }


}

/// SRTF Functions //

void sort(int* a, int *b,int *pro,int n){
	int k,j,key1,key2,key3;
	for(int i=1; i<n; i++){
		j=i-1;
		key1=a[i];
		key2=b[i];
		key3=pro[i];
		while(j>=0 && key1<a[j]){
			a[j+1]=a[j];
			b[j+1]=b[j];
			pro[j+1]=pro[j];
			j--;
		}
		a[j+1]=key1;
		b[j+1]=key2;
		pro[j+1]=key3;
	}
}

int findLeastBurstTime(int* bt, int* at, int ct,int n){
	int min_value=bt[0];
	int min_index=0;
	for(int i=0; i<n && at[i]<=ct; i++){
		if(bt[i]<min_value){
			min_value=bt[i];
			min_index=i;
		}
	}
	return min_index;
}

/// NPP Functions ///

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

/// PP Functions ///

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

int find_Least_Priority(int* priority, int* at, int ct,int n){
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

/// RR Functions ///

void sort_rr(CPUS a[],int);
void makenull(CPUS a[],int);

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


/// Scheduling Functions ///
    int FCFS();
    int SJF();
    int SRTF();
    int NPP();
    int PP();
    int RR();

///
int main(){
    listenArrowKeys();
}


void chooser(){
    system("cls");
    int i;
   cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
   cout << "\n" << endl;
   SetColor(rand());
   cout << "  OOOOOO OOOOOO   OOOOOO  OOOOOO  OO  OO  OOOOOO  OOOOO   OO  OO  OO      OOOOOO  OO  OO  OOOOOO " << endl;
   cout << "  OO  OO OO       OO      OO      OO  OO  OO      OO  OO  OO  OO  OO        OO    OOO OO  OO     " << endl;
   cout << "  OO  OO OOOOOO   OOOOOO  OO      OOOOOO  OOOOOO  OO   O  OO  OO  OO        OO    OOOOOO  OO OOO " << endl;
   cout << "  OO  OO     OO       OO  OO      OO  OO  OO      OO  OO  OO  OO  OO        OO    OO OOO  OO  OO " << endl;
   cout << "  OOOOOO OOOOOO   OOOOOO  OOOOOO  OO  OO  OOOOOO  OOOO    OOOOOO  OOOOOO  OOOOOO  OO OOO  OOOOOO " << endl;
   cout << "\n" << endl;
   SetColor(15);
   cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
   cout << "\n" << endl;
    for(i = 0; i <= length; i++){

        if(i == curSelection){
            SetColor(rand()); printf("\t\t\t[X] %s\n",commands[i]);
        }else {
            SetColor(15);
            printf("\t\t\t[ ] %s\n",commands[i]);
        }
    }
    SetColor(15);
    cout << "\n" << endl;
    cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
}


int checkChoosen(){

    switch(curSelection){

    case 0:
         system("cls");
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        cout<< " \n\t\t [ Proceeding to First Come First Serve Scheduling ] " << endl;
        cout<< " \n\n\t\t\t     [ Please Wait for a moment ] " << endl;
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        Sleep(1000);
        system("cls");
        FCFS();
        break;
    case 1:
       system("cls");
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        cout<< " \n\t\t [ Proceeding to Short-Job First Scheduling ] " << endl;
        cout<< " \n\n\t\t\t [ Please Wait for a moment ] " << endl;
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        Sleep(1000);
        system("cls");
        SJF();
        break;
    case 2:
        system("cls");
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        cout<< " \n\t\t [ Proceeding to Shortest Remaining Time First Scheduling ] " << endl;
        cout<< " \n\n\t\t\t        [ Please Wait for a moment ] " << endl;
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        Sleep(1000);
        system("cls");
        SRTF();
        break;
    case 3:
        system("cls");
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        cout<< " \n\t\t [ Proceeding to Non-Preemptive Priority Scheduling ] " << endl;
        cout<< " \n\n\t\t\t     [ Please Wait for a moment ] " << endl;
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        Sleep(1000);
        system("cls");
        NPP();
        break;
    case 4:
        system("cls");
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        cout<< " \n\t\t [ Proceeding to Pre-emptive Priority Scheduling ] " << endl;
        cout<< " \n\n\t\t\t   [ Please Wait for a moment ] " << endl;
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        Sleep(1000);
        system("cls");
        PP();
        break;
    case 5:
        system("cls");
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        cout<< " \n\t\t [ Proceeding to Round-Robin Scheduling ] " << endl;
        cout<< " \n\n\t\t       [ Please Wait for a moment ] " << endl;
        cout<<"\n\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB"<<endl;
        Sleep(1000);
        system("cls");
        RR();
        break;
    case 6:
        system("cls");
      exit(0);
        break;
    default: exit(0);break;
    }

}

int FCFS()
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

    for (int j=0;j<n;j++)
    {
            sum+=bt[j];
            rt[j]+=sum;
    }

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
    system("OS.exe");

}

int SJF()
{
    int i = 0;
    calculate();
    valArrival(count, mat);
    if (i == 1)
    {
        arrangeArrival(count, mat);
    }
    completionTime(count, mat);
    getStartAndEnd(count, mat);
    showResult(count, mat);
    gantChart();
    average();
    SetColor(15);
    cout<< "\n\n\n";
    cout << "\t\t\t Press [ ENTER ] key to return to Menu \n";
    getch();
    system("cls");
    cout<< " \n\t\t [ Proceeding to Main Menu ] \n";
    Sleep(1000);
    system("OS.exe");
}

int SRTF()
{
    int n;
	cout<< "\n\t\t SHORTEST-REMAINING-TIME-FIRST SCHEDULING \n";
    cout<< "\n\tEnter number of processes: ";
    cin >> n;

    cout<< "\n\n\t   [ Enter arrival time and burst time of each process ]\n\n";
	int at[n],bt[n],bt1[n],ct[n],tat[n],wt[n],pro[n];


	for(int i=0; i<n; i++){
        printf("\tArrival time of process P[%d] : ", i+1);
        scanf("%d", &at[i]);

        printf("\tBurst time of process P[%d] : ", i+1);
        scanf("%d",&bt[i]);

        printf("\n");
		pro[i]=i+1;

	sort(at,bt,pro,n);
	for(int i=0; i<n; i++)
		bt1[i]=bt[i];
	}


	printf("\n\n\t[ SHORTEST-REMAINING-TIME-FIRST SCHEDULING GANTT CHART ]\n\n\n");

	int prev_i,c,i,loop_count=n,max=MAX_VALUE;
	i=findLeastBurstTime(bt,at,at[0],n);
	SetColor(rand());
	printf(" P[%d] ",pro[i]);
	for(int t=0;t<bt[i];t++)
            {
                printf("\xDB");
                printf("");
            }
	c=at[i]+1;
	ct[i]=c;
	bt[i]--;

	if(bt[i]==0)
	{
		bt[i]=MAX_VALUE;
		loop_count--;
	}

	while(loop_count>0)
	{
		prev_i=i;
		i=findLeastBurstTime(bt,at,c,n);
		if(prev_i!=i)
            SetColor(rand());
			printf(" P[%d]",pro[i]);
			for(int t=0;t<bt[i];t++)
            {
                printf("\xDB");
                printf("");
            }
		c++;
		if(bt[i]!=max)
		{
			ct[i]=c;
			bt[i]--;
			if(bt[i]==0)
			{
				bt[i]=MAX_VALUE;
				loop_count--;
			}
		}
	}

	// calculating waiting and turn around time
	float sum_tat=0,sum_wt=0;
	for(int i=0; i<n; i++){
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt1[i];
		sum_tat+=tat[i];
		sum_wt+=wt[i];
	}

    SetColor(15);
	printf("\n\n\n\t[ SHORTEST-REMAINING-TIME-FIRST SCHEDULING TABLE ]\n\n");
	printf("PN    |   AT  |   BT  |   ET   |  WT  |  RT  |  TAT\n");

	for(int i=0; i<n; i++){
		printf("P%d\t  %d\t  %d\t  %d\t  %d\t  %d\t %d\n",pro[i],at[i],bt1[i],ct[i],wt[i],wt[i],tat[i]);
	}

	printf("\n\nAvg Turn Around Time: %.2f\nAvg Responce Time: %.2f\nAvg Wating Time: %.2f\n",sum_tat/n,sum_wt/n,sum_wt/n);

    cout<< "\n\n\n";
    cout << "\t\t\t Press [ ENTER ] key to return to Menu \n";
    getch();
    system("cls");
    cout<< " \n\t\t [ Proceeding to Main Menu ] \n";
    Sleep(1000);
    system("OS.exe");
}

int NPP()
{
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
    system("OS.exe");
}

int PP()
{
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

	sort_pp(at,bt,pt,pro,n);
	for(int i=0; i<n; i++)
	{
		bt1[i]=bt[i];
		pt1[i]=pt[i];
	}


	printf("\n\n\t[ PREEMPTIVE PRIORITY SCHEDULING GANTT CHART ]\n\n\n");

	int prev_i,c,i,loop_count=n;
	i=find_Least_Priority(pt,at,at[0],n);

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
		i=find_Least_Priority(pt,at,c,n);
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
    system("OS.exe");
}

int RR()
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
    system("OS.exe");
    makenull(a,pro);

}
