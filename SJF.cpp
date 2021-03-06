#include<iostream>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>

using namespace std;
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

int main()
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
    system("Main.exe");

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


