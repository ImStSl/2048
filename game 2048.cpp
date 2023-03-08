#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<conio.h>
using namespace std;
int tb[10][10]={0}, temptb[10][10]={0};
struct scorerecord
{
    unsigned int row, column, scorere;
} screc;
unsigned int score;
void scoreboard(scorerecord);
void showmap(int , int );
int mp(int ,int);
void moveup(int , int);
void movedown (int, int );
void moveleft(int, int );
void moveright(int, int );
void random(int ,int);
int check( int, int);
int main()
{
    int r,c;
    char open [7], act[5];
    bool savegame=false;
    FILE *fptr, *ptr;
    backtomenu:
    cout<<"\a Wellcome To The <2048>"<<endl<<" PROGRAMMER: IM_STSL \n";
    cout<<"if you have an UNFINISHED game, use 'resume' to resume your play, \n else if you wanna START a new game, use 'new' \n if you wanna see scoreboard use 'board' \n";
    cin>>open;
    if(strcmp(open, "board")==0)
    {
        scoreboard(screc);
        cout<<"if you wanna exit the game enter 'exit' and if you wanna back to the menu enter 'back' \n";
        cin>>act;
        if(strcmp(act, "exit")==0)
            exit(1);
        else
        {
            system("cls");
            goto backtomenu;
        }
    }
    else if(strcmp(open, "resume")==0)
    {
        fptr=fopen("game.bin", "rb");
        if(fptr==NULL)
        {
            cout<<"error while opening file";
            exit(1);
        }
        fread(&r, sizeof(r), 1, fptr);
        fread(&c, sizeof(c), 1, fptr);
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<c; j++)
            {
                fread(&tb[i][j], sizeof(tb[i][j]), 1 , fptr);
                fread(&temptb[i][j], sizeof(temptb[i][j]), 1 , fptr);
            }
        }
        fread(&score, sizeof(score), 1 , fptr);
        fclose(fptr);
    }
    else if(strcmp(open, "new")==0)
    {
    cout<<"enter the number of rows and then columns of the map. \n please enter a number LESS than 11"<<endl;
    cout<<"the rows: ";
    cin>>r;
    cout<<endl<<"the columns: ";
    cin>>c;
    cout<<endl;
    }
    showmap(r,c);
    savegame=mp(r, c);

    if(savegame)
    {
        fptr=fopen("game.bin","wb");
        if(fptr==NULL)
        {
            cout<<"error while opening file";
            exit(1);
        }
        fwrite(&r, sizeof(r), 1, fptr );
        fwrite(&c, sizeof(c), 1, fptr);
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<c; j++)
            {
                fwrite(&tb[i][j], sizeof(tb[i][j]), 1 , fptr);
                fwrite(&temptb[i][j], sizeof(temptb[i][j]), 1 , fptr);
            }
        }
        fwrite(&score, sizeof(score), 1 , fptr);
        fclose(fptr);
        cout<<"\n see you later! \n";
    }
    screc.scorere=score;
    screc.row=r;
    screc.column=c;
    ptr=fopen("scoreboard.bin", "ab");
    if(ptr==NULL)
    {
        cout<<"error while opening";
        exit(1);
    }
    fwrite(&screc, sizeof(scorerecord), 1, ptr);
    fclose(ptr);
}
void scoreboard(scorerecord screc)
{
    FILE *ptr;
    ptr=fopen("scoreboard.bin", "rb");
    while(!feof(ptr))
    {
        fread(&screc, sizeof(scorerecord), 1, ptr);
        if(feof(ptr))
        {
            break;
        }
        cout<<" the "<<screc.row<<" * "<<screc.column<<" map "<<screc.scorere<<endl;
    }
    fclose(ptr);
}
void showmap(int r, int c)
{
    //k and z are counters, here i have manually increased the number of blocks in my array by increasing i and j
    int  maxmm, lenmax=1, counter, lentb=0, i=0, j=0;
    maxmm=0;
    for(int k=0; k<r; k++)
    {
        for(int z=0; z<c; z++)
        {
            if(tb[k][z]>maxmm)
                maxmm=tb[k][z];
        }
    }
    if(maxmm)
        lenmax=log10(maxmm)+1;
    for(int counter=0; counter<2*r+1; counter++)
    {
        cout<<"\t \t";
        if(counter%2==0)
        {
            for(int k=0; k<(c*lenmax+c+1); k++)
                cout<<(char)178;
            cout<<endl;
        }
        if(counter%2!=0)
        {
            for(int k=0; k<c; k++)
            {
                cout<<(char)178;
                if(tb[i][j]!=0)
                   {
                       cout<<tb[i][j];
                       lentb=log10(tb[i][j])+1;
                   }
                else
                    lentb=0;
                for(int z=0; z<lenmax-lentb; z++)
                    cout<<" ";
                j++;
            }
            cout<<(char)178<<endl;
            j=0;
            i++;
        }
    }
}
int mp(int r, int c)
{
    int i, j;
    char act;
    bool cntnu=true, flact=false;
    // flact is flag act, its made for when user enters wrong entries
    srand(time(0));
    for(int k=0; k<2; k++)
    {
        i=rand()%r;
        j=rand()%c;
        tb[i][j]=2;
        temptb[i][j]=2;
    }
    while(cntnu)
    {
        cout<<"\n \t w=up \n a=right \t d=left \n\t s=down \n u=undo \t e=save and exit \n \n score is:"<<(char)60<<score<<(char)62<<"\n";
        act=getch();
        if(act=='u')
        {
            for(int i=0; i<r ; i++)
            {
                for(int j=0; j<c; j++)
                    tb[i][j]=temptb[i][j];
            }
            system("cls");
            showmap(r, c);
            continue;
        }
        else
        {
            for(int i=0; i<r ; i++)
            {
                for(int j=0; j<c; j++)
                    temptb[i][j]=tb[i][j];
            }
        }
        if(act=='w')
            {
                moveup(r, c);
                flact=true;
            }
        if(act=='s')
            {
            movedown(r, c);
            flact=true;
            }
        if(act=='a')
            {
            moveleft(r,c);
            flact=true;
            }
        if(act=='d')
            {
            moveright(r, c);
            flact=true;
            }
        if(act=='e')
        {
            return 1;
        }
        if(!flact)
        {
            system("cls");
            cout<<"please choose one of these actions";
            continue;
        }
        random(r,c);
        system("cls");
        showmap(r, c);
        cntnu=check(r, c);
        flact=false;
    }
    cout<<"GAME OVER!";
    return 0;
    // 0 for showing that the game is over
}
void moveup(int r, int c)
{
    for(int k=0; k<r-1; k++)
    {
        for(int i=0; i<r-1; i++)
        {
            for(int j=0; j<c; j++)
            {
                if (tb[i+1][j])
                {
                    if(tb[i][j]==0)
                    {
                        tb[i][j]=tb[i+1][j];
                        tb[i+1][j]=0;
                    }
                }
            }
        }
    }
    for(int i=0; i<r-1; i++)
    {
        for (int j=0; j<c; j++)
        {
            if(tb[i][j]==tb[i+1][j])
            {
                tb[i][j]*=2;
                score+=tb[i][j];
                tb[i+1][j]=0;
            }
        }
    }
}
void movedown(int r, int c)
{
    for(int k=0; k<r-1; k++)
    {
        for(int i=r-1; i>0; i--)
        {
            for(int j=0; j<c; j++)
            {
                if(tb[i-1][j])
                {
                    if(tb[i][j]==0)
                    {
                        tb[i][j]=tb[i-1][j];
                        tb[i-1][j]=0;
                    }
                }
            }
        }
    }
    for(int i=r-1; i>0; i--)
    {
        for(int j=0; j<c; j++)
        {
            if(tb[i][j]==tb[i-1][j])
            {
                tb[i][j]*=2;
                score+=tb[i][j];
                tb[i-1][j]=0;
            }
        }
    }
}
void moveright(int r, int c)
{
    for(int k=0; k<c-1; k++)
    {
        for(int j=c-1; j>0; j--)
        {
            for(int i=0; i<r; i++)
            {
                if(tb[i][j-1])
                {
                    if(tb[i][j]==0)
                    {
                        tb[i][j]=tb[i][j-1];
                        tb[i][j-1]=0;
                    }
                }
            }
        }
    }
    for(int j=c-1; j>0; j--)
    {
        for(int i=0; i<r; i++)
        {
            if(tb[i][j]==tb[i][j-1])
            {
                tb[i][j]*=2;
                score+=tb[i][j];
                tb[i][j-1]=0;
            }
        }
    }
}
void moveleft(int r, int c)
{
    for(int k=0; k<c-1; k++)
    {
        for(int j=0; j<c-1; j++)
        {
            for(int i=0; i<r; i++)
            {
                if(tb[i][j+1])
                {
                    if(tb[i][j]==0)
                    {
                        tb[i][j]=tb[i][j+1];
                        tb[i][j+1]=0;
                    }
                }
            }
        }
    }
    for(int j=0; j<c-1; j++)
    {
        for(int i=0; i<r; i++)
        {
            if(tb[i][j]==tb[i][j+1])
            {
                tb[i][j]*=2;
                score+=tb[i][j];
                tb[i][j+1]=0;
            }
        }
    }
}
void random(int r, int c)
{
    int i, j;
    i=rand()%r;
    j=rand()%c;
    if(tb[i][j]==0)
        tb[i][j]=2;
    else
        random(r, c);
}
int check(int r, int c)
{
    for(int i=0; i<r; ++i)
        for(int j=0; j<c; ++j)
        {
            if(tb[i][j]==2048)
                cout<<"\a yeeeeah you won the 2048! \n you can continue your game anyway \n";
        }
    for(int i=0; i<r; ++i)
        for(int j=0; j<c; ++j)
        {
            if(tb[i][j]==0)
                return 1;
        }
    for(int i=0; i<r-1; ++i)
    {
        for(int j=0; j<c; ++j)
        {
            if(tb[i][j]==tb[i+1][j])
                return 1;
        }
    }
        for(int j=0; j<c-1; ++j)
        {
            for(int i=0; i<r; ++i)
            {
                if(tb[i][j]==tb[i][j+1])
                    return 1;
            }
        }
    return 0;
}
