#include "interface.h"
#include <stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>
#include<bits/stdc++.h>

using namespace std;
void homepage();
void choise();

void bTask();
void enter();

char data[50] = "";

int main()
{

    //int gd=DETECT;
    //int gm;

    initwindow(800,500);
    setbkcolor(3);
    cleardevice();
    homepage();
    _getch();

    return 0;
}
void homepage()
{
    rectangle(10,10,80,50);
    outtextxy(20,21,"Home");

    int x=150,y=100,width;
    for(int i=1;i<=8;i++){
        settextstyle(0,HORIZ_DIR,50);

        switch(i){
        case 1:
            width=textwidth("W");
            x=x+width;
            outtextxy(x,y,"W");
            break;
        case 2:
            width=textwidth("e");
            x=x+width;
            outtextxy(x,y,"e");
            break;
        case 3:
            width=textwidth("l");
            x=x+width;
            outtextxy(x,y,"l");
            break;
        case 4:
            width=textwidth("l");
            x=x+width;
            outtextxy(x,y,"l");
            break;
        case 5:
            width=textwidth("c");
            x=x+width;
            outtextxy(x,y,"c");
            break;
        case 6:
            width=textwidth("o");
            x=x+width;
            outtextxy(x,y,"o");
            break;
        case 7:
            width=textwidth("m");
            x=x+width;
            outtextxy(x,y,"m");
            break;
        case 8:
            width=textwidth("e");
            x=x+width;
            outtextxy(x,y,"e");
            break;


        }
        delay(100);
    }
    settextstyle(0,HORIZ_DIR,0);
    outtextxy(470,130,"To");
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(100,160,"DATA SORTING VISUALIZATION");

    Button start(300,400,400,450,6,"Start");
    while(1)
    {
        start.hover(8);
        if(GetAsyncKeyState(VK_LBUTTON)){
            if(start.cursor()){
               cleardevice();
               choise();
            }
        }
        setbkcolor(3);

    }
}
char check;
void choise()
{

    outtextxy(50,70,"which type of sort do you want to visualization?");
    outtextxy(50,100,"Choise one and Click that");
    settextstyle(BOLD_FONT,0,3);
    setcolor(7);
    Button B(50,150,280,180,5,"1.Bubble sort");
    Button s(350,150,580,180,5,"2.Selection sort");
    Button q(50,200,280,230,5,"3.Quick sort");
    Button i(350,200,580,230,5,"4.Insertion sort");
    //Button m(50,250,280,280,5,"5.Marge sort");
    Button h(50,250,280,280,5,"5.Heap sort");

    Button back(250,450,350,480,6,"Back");
    while(1){
        back.hover(8);
        if(GetAsyncKeyState(VK_LBUTTON)){
            if(back.cursor()) cleardevice(),homepage();
        }
        B.hover(RED);
        s.hover(RED);
        q.hover(RED);
        i.hover(RED);
        h.hover(RED);
        if(GetAsyncKeyState(VK_LBUTTON)){
            if(B.cursor()) cleardevice(),check='b',bTask();
            else if(s.cursor()) cleardevice(),check='s',bTask();
            else if(q.cursor()) cleardevice(),check='q',bTask();
            else if(i.cursor()) cleardevice(),check='i',bTask();
            else if(h.cursor()) cleardevice(),check='h',bTask();
        }

        setbkcolor(3);
    }

}

void bTask()
{
    setbkcolor(3);
    setcolor(WHITE);
    outtextxy(50,20,"Enter an array and size is less than 10: ");
    Input input(50,50,350,80);

    Button Back(721,460,790,490,6,"Back");
    //Button Next(700,460,780,490,6,"Next");
    Button enter(355,50,420,80,5,"enter");

    while(1){
        Back.hover(8);
        //Next.hover(8);
        enter.hover(4);
        if(GetAsyncKeyState(VK_LBUTTON) ){
            if(Back.cursor()) cleardevice(),choise();
            //else if(Next.cursor()) cleardevice();
            else if(input.cursor()) input.getText(data);//cout<<input.getText(data);
            else if(enter.cursor()){
                int i,j=0,len=strlen(data),flag=0;
                vector<int>arr;
                arr.push_back(0);
                for( i=0;i<strlen(data);i++){
                    if (data[i] == ' ' && data[i+1]!=' ' &&j>0 &&(i+1)!=strlen(data) ) j++,arr.push_back(0);
                    else if(data[i]!=' ') arr[j]= arr[j] * 10 + (data[i] - 48),flag=1;// subtract str[i] by 48 to convert it to int
                    else if(data[i] == ' ' && data[i+1]!=' ' && flag==1 &&(i+1)!=strlen(data)) j++,arr.push_back(0); //for 1st element
                }
                if(flag==1){
                    Animate ob(arr);
                    if(check=='b') ob.bubble_sort(),delay(5000),cleardevice(),bTask();///
                    else if(check=='s') ob.selection_sort(),delay(5000),cleardevice(),bTask();///
                    else if(check=='q') ob.quick_sort(),delay(5000),cleardevice(),bTask();
                    else if(check=='i') ob.insertion_sort(),delay(5000),cleardevice(),bTask();
                    else if(check=='h') ob.heap_sort(),delay(5000),cleardevice(),bTask();
                }
                else input.warning("Input is empty!");
                flag=0;
            }
        }
        setbkcolor(3);
        if(kbhit()) getch();
    }
}



