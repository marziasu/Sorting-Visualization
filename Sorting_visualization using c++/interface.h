#include <graphics.h>
#include <bits/stdc++.h>

using namespace std;

class Field
{
public:
    int left, top, right, bottom, bgColor,fcolor;
    char *title;

    Field()
    {
        bgColor = WHITE;
    }

    Field(int left, int top, int right, int bottom, int bgColor, char* title)
    {
        visible(left, top, right, bottom, bgColor, title);
    }
    void visible(int left, int top, int right, int bottom, int bgColor, char* title)
    {
        this -> left = left;
        this -> top = top;
        this -> right = right;
        this -> bottom = bottom;
        this -> bgColor = bgColor;
        this -> title = title;
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, bgColor);
        bar(left, top, right, bottom);
        rectangle(left, top, right, bottom);
        setcolor(WHITE);
        setbkcolor(bgColor);
        outtextxy((left+right)/2-textwidth(title)/2, (bottom+top)/2-textheight("A")/2, title);
    }
    bool cursor()
    {
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(GetForegroundWindow(), &p);
        if(p.x >= left && p.x<=right && p.y>=top && p.y<=bottom) return true;
        return false;
    }
};

class Input : public Field
{
private:
    int x, y;
public:
    Input()
    {
    }
    Input(int left, int top, int right, int bottom)
    {
        visible(left, top, right, bottom);
        setfillstyle(SOLID_FILL,15);
        rectangle(left,top,right,bottom);
        floodfill(left+2,top+2,WHITE);
    }
    void visible(int left, int top, int right, int bottom)
    {
        Field::visible(left, top, right, bottom, WHITE, "");
        x = left + 3;
        y = (top+bottom)/2 - textheight("A")/2;
    }
    void sleep()
    {
        for (int c = 1; c <= 12760; c++)
        {
            if(kbhit() || !cursor()) return;
            for(int d = 1; d <= 2276; d++)
                if(kbhit()) return;
        }
    }
    void warning(char *text)
    {
        int td = textwidth(text) / 2;
        int th = textheight("A")/2;
        setbkcolor(3);
        setcolor(RED);
        outtextxy(600 - td, 100 - th, text);
        delay(1300);
        setcolor(3);
        outtextxy(600 - td, 100 - th, text);
        setcolor(WHITE);
    }
    void showCursor(char* data, int color)
    {
        double tw;
        tw = textwidth(data);
        setcolor(color);
        outtextxy(x + tw, y, "|");
    }
    char getText(char *data)
    {
        setbkcolor(WHITE);
        int idx = strlen(data);

        setcolor(BLACK);
        outtextxy(x, y, data);

        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if(idx && ch == 8) // 8=backspace
                {
                    setcolor(BLACK);
                    outtextxy(x, y, data);
                    showCursor(data, WHITE);
                    idx--; //element delete
                }
                else if(ch >= 48  && ch <= 57 || ch==32)
                {
                    data[idx++] = ch;
                    data[idx] = 0;
                    if(left + textwidth(data) + textwidth("|") >= right - 3){
                        idx--;//If true that means Input Area is overflow
                        warning("Box is full!");
                    }
                    setbkcolor(WHITE);

                }
                else if(ch == 9 || ch == 13)//9 = tab, 13 = enter key
                {
                    showCursor(data, WHITE);
                    return 9;
                }
                data[idx] = 0;
                setcolor(BLACK);
                outtextxy(x, y, data);
            }
            else if(!cursor())
            {
                showCursor(data, WHITE);
                return 0;
            }
            showCursor(data, BLACK);
            sleep();
            showCursor(data, WHITE);
            sleep();
        }
    }
};

class Button : public Field
{
private:
    bool flag;
public:

    Button() {}
    Button(int left, int top, int right, int bottom, int bgColor, char* title)
        :Field(left, top, right, bottom, bgColor, title)
    {
        flag = false;
    }
    void hover(int color)
    {
        if(cursor() && !flag)
            new Field(left, top, right, bottom, color, title), flag = true;
        else if(!cursor() && flag)
            new Field(left, top, right, bottom, bgColor, title), flag = false;
    }

};
class Animate
{
private:
    vector<int>arr;
    int len,flag=0;
public:
    Animate(vector<int>arry)
    {
        arr=arry;
        len=arr.size();
    }

    void drawCircle(int x,int y,int a)
    {
        char c[len];

        setfillstyle(SOLID_FILL,9);
        circle(x,y,30);
        floodfill(x,y,15);
        setcolor(WHITE);
        setbkcolor(9); //textbk
        sprintf(c,"%d",a);
        outtextxy(x-textwidth(c)/2,y-textheight(c)/2,c);
        setbkcolor(3);
    }
    void removeCircle(int x,int y,int a)
    {
        char c[len];

        setfillstyle(SOLID_FILL,3);
        circle(x,y,30);
        floodfill(x,y,3);
        setcolor(3);
        setbkcolor(3); //textbk
        sprintf(c,"%d",a);
        outtextxy(x-textwidth(c)/2,y-textheight(c)/2,c);
        setbkcolor(3);
        setcolor(15);
    }
    void bubble_sort()
    {
        outtextxy(50,100,"Bubble sort......");
        int x=0,y=250,i,j;
        for( i=0;i<len;i++){
            x=x+70;
            drawCircle(x,y,arr[i]);
            delay(700);
        }
        //x=20;
         setbkcolor(3);
        for(j=0;j<len;j++){
            x=0;
            int tmp;
            for(i=0;i<len-j-1;i++){
                setbkcolor(3);
                x=x+70;
                tmp=x;
                setbkcolor(3);
                setcolor(WHITE);
                outtextxy(x-textwidth("?")/2,200-textheight("?")/2,"?");
                outtextxy((x+70)-textwidth("?")/2,200-textheight("?")/2,"?");
                delay(1500);
                if(arr[i]>arr[i+1]){
                    for(int pos=x;pos<=x+70;pos++){
                        drawCircle(x+70,y,arr[i+1]);
                        drawCircle(pos,y,arr[i]);
                        delay(20);
                        if(pos!=x+70) removeCircle(pos,y,arr[i]),setbkcolor(3);
                        else removeCircle(x+70,y,arr[i+1]);
                    }
                    setbkcolor(3);
                    for(int pos=x+70-1;pos>=x;pos--){
                        drawCircle(pos,y,arr[i+1]);
                        drawCircle(x+70,y,arr[i]);
                        delay(20);
                        if(pos!=x) removeCircle(pos,y, arr[i+1]);

                    }
                    int temp;
                    temp=arr[i],arr[i]=arr[i+1],arr[i+1]=temp,flag=1;
                }
                else{
                    drawCircle(x,y,arr[i]);
                    drawCircle(x+70,y,arr[i+1]);
                }
                setbkcolor(3);
                setcolor(3);
                outtextxy(x-textwidth("?")/2,200-textheight("?")/2,"?");
                outtextxy((x+70)-textwidth("?")/2,200-textheight("?")/2,"?");
                delay(700);
            }
            setbkcolor(3);
            setcolor(15);
            outtextxy((tmp+70)-textwidth("*")/2,200-textheight("*")/2,"*");
            delay(500);
        }

        outtextxy((x+70)-textwidth("*")/2,200-textheight("*")/2,"*");
        setbkcolor(3);
    }

    ///selection sort
    void selection_sort()
    {
        outtextxy(50,100,"Selection sort......");
        int x=0,y=250,i,j;
        for( i=0;i<len;i++){
            x=x+70;
            drawCircle(x,y,arr[i]);
            delay(700);
        }
        setbkcolor(3);
        int a=0;
        for(j=0;j<len-1;j++){
            a=a+70;
            int tmp,x1=a;
            for(i=j+1;i<len;i++){
                setbkcolor(3);
                x1=x1+70;
                setbkcolor(3);
                setcolor(WHITE);
                outtextxy(a-textwidth("M")/2,200-textheight("M")/2,"M");
                outtextxy(x1-textwidth("?")/2,200-textheight("?")/2,"?");
                delay(1500);
                if(arr[j]>arr[i]){
                        //forward flow
                    for(int pos=a,y;pos<=x1;pos++){
                        drawCircle(x1,250,arr[i]);
                        if(pos==a){
                            for(y=250;y<320;y++) drawCircle(pos,y,arr[j]),delay(1),removeCircle(pos,y,arr[j]),setbkcolor(3);
                        }
                        else if(pos!=x1) drawCircle(pos,y,arr[j]),removeCircle(pos,y,arr[j]),setbkcolor(3);
                        else if(pos==x1){
                           for(y=270;y>=250;y--){
                                if(y==250) removeCircle(x1,y,arr[i]),drawCircle(pos,y,arr[j]),delay(10);
                                else drawCircle(pos,y,arr[j]),delay(1),removeCircle(pos,y,arr[j]),setbkcolor(3);
                           }
                        }
                    }
                    delay(500);
                    setbkcolor(3);
                  //reverse flow
                    for(int pos=x1-1;pos>=a;pos--){
                        drawCircle(x1,250,arr[j]);
                        if(pos==(x1-1)){
                                for(y=250;y<320;y++) drawCircle(x1,250,arr[j]),drawCircle(pos,y,arr[i]),delay(1),removeCircle(pos,y,arr[i]),setbkcolor(3);
                        }
                        else if(pos!=a) drawCircle(pos,y,arr[i]),removeCircle(pos,y,arr[i]),setbkcolor(3);
                        else {
                           for(y=270;y>=250;y--){
                                if(y==250) drawCircle(pos,y,arr[i]),delay(10);
                                else drawCircle(pos,y,arr[i]),delay(1),removeCircle(pos,y,arr[i]),setbkcolor(3);
                           }
                        }
                    }
                    int temp;
                    temp=arr[j],arr[j]=arr[i],arr[i]=temp,flag=1;
                }
                else{
                    drawCircle(a,y,arr[j]);
                    drawCircle(x1,y,arr[i]);
                }
                setbkcolor(3);
                setcolor(3);
                outtextxy(a-textwidth("M")/2,200-textheight("M")/2,"M");
                outtextxy(x1-textwidth("?")/2,200-textheight("?")/2,"?");
                delay(700);
            }
            setbkcolor(3);
            delay(500);
        }
        setbkcolor(3);

    }
    void redCircle(int x,int y,int a)
    {
        char c[len];
        setcolor(4);
        setfillstyle(SOLID_FILL,4);
        circle(x,y,30);
        floodfill(x,y,4);
        setcolor(WHITE);
        setbkcolor(4); //textbk
        sprintf(c,"%d",a);
        outtextxy(x-textwidth(c)/2,y-textheight(c)/2,c);
        setbkcolor(3);
    }
    void remove_redCircle(int x,int y,int a)
    {
        char c[len];
        setcolor(3);
        setfillstyle(SOLID_FILL,3);
        circle(x,y,30);
        floodfill(x,y,3);
        //setcolor(3);
        setbkcolor(3); //textbk
        sprintf(c,"%d",a);
        outtextxy(x-textwidth(c)/2,y-textheight(c)/2,c);
        setbkcolor(3);

    }
    //quick sorting
    void sorting(int low,int high,int x,int x1)
    {

        if(low<high){
            //create_partition
            int pivot=arr[high];
            redCircle(70*(high+1),250,pivot),delay(1500);

            int j,i=low-1,tmp,t;//x=0,x1=0;
            for(j=low;j<high;j++){

                x=x+70;
                if(arr[j]<pivot){

                    x1=x1+70,i++;
                    if(x1!=x){
                        for(int pos=x1;pos<=x;pos++){
                            int y1;
                            if(pos==x1) for(y1=250;y1<320;y1++) drawCircle(pos,y1,arr[i]),delay(2),removeCircle(pos,y1,arr[i]),setbkcolor(3);
                            else if(pos!=x) drawCircle(pos,y1,arr[i]),removeCircle(pos,y1,arr[i]),setbkcolor(3);
                            else {
                                for(y1=320;y1>=250;y1--){
                                    drawCircle(pos,250,arr[j]);
                                    if(y1==250) drawCircle(pos,y1,arr[i]),delay(2);
                                    else drawCircle(pos,y1,arr[i]),delay(2),removeCircle(pos,y1,arr[i]),setbkcolor(3);
                                }

                            }
                        }
                        for(int pos=x;pos>=x1;pos--){
                            int y1;
                            if(pos==x) for(y1=250;y1<320;y1++) drawCircle(pos,250,arr[i]),drawCircle(pos,y1,arr[j]),delay(1),removeCircle(pos,y1,arr[j]),setbkcolor(3);
                            else if(pos!=x1) drawCircle(pos,y1,arr[j]),removeCircle(pos,y1,arr[j]),setbkcolor(3);
                            else {
                                for(y1=320;y1>250;y1--) drawCircle(pos,y1,arr[j]),delay(1),removeCircle(pos,y1,arr[j]),setbkcolor(3);
                                drawCircle(pos,250,arr[j]);
                            }
                        }
                   }
                    t=arr[i],arr[i]=arr[j],arr[j]=t;
                }
            }

            //pivot exchange
            if(high!=i+1){
                for(int pos=x1+70;pos<=x+70;pos++){
                    int y1;
                    if(pos==x1+70) for(y1=250;y1<320;y1++) drawCircle(pos,y1,arr[i+1]),delay(1),removeCircle(pos,y1,arr[i+1]),setbkcolor(3);
                    else if(pos!=(x+70)) drawCircle(pos,y1,arr[i+1]),removeCircle(pos,y1,arr[i+1]),setbkcolor(3);
                    else {
                        for(y1=320;y1>=250;y1--){
                            redCircle(pos,250,arr[high]);
                            if(y1==250) redCircle(pos,y1,arr[i+1]),delay(10);
                            else drawCircle(pos,y1,arr[i+1]),delay(1),removeCircle(pos,y1,arr[i+1]),setbkcolor(3);
                        }
                        //drawCircle(pos,250,arr[i+1]);
                    }
                }
                //pivot moving
                for(int pos=x+70;pos>=x1+70;pos--){
                    int y1;
                    if(pos==x+70) for(y1=250;y1<320;y1++) drawCircle(pos,250,arr[i+1]),redCircle(pos,y1,arr[high]),delay(1),removeCircle(pos,y1,arr[high]),setbkcolor(3);
                    else if(pos!=(x1+70)) redCircle(pos,y1,arr[high]),remove_redCircle(pos,y1,arr[high]),setbkcolor(3);
                    else {
                        for(y1=320;y1>=250;y1--){
                            if(y1!=250) redCircle(pos,y1,arr[high]),delay(1),remove_redCircle(pos,y1,arr[high]),setbkcolor(3);
                            else redCircle(pos,250,arr[high]);
                        }

                    }
                }
            }
            delay(1000);
            tmp=arr[high],arr[high]=arr[i+1],arr[i+1]=tmp;
            int p=i+1;
            //left and right side sort after partition

            sorting(low,p-1,0,0);
            low=p+1;
            sorting(low,high,x1+70,x1+70);
        }


    }
    void quick_sort()
    {
        outtextxy(50,100,"Quick sort......");
        int x=0,y=250,i,j;
        for( i=0;i<len;i++){
            x=x+70;
            drawCircle(x,y,arr[i]);
            delay(700);
        }
        setbkcolor(3);
        int low=0;
        int high=len-1;
        sorting(low,high,0,0);

        for(int i=0;i<len;i++){
            cout<<arr[i]<<" "<<endl;
        }

    }
    //insertion sort
    void insertion_sort()
    {
        outtextxy(50,100,"Insertion sort......");
        int x=0,y=250,i,j,key,tmp;
        for( i=0;i<len;i++){
            x=x+70;
            drawCircle(x,y,arr[i]);
            delay(700);
        }
        x=70;
        setbkcolor(3);
        for( i=1;i<len;i++){
            x=x+70;
            tmp=x;
            key=arr[i];
            j=i-1;
            int pos=x;

            setbkcolor(3);
            setcolor(WHITE);
            outtextxy(x-textwidth("?")/2,200-textheight("?")/2,"?");

            for(y=250;y<320;y++) drawCircle(x,y,key), delay(3),removeCircle(x,y,key);
            drawCircle(x,y,key);
            while(j>=0 && arr[j]>key){
                    pos=pos-70;
                    for(int p=pos;p<=pos+70;p++){
                            if(p==pos+70) drawCircle(p,250,arr[j]),delay(3);
                            else drawCircle(p,250,arr[j]),delay(3),removeCircle(p,250,arr[j]),delay(3);
                    }
                    arr[j+1]=arr[j],j--;

            }

                //key transfer
            for(tmp;tmp>=pos;tmp--){
                if(tmp!=pos) drawCircle(tmp,y,key),delay(1),removeCircle(tmp,y,key);
                else if(tmp==(pos)){
                    for(y;y>=250;y--){
                        if(y!=250) drawCircle(tmp,y,key),delay(3),removeCircle(tmp,y,key);
                        else drawCircle(tmp,y,key);
                    }
                }
            }
            setbkcolor(3);
            setcolor(3);
            outtextxy(x-textwidth("?")/2,200-textheight("?")/2,"?");
            delay(500);

            arr[j+1]=key;

        }
    }
    int root1[2],root2[2],root3[2],root4[2],root5[2],root6[2],root7[2],root8[2],root9 [2];
    void draw_left_line(int root,int &x,int &y){
        int tx,ty,x2,y2;
        if(root==3||root==5 ){
            tx=x-30+10,x2=tx-30+8;
            ty=y+10+13, y2=ty+20+13;
        }
        else if(root==7 || root==9){
            tx=x-30+15,x2=tx-30+23;
            ty=y+10+20, y2=ty+20+15;
        }
        else{
            tx=x-30,x2=tx-70;
            ty=y+12, y2=ty+30;
        }
        line(tx,ty,x2,y2);
        x=x2;y=y2;
    }
    int left_leaf(int root,int x,int y)
    {
        int tx,ty;
        draw_left_line(root,x,y);

        if(root==9){
            tx=x-20; ty=y+18;
            drawCircle(tx,ty,arr[root]);
        }
        else{
            tx=x-23 ; ty=y+15;
            drawCircle(tx,ty,arr[root]);
        }

        if(root==1){ root1[0]=tx; root1[1]=ty;}
        else if(root==3){ root3[0]=tx; root3[1]=ty;}
        else if(root==5){ root5[0]=tx; root5[1]=ty;}
        else if(root==7){ root7[0]=tx; root7[1]=ty;}
        else if(root==9){ root9[0]=tx; root9[1]=ty;}

        delay(1000);
        return tx;
    }
    void draw_Right_line(int root,int &x,int &y){
        int tx,ty,x2,y2;
        if(root==4||root==6){
            tx=x+28-10,x2=tx+30-5;
            ty=y+10+13, y2=ty+20+13;
        }
        else if(root==8){
            tx=x,x2=tx+4;
            ty=y+10+24, y2=ty+20+15;
        }
        else{
            tx=x+28,x2=tx+70;
            ty=y+10, y2=ty+30;
        }
        line(tx,ty,x2,y2);
        x=x2;y=y2;
    }
    int right_leaf(int root,int x,int y)
    {
        int tx,ty;
        draw_Right_line(root,x,y);

        tx=x+23; ty=y+15;
        drawCircle(tx,ty,arr[root]);

        if(root==2){ root2[0]=tx; root2[1]=ty;}
        else if(root==4){ root4[0]=tx; root4[1]=ty;}
        else if(root==6){ root6[0]=tx; root6[1]=ty;}
        else if(root==8){ root8[0]=tx; root8[1]=ty;}

        delay(1000);
        return tx;

    }
    int* find_idxArray(int i){
        int* root=new int[2];
        if(i==9){
            root[0]=root9[0]; root[1]=root9[1];
        }
        else if(i==8){
            root[0]=root8[0]; root[1]=root8[1];
        }
        else if(i==7){
            root[0]=root7[0]; root[1]=root7[1];
        }
        else if(i==6){
            root[0]=root6[0]; root[1]=root6[1];
        }
        else if(i==5){
            root[0]=root5[0]; root[1]=root5[1];
        }
        else if(i==4){
            root[0]=root4[0]; root[1]=root4[1];
        }
        else if(i==3){
            root[0]=root3[0]; root[1]=root3[1];
        }
        else if(i==2){
            root[0]=root2[0]; root[1]=root2[1];
        }
        else if(i==1){
            root[0]=root1[0]; root[1]=root1[1];
        }
        else if(i==0){ root[0]=330;root[1]=250;}
        return root;
    }
    void heapify(int n,int i){

        int large=i;

        int l=2*i+1, r=2*i+2;

        if(l<n && arr[large]<arr[l]) large=l;
        if(r<n && arr[large]<arr[r]) large=r;

        int* leaf;
        int* root=find_idxArray(i);
        if(large!=i){
            leaf=find_idxArray(large);
            if(large==l){ //left side swap
                if(i==0){ //For 1st element
                    for(int x=leaf[0],y=leaf[1];x<=root[0],y>=root[1] ;x+=2,y--){

                        drawCircle(root[0],root[1],arr[i]);
                        drawCircle(x,y,arr[large]);
                        delay(20);
                        if(x!=root[0] && y!=root[1]) removeCircle(x,y,arr[large]),setbkcolor(3);
                        else removeCircle(root[0],root[1],arr[i]);

                    }
                    delay(100);
                    //reverse
                    for(int x=root[0]+1,y=root[1];x>=leaf[0],y<=leaf[1] ;x-=2,y++){
                        drawCircle(root[0],root[1],arr[large]);
                        drawCircle(x,y,arr[i]);

                        delay(20);
                        if(x!=leaf[0] && y!=leaf[1]) removeCircle(x,y,arr[i]),setbkcolor(3);


                    }

                }
                else{
                    if(large==9){ //for left side 9th element
                        for(int x=leaf[0],y=leaf[1];x<=root[0],y>=root[1] ;x++,y-=2){
                            drawCircle(root[0],root[1],arr[i]);
                            drawCircle(x,y,arr[large]);
                            delay(20);
                            if(x!=root[0] && y!=root[1]) removeCircle(x,y,arr[large]),setbkcolor(3);
                            else removeCircle(root[0],root[1],arr[i]);
                        }
                        delay(100);
                        //root reverse
                        for(int x=root[0],y=root[1];x>=leaf[0],y<=leaf[1] ;x-=0.5,y+=3){
                            drawCircle(root[0],root[1],arr[large]);
                            drawCircle(x,y,arr[i]);

                            delay(20);
                            if(x!=leaf[0] && y!=leaf[1]) removeCircle(x,y,arr[i]),setbkcolor(3),drawCircle(x,y,arr[i]);

                        }

                    }
                    else{ //for left all element without 1st and 9th
                        for(int x=leaf[0],y=leaf[1];x<=root[0],y>=root[1] ;x+=1.5,y-=2){
                            drawCircle(root[0],root[1],arr[i]);
                            drawCircle(x,y,arr[large]);
                            delay(20);
                            if(x!=root[0] && y!=root[1]) removeCircle(x,y,arr[large]),setbkcolor(3);
                            else removeCircle(root[0],root[1],arr[i]);
                        }
                        delay(100);
                        //root reverse

                        for(int x=root[0],y=root[1];x>=leaf[0],y<=leaf[1] ;x-=2.3,y+=3.5){
                            drawCircle(root[0],root[1],arr[large]);
                            drawCircle(x,y,arr[i]);

                            delay(20);
                            if(x!=leaf[0] && y!=leaf[1]) removeCircle(x,y,arr[i]),setbkcolor(3),drawCircle(x,y,arr[i]);

                        }

                    }
                }
            }
            else if(large==r){
                if(i==0){ //for 1st
                    for(int x=leaf[0],y=leaf[1];x>=root[0],y>=root[1] ;x-=2,y--){
                        drawCircle(root[0],root[1],arr[i]);
                        drawCircle(x,y,arr[large]);
                        delay(20);

                        if(x!=root[0] && y!=root[1]) removeCircle(x,y,arr[large]),setbkcolor(3),drawCircle(x,y,arr[i]);
                        else removeCircle(root[0],root[1],arr[i]);
                    }
                    delay(100);
                    for(int x=root[0]+1,y=root[1];x>=leaf[0],y<=leaf[1] ;x+=2,y++){
                        drawCircle(root[0],root[1],arr[large]);
                        drawCircle(x,y,arr[i]);

                        delay(20);
                        if(x!=leaf[0] && y!=leaf[1]) removeCircle(x,y,arr[i]),setbkcolor(3);
                    }
                }
                else if(large==8){
                    for(int x=leaf[0],y=leaf[1];x>=root[0]+10,y>=root[1] ;x--,y-=3){
                        drawCircle(root[0],root[1],arr[i]);
                        drawCircle(x,y,arr[large]);
                        delay(20);

                        if(x!=root[0] && y!=root[1]) removeCircle(x,y,arr[large]),setbkcolor(3);
                        else removeCircle(root[0],root[1],arr[i]);
                    }
                    delay(100);
                    //reverse
                    for(int x=root[0]+1,y=root[1];x>=leaf[0],y<=leaf[1] ;x++,y+=3){
                        drawCircle(root[0],root[1],arr[large]);
                        drawCircle(x,y,arr[i]);

                        delay(20);
                        if(x!=leaf[0] && y!=leaf[1]) removeCircle(x,y,arr[i]),setbkcolor(3);
                    }
                    flag=1;

                }

                else{ //all without 1st and 8th
                    for(int x=leaf[0],y=leaf[1];x>=root[0],y>=root[1] ;x--,y--){
                        drawCircle(root[0],root[1],arr[i]);
                        drawCircle(x,y,arr[large]);
                        delay(10);

                        if(x!=root[0] && y!=root[1]) removeCircle(x,y,arr[large]),setbkcolor(3);
                        else removeCircle(root[0],root[1],arr[i]);
                    }
                    delay(100);
                    //reverse
                    for(int x=root[0]+1,y=root[1];x>=leaf[0],y<=leaf[1] ;x++,y++){
                        drawCircle(root[0],root[1],arr[large]);
                        drawCircle(x,y,arr[i]);

                        delay(10);
                        if(x!=leaf[0] && y!=leaf[1]) removeCircle(x,y,arr[i]),setbkcolor(3);

                    }

                }
            }
            line(root[0],root[1],leaf[0],leaf[1]);
            swap(arr[i],arr[large]);
            delay(1000);
            heapify(n,large);

        }

    }
    void heap_sort()
    {
        outtextxy(10,200,"Heap sort..");
        int x=330,y=250;
        int n=len;
        drawCircle(x,y,arr[0]);
        int a1,a2,j;

        queue<int> x1;
        x1.push(x);

    //create tree
        for(int i=1,j=1;i<=n/2;i++,j++){
            int idx=2*i;
            if(i==2) y=y+52;
            else if(i==4) y=y+50+15;

            if(idx<=n){
                a1=left_leaf(idx-1,x1.front(),y);
                x1.push(a1);
            }
            if(idx+1<=n){
                a2=right_leaf(idx,x1.front(),y);
                x1.push(a2);
            }
            x1.pop();
        }
        //sorting process
        for(int val=n/2 ;val>=0;val--){
            heapify(n,val);
        }
        delay(100);

        int px,py,temp=750,d=0,a=5;
        for(int j=n-1;j>=0;j--){
                //for root deleting from tree
            if(temp>391){
                for(py=250;py>=130;py--){
                    if(py!=130) drawCircle(330,py,arr[0]),delay(1),removeCircle(330,py,arr[0]);
                }
                for(px=330;px<=(750-d);px++){
                    if(px!=750-d) drawCircle(px,py,arr[0]),removeCircle(px,py,arr[0]);
                    else{ drawCircle(px,py,arr[0]);}
                    temp=px;
                }
            }
            else if(temp<=391){
                temp-=60;
                for(py=250;py>=230;py--){
                    if(py!=230) drawCircle(330,py,arr[0]),delay(1),removeCircle(330,py,arr[0]);
                    else{
                        for(px=330;px>=temp-a;px--){
                            if(px!=temp-a) drawCircle(px,py,arr[0]),delay(1),removeCircle(px,py,arr[0]);
                            else{
                                for(py;py>=130;py--){
                                    if(py!=130) drawCircle(px,py,arr[0]),delay(1),removeCircle(px,py,arr[0]);
                                    else drawCircle(px,py,arr[0]);
                                }
                                px=temp-a;
                            }
                        }
                        py=230;
                    }
                }
                a+=3;

            }
            d+=60;
            //swaping
            if(j!=0){
                int* xy=find_idxArray(j);
                px=xy[0];

                for(py=xy[1];py<=xy[1]+70;py++) if(py!=xy[1]+70) drawCircle(px,py,arr[j]),delay(1),removeCircle(px,py,arr[j]);
                for(px;px<=600;px++){
                    if(px!=600) drawCircle(px,py,arr[j]),removeCircle(px,py,arr[j]);
                    else{
                       for(py;py>=220;py--) {
                            if(py!=220) drawCircle(px,py,arr[j]),delay(1),removeCircle(px,py,arr[j]);
                            else{
                                for(px;px>=330;px--){
                                    if(px!=330) drawCircle(px,py,arr[j]),removeCircle(px,py,arr[j]);
                                    else{
                                        for(py;py<=250;py++){
                                            if(py!=250) drawCircle(px,py,arr[j]),delay(1),removeCircle(px,py,arr[j]);
                                            else{ drawCircle(px,py,arr[j]); }
                                       }
                                    }
                                }
                                py=220;
                            }
                       }
                       px=600;
                    }
                }
                delay(100);
                swap(arr[0],arr[j]);
                arr[len--];
                heapify(len,0);

            }

        }
        delay(1000);
    }

};

