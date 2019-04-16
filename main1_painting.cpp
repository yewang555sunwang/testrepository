//功能：绘图测试    软件：code blocks 17.12
#include <graphics.h>  //此头文件没有要自行配置
#include <math.h>

int main()
{

    int x0=320, y0=240;
     int n=25,i,j,r=180;
     int x[50],y[50];
     int gdriver, gmode;
          gdriver=VGA;
          gmode=VGAHI;
     initgraph(&gdriver,&gmode,(char *) "");  //此函数使用自行查阅，以下同此。
     bar3d(50, 50, 150, 30, 1,1); //画三维条形
     Sleep(1000);
     cleardevice(); //清除图形屏幕
    // setbkcolor(WHITE);
    int qqq=1;
    while(qqq<15)
    {
        setbkcolor(WHITE);  //设置背景色
        if(qqq==1)setcolor(BLUE);  //可用选择语句
        if(qqq==2)setcolor(GREEN);
        if(qqq==3)setcolor(CYAN);
        if(qqq==4)setcolor(RED);
        if(qqq==5)setcolor(MAGENTA);
        if(qqq==6)setcolor(BROWN);
        if(qqq==7)setcolor(LIGHTGRAY);
        if(qqq==8)setcolor(DARKGRAY);
        if(qqq==9)setcolor(LIGHTBLUE);
        if(qqq==10)setcolor(LIGHTGREEN);
        if(qqq==11)setcolor(LIGHTCYAN);
        if(qqq==12)setcolor(LIGHTRED);
        if(qqq==13)setcolor(LIGHTMAGENTA);
        if(qqq==14)setcolor(YELLOW);
        if(qqq==9)setcolor(LIGHTBLUE);
        if(qqq==10)setcolor(LIGHTGREEN);
       // 5 - MAGENTA Ñóºì 6 - BROWN ×Ø
//7 - LIGHTGRAY µ­»Ò 8 - DARKGRAY Éî»Ò
//9 - LIGHTBLUE µ­À¼ 10 - LIGHTGREEN µ­ÂÌ
//11 - LIGHTCYAN µ­Çà 12 - LIGHTRED µ­ºì
//13 - LIGHTMAGENTA µ­Ñóºì 14 - YELLOW »Æ
     for(i=0;i<n;i++)
        {        x[i]=r*cos(2*3.1415926*i/n)+x0;        y[i]=r*sin(2*3.1415926*i/n)+y0;    }
     for(i=0;i<=n-2;i++)
           {
            for(j=i+1;j<=n-1;j++)
               line(x[i],y[i],x[j],y[j]);    }
               qqq++;
        if(qqq==15)qqq=1;
     Sleep(1000);
               //closegraph();
    }
     getch();
      closegraph();

    return 0;
}
