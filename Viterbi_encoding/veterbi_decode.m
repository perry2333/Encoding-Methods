close all;clear all;
%卷积编码器的子生成元g1=111,g2=101  %通过翻转码字实现了子生成元的交换
%x为输入的待译码序列
x=importdata('encode_data.txt');%长度不限，只需要长度为偶数
x=reverse(x);
a=size(x);       %输入序列的长度
s=a(2)/2;        %译码后的m序列长度为x的一半
m=zeros(1,s);     %最终结果存放
ma=zeros(1,s);  
mb=zeros(1,s);  
mc=zeros(1,s);  
md=zeros(1,s);  %存放路径
tempma=zeros(1,s);
tempmb=zeros(1,s);
tempmc=zeros(1,s);
tempmd=zeros(1,s);%每个时刻的最小路径值

out=zeros(1,2*s);%最终编码输出
outa=zeros(1,2*s);
outb=zeros(1,2*s);
outc=zeros(1,2*s);
outd=zeros(1,2*s);%存放编码输出
tempouta=zeros(1,2*s);
tempoutb=zeros(1,2*s);
tempoutc=zeros(1,2*s);
tempoutd=zeros(1,2*s);%%储存每个时刻最小路径对应的编码输出
Fa=0;
Fb=0;
Fc=0;
Fd=0;%累计汉明距离
for i=1:s
    if i==1 
        d0=dis(x(1),x(2),0,0);%0-->00-->00 编码器输出00 0+0+0=0 0+0=0
        d3=dis(x(1),x(2),1,1);%1-->10-->00 编码器输出00 1+0+0=1 1+0=1
        
        Fa=Fa+d0;
        Fb=Fb+d3;
        
        ma(i)=0;
        mb(i)=0;%注意这里并不是真正对应当前的源码，而是考虑到i=2时候的整体源码输入
        mc(i)=1;
        md(i)=1;
        
        outa(2*i-1)=0; outa(2*i)=0;
        outb(2*i-1)=0; outb(2*i)=0;
        outc(2*i-1)=1; outc(2*i)=1;
        outd(2*i-1)=1; outd(2*i)=1;
        continue;
    elseif i==2 
        d0=dis(x(3),x(4),0,0);%d0=1
        d1=dis(x(3),x(4),0,1);%d1=2
        d2=dis(x(3),x(4),1,0);%d2=0
        d3=dis(x(3),x(4),1,1);%d3=1
        
        %注意下面的顺序，不能错，否则会产生数据相关，要么加中间变量。
        Fc=Fb+d2;   %0-->10-->01 0+1+0=1(高位) 0+0=0（低位） 编码器输出为：10
        Fd=Fb+d1;   %1-->10-->11 1+1+0=0 1+0=1 编码器出书为：01
        Fb=Fa+d3;
        Fa=Fa+d0;   
        
        ma(i)=0;
        mb(i)=1;
        mc(i)=0;
        md(i)=1;
        
        outa(2*i-1)=0; outa(2*i)=0;
        outb(2*i-1)=1; outb(2*i)=1;
        outc(2*i-1)=1; outc(2*i)=0;
        outd(2*i-1)=0; outd(2*i)=1;
        continue; 
    elseif i>2
        d0=dis(x(2*i-1),x(2*i),0,0);
        d1=dis(x(2*i-1),x(2*i),0,1);
        d2=dis(x(2*i-1),x(2*i),1,0);
        d3=dis(x(2*i-1),x(2*i),1,1);
        %下面开始进行加比较选，选F值小的路径
        tempa=Fa;
        tempb=Fb;
        tempc=Fc;
        tempd=Fd;
        if Fa+d0<Fc+d3 %到达00状态的两条路径比较大小
            tempa=Fa+d0; %0-->00-->00 编码器输出00 0+0+0=0 0+0=0
            tempma=ma;
            tempma(i)=0;
            tempouta=outa;
            tempouta(2*i-1)=0;
            tempouta(2*i)=0;
        else
            tempa=Fc+d3;%0-->01-->00 编码器输出11  0+0+1=1 0+1=1
            tempma=mc;
            tempma(i)=0;
            tempouta=outc;
            tempouta(2*i-1)=1;
            tempouta(2*i)=1;
        end
        
        if Fa+d3<Fc+d0 %到达10状态的两条路径比较大小
            tempb=Fa+d3;%1-->00-->10 编码器输出11  1+0+0=1 1+0=1
            tempmb=ma;
            tempmb(i)=1;
            tempoutb=outa;
            tempoutb(2*i-1)=1;
            tempoutb(2*i)=1;
        else
            tempb=Fc+d0;%1-->01-->10 编码器输出00  1+0+1=0 1+1=0
            tempmb=mc;
            tempmb(i)=1;
            tempoutb=outc;
            tempoutb(2*i-1)=0;
            tempoutb(2*i)=0;
        end
        
        if Fb+d2<Fd+d1 %到达01状态的两条路径比较大小
            tempc=Fb+d2;%0-->10-->01  编码器输出10  0+1+0=1 0+0=0  
            tempmc=mb;
            tempmc(i)=0;
            tempoutc=outb;
            tempoutc(2*i-1)=1;
            tempoutc(2*i)=0;
        else
            tempc=Fd+d1;%0-->11-->01  编码器输出01  0+1+1=0 0+1=1
            tempmc=md;
            tempmc(i)=0;
            tempoutc=outd;
            tempoutc(2*i-1)=0;
            tempoutc(2*i)=1;
        end
        
        if Fb+d1<Fd+d2 %到达11状态的两条路径比较大小
            tempd=Fb+d1;%1-->10-->11 编码器输出01  1+1+0=0 1+0=1
            tempmd=mb;
            tempmd(i)=1;
            tempoutd=outb;
            tempoutd(2*i-1)=0;
            tempoutd(2*i)=1;
        else
            tempd=Fd+d2;%1-->11-->11 编码器输出10  1+1+1=1 1+1=0
            tempmd=md;
            tempmd(i)=1;
            tempoutd=outd;
            tempoutd(2*i-1)=1;
            tempoutd(2*i)=0;
        end
        Fa=tempa;
        Fb=tempb;
        Fc=tempc;
        Fd=tempd;
        
        ma=tempma;
        mb=tempmb;
        mc=tempmc;
        md=tempmd;
        
        outa=tempouta;
        outb=tempoutb;
        outc=tempoutc;
        outd=tempoutd;
    end
end


temp=min([Fa,Fb,Fc,Fd]);
if temp==Fa
    F=Fa
    m=ma
    x%再显示一遍接收数据x，便于和下面的进行对比
    out=outa
elseif temp==Fb
    F=Fb
    m=mb
    x%再显示一遍接收数据x，便于和下面的进行对比
    out=outb
elseif temp==Fc
    F=Fc
    m=mc
    x%再显示一遍接收数据x，便于和下面的进行对比
    out=outc
else
    F=Fd
    m=md
    x%再显示一遍接收数据x，便于和下面的进行对比
    out=outd
end 

%向result文件中输出译码结果
fid=fopen('result.txt','w');

fprintf(fid,'%d ',m);

fclose(fid);
