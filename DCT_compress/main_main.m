N = [4 8 16 32 64 128 256];
rate = zeros(1,7);
count = zeros(1,7);
aserror = zeros(1,7);
xg = zeros(1,7);
int = zeros(1,7);
n = [1:7];
H_rec = zeros(1,7);
for i = 1:7
    [rate(i),count(i),aserror(i),xg(i),grayNum_rec,grayNum]=main(N(i));
    D = count(i)/256^2;
    grayNum_rec = grayNum_rec./65536;
    for q = 1:256
        if grayNum_rec(q)~=0
           H_rec(i) = H_rec(i) - grayNum_rec(q)*log2(grayNum_rec(q));
        end
    end
    int(i)=log2(256)-D*log2(255)+D*log2(D)+(1-D)*log2(1-D);
end
H = log2(256);
display(H);
figure
plot(n,int);
title('不同分块下的最小信息传输率')
ylabel('bit/单位符号');
xlabel('分块大小/(log2(N)-1)');
figure
plot(n,H_rec);
title('不同分块下恢复图片的传输信息率')
ylabel('bit/单位符号');
xlabel('分块大小/(log2(N)-1)');
figure
plot(n,H_rec,'-',n,int,'--');
title('当前限失真传输性能与极限传输性能')
ylabel('bit/单位符号');
xlabel('分块大小/(log2(N)-1)');
legend('当前传输信息率','极限传输信息率','location','east')
figure
plot(n,8./H_rec,'-',n,8./int,'--');
title('当前压缩性能与极限压缩性能')
xlabel('分块大小/(log2(N)-1)');
legend('当前压缩比','极限压缩比','location','east')
%axis([0.5 7.5 3 4.5]);
figure
plot(n,rate);
axis([0.5 7.5 0 4]);
ylabel('压缩比');
xlabel('分块大小/(log2(N)-1)');
figure
plot(n,count/256/256,'-.');
axis([0.5 7.5 0.8 1]);
legend('平均汉明失真度','Location','SouthEast')
figure
plot(n,rate,'-',n,count/9000,'-.',n,aserror/25,'--');
legend('压缩比','汉明失真度/9000','均方误差/25','Location','SouthEast')
axis([0.5 7.5 0 4]);
ylabel('压缩比/汉明失真/均方误差');
xlabel('分块大小/(log2(N)-1)');
title('各分块折线图');