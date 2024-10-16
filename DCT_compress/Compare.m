function [count,aserror,xg,check]=Compare(COPY,COPY_new,N,mode)
%COMPARE 统计两个矩阵之间的失真情况并给出原图像与恢复图像的均方误差
%第四个参数大于等于1表示汉明失真，0表示绝对失真
[m,n] = size(COPY);
check = zeros(m,n);
count = 0;sum = 0;value = 0;xg = 0;
for i = 1:m
    for j = 1:n
        value = value + double(COPY(i,j));
        abs_error = double(abs(COPY(i,j) - COPY_new(i,j)));
        sum = sum +abs_error^2;
        if mode >= 1 && COPY(i,j)~= COPY_new(i,j)    %当两个像素值之间距离大于等于1时判定为汉明失真
            count = count + 1;
            check(i,j) = 1;
        end
        if mode == 0
            count = count + abs_error;
        end
    end
end
Ave = value/n^2;
for i = 1:m
    for j = 1:n
        xg = (double(COPY(i,j))-Ave)^2 + xg;        
    end
end
xg = xg/n^2;
aserror = sum/(n*n);
fprintf('当分块大小为%d*%d时，原图像与恢复图像的均方误差为%.02f ,',N,N,aserror);
d = count/(m*n);
if mode == 0
    fprintf('图像的绝对失真度为%d\n',N,N,count);
end
if mode >=1
    fprintf('图像的汉明失真度为%d，相对汉明失真度为%.02f%%\n',count,d*100);
end
end

