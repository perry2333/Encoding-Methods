function [grayNum] = Histogram(cdata)
%统计灰度图像灰度直方图
figure,imshow(cdata,gray(256)),title('限失真压缩后图像');
[row,col] = size(cdata);%将矩阵cdata的行赋值为row,列赋值为col
grayNum = zeros(1,256); %申明1行256列的数组用于存放[0;255]的像素个数
% 记录灰度值为image(i,j)像素个数
for i=1:row
    for j=1:col
            grayNum(cdata(i,j)+1) = grayNum(cdata(i,j)+1)+1;%数组的列是从1到256。而cdata(i,j)的范围是0到255，故要+1
    end
end
%画灰度直方图，将列下标[1,256]即灰度值，映射到[0,255]
figure,
bar(0:255,grayNum,'grouped');%第一个参数为横轴（即灰度值），第二个参数为纵轴（个数），第三个为直方图类型
title('当前分块下灰度直方图');
axis([-1 257 0 25000]);
end
