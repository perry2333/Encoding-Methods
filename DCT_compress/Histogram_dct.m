function  Histogram_dct(cdata)
%统计灰度图像灰度直方图
[row,col] = size(cdata);%将矩阵cdata的行赋值为row,列赋值为col
list = zeros(row*col,1);
k=0;
for i=1:row:row*col
    k=k+1;
    list(i:i+row-1,1) = cdata(:,k);
end
%画灰度直方图，将列下标[1,256]即灰度值，映射到[0,255]
figure,
histogram(list)
axis([-255 255 0 30000])
end
