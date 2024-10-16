function [rate,count,aserror,xg,grayNum_rec,grayNum,COPY,COPY_recover,check]=main(N)
%% 读取图片
%clear;
[COPY,map]=imread('goodgoodman.bmp');
COPY = double(COPY);
COPY_new = COPY;
fl = fopen('compress_data.txt','w');
[m,n] = size(COPY);
%N = [4 8 16 32 64 128 256];                                          %可修改N为4,8,16,32,64,128,256；
%% 分块量化过程
for i_ = 1: N : m-N+1                                                                     
    for j_ = 1 : N : n-N+1
        A = COPY(i_:i_+N-1,j_:j_+N-1);          %分块读取
        [A_dct,A_num] = Dct(A);                 %对分块进行离散余弦变换，并进行量化
        COPY_dct(i_:i_+N-1,j_:j_+N-1) = A_dct;  %保留余弦变换后的图片
        COPY_num(i_:i_+N-1,j_:j_+N-1) = A_num;  %保留量化后的图片
      
    end
end
%% 对量化后的矩阵进行压缩和解压,输出解压后的数据，并输出压缩比                                                                                            
  [COPY_out,rate]=Compress(COPY_num,N);                                              
%% 恢复原图片过程
for i_ = 1: N : m-N+1                                                                   
    for j_ = 1 : N : n-N+1
        A_out = COPY_out(i_:i_+N-1,j_:j_+N-1);   %分块读取
        [A_undct,A_unnum] = UnDct(A_out);        %对量化后的矩阵进行限失真复原
        COPY_recover(i_:i_+N-1,j_:j_+N-1) = A_undct; %将复原后的数据填成新的矩阵COPY_new
    end
end
fprintf('使用的离散余弦变换矩阵为\n');disp(dctmtx(N));
%% 输出为灰度图像
% B = ones(256,256);
map1 = gray(256);
imwrite(uint8(COPY),map1,'result_cameraman_gray.bmp');
% imwrite(uint8(B),map1,'testing0.bmp');
% imwrite(uint8(2*B),map1,'testing1.bmp');
% imwrite(uint8(20*B),map1,'testing2.bmp');
% imwrite(uint8(200*B),map1,'testing3.bmp');
imwrite(uint8(COPY_recover),map1,'result_n.bmp');
imwrite(uint8(COPY_dct),map1,'result_dct_n.bmp');
imwrite(uint8(COPY_num),map1,'result_num_n.bmp');
%% 统计失真度以及相关图像绘制
[count,aserror,xg,check]=Compare(COPY,COPY_recover,N,1);                 
grayNum_rec = Histogram(COPY_recover);
grayNum = Histogram(COPY);
Histogram_dct(COPY_dct);