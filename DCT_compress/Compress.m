
function [A_OUT,r] = Compress(A_dct,N)
[M,M]=size(A_dct);
counter_s=0;

for i_ = 1: N : M-N+1                                                                     
    for j_ = 1 : N : M-N+1
        counter_s=counter_s+1;
        A = A_dct(i_:i_+N-1,j_:j_+N-1)          %分块读取

     [m,n]=size(A); 
     k=m*n;
     
     counter=0;
     for i=2:m+1
         for j=1:i-1
             counter=counter+1;
             str(1,counter)=A(i-j,j);
         end   
     end %录入左上三角阵
     
     for i=(m+2):(m+m)
         for j=(i-m):m
             counter=counter+1;
             str(1,counter)=A(i-j,j);
         end 
     end
    %   disp('录入矩阵=');disp(str);
    [Statistics]=tabulate(str);
    %   disp(Statistics);
    [num,~]=size(Statistics);
%-----------------------矩阵录入部分结束---------------------------%
    
 for i=1:num
    dic(1,i)=Statistics(i,1);
    pos(1,i)=Statistics(i,3)/100;
 end
    
if(num==1)
%     disp('全x矩阵,x=');disp(dic(1,1));
    encstr=str;
    j=1;
    out=[1];
    [~,length] = size(encstr);
    for z=1:1:(length-1) %行程编码程序段
        if encstr(1,z)==encstr(1,z+1)
           out(j)=out(j)+1;
        else
          data(j)=encstr(1,z); % data(j)代表相应的像素数据
          j=j+1;
          out(j)=1;
        end
    end
    data(j)=encstr(1,length); %最后一个像素数据赋给 data

  %  disp('out=');disp(out);           %out为游程编码的结果

    [~,outlength]=size(out);
    %out:游程编码结果 A：原矩阵
    z1=0;
    for a=1:m
        for b=1:n
%             disp(A(a,b));
            if(A(a,b)<=-100&&A(a,b)>=-999) z1=z1+4; end
            if(A(a,b)<=-10&&A(a,b)>=-99) z1=z1+3; end
            if(A(a,b)<=-1&&A(a,b)>=-9) z1=z1+2; end
            if(A(a,b)<=9&&A(a,b)>=0) z1=z1+1; end
            if(A(a,b)<=99&&A(a,b)>=10) z1=z1+2; end
            if(A(a,b)<=999&&A(a,b)>=100) z1=z1+3; end
            if(A(a,b)<=9999&&A(a,b)>=1000) z1=z1+2; end
        end
    end
    
    z2=0;
    for a=1:outlength
        if (out(1,a)<=9&&out(1,a)>=0) z2=z2+1; end
        if (out(1,a)<=99&&out(1,a)>=10) z2=z2+2; end
        if (out(1,a)<=999&&out(1,a)>=100) z2=z2+3; end
        if (out(1,a)<=9999&&out(1,a)>=1000) z2=z2+4; end
    end
%     disp(z1);
%     disp(z2);
    rate=z1/z2;
 %   disp('压缩比=');disp(rate);       %rate为压缩比

    l=1;
    for m=1:outlength
        for n=1:1:out(m);
            decode(l)=data(m);
            l=l+1;
        end
    end
 %   disp('游程编码解码=');disp(decode);%decode为游程解码的结果
    deco=decode;
end

%-----------------------处理全0阵结束------------------------% 


if(num>1) %不是全0阵
   sum_pos=sum(pos);
   if(sum_pos~=1)
       [~,l]=size(pos);
       max_num=1;
       for s=1:l
          if(pos(1,s)>pos(1,max_num))
            max_num=s;
          end
       end
       pos(1,max_num)=pos(1,max_num)+1-sum_pos;
   end
   
%   [dict,~] = huffmandict(dic, pos) ;
%   encstr = huffmanenco(str,dict);
   encstr=str;
%   disp('Huffman编码=');disp(encstr);  %encstr为Huffman编码结果
   
   j=1;
    out=[1];
    [~,length] = size(encstr);
    for z=1:1:(length-1) %行程编码程序段
        if encstr(1,z)==encstr(1,z+1)
           out(j)=out(j)+1;
        else
          data(j)=encstr(1,z); % data(j)代表相应的像素数据
          j=j+1;
          out(j)=1;
        end
    end
    data(j)=encstr(1,length); %最后一个像素数据赋给 data
 
    [~,outlength]=size(out);
    
    z1=0;
    for a=1:m
        for b=1:n
            disp(A(a,b));
            if(A(a,b)<=-100&&A(a,b)>=-999) z1=z1+4; end
            if(A(a,b)<=-10&&A(a,b)>=-99) z1=z1+3; end
            if(A(a,b)<=-1&&A(a,b)>=-9) z1=z1+2; end
            if(A(a,b)<=9&&A(a,b)>=0) z1=z1+1; end
            if(A(a,b)<=99&&A(a,b)>=10) z1=z1+2; end
            if(A(a,b)<=999&&A(a,b)>=100) z1=z1+3; end
            if(A(a,b)<=9999&&A(a,b)>=1000) z1=z1+2; end
        end
    end
    
    z2=0;
    for a=1:outlength
        if (out(1,a)<=9&&out(1,a)>=0) z2=z2+1; end
        if (out(1,a)<=99&&out(1,a)>=10) z2=z2+2; end
        if (out(1,a)<=999&&out(1,a)>=100) z2=z2+3; end
        if (out(1,a)<=9999&&out(1,a)>=1000) z2=z2+4; end
    end
    out=out
    rate=z1/z2;
%     disp(z1);
%     disp(z2);
    
 if(rate>=1)
    l=1;
    for m=1:outlength
        for n=1:1:out(m);
            decode(l)=data(m);
            l=l+1;
        end
    end
 %   disp('游程编码解码=');disp(decode);%decode为游程解码的结果
     deco=decode;
%     deco = huffmandeco(decode, dict);
%    disp('Huffman解码=');disp(deco);  %deco为Huffman解码的结果
 end
    
 if(rate<=1)
%     disp('压缩比=1'); %矩阵不适合压缩编码，不再编码，解编码数组等于原数组
     rate=1;
     deco=str;
 end
  
   
end
%-----------------------处理非全0阵结束------------------------% 
   
%     disp(deco);
    
     [~,m]=size(A);
     counter=0;
     for i=2:m+1
         for j=1:i-1
             if(counter<k)
             counter=counter+1;
             A_out(i-j,j)=deco(1,counter);
             end
         end   
     end %还原左上三角阵
     
     for i=(m+2):(m+m)
         for j=(i-m):m
             if(counter<k)
             counter=counter+1;
             A_out(i-j,j)=deco(1,counter);
             end
         end 
     end %还原右下角矩阵
     A_OUT = A_dct;
 %   disp('还原矩阵=');disp(A_out);
    A_out=reshape(A_out,m,m);
%-----------------------矩阵还原结束------------------------% 
    
    r_(counter_s,1)=1/rate;
    end
end


    r=0;
    for i =1:counter_s
        r=r+r_(counter_s,1);
    end    
    
    r=counter_s/r;
    
end
  