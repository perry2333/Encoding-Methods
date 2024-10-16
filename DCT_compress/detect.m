function [stop] = detect(A,B)
%DETECT 比对两个矩阵之间的偏差
%   变量是两个矩阵
[m,n] = size(A);
total = m*n;
count = 0;
stop = 0;
for i=1:m
    for j = 1:n
        if A(i,j)~=B(i,j)
            count = count + 1;
        end
    end
end
if count / total > 0.5
    stop = 1;
end

