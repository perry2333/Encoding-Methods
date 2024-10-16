function [B] = matric_interp(A)
[m,~] = size(A);
B = zeros(2*m,2*m);
for i = 1:m
    for  j = 1:m
        B(2*i,2*j) = A(i,j);
    end
end
B(:,1) = B(:,2);
B(:,2) = 0;
for i = 1:m
    p = [B(2*i,1) B(2*i,4:2:2*m)];
    x = [1 4:2:2*m];
    x_ = [1:2*m];
    l = interp1(x,p,x_);
    B(2*i,:) =l;
end
B(1,:) = B(2,:);
B(2,:) = zeros(1,2*m);
for i = 1:2*m
    p = [B(1,i);B(4:2:2*m,i)];
    x = [1 4:2:2*m];
    x_ = [1:2*m];
    l = interp1(x,p',x_);
    B(:,i) =l';
end