function [y] = dis(x1,x2,x3,x4)
%计算两个码长为2的码字的汉明距离
     y = 0;
     if x1~=x3
         y = y+1;
     end
     if x2~=x4
         y= y+1;
     end
end

