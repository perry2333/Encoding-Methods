function [y] = reverse(x)
length = size(x);
for i = 1:2:length(2)
    y(i)=x(i+1);
    y(i+1)=x(i);
end
end

