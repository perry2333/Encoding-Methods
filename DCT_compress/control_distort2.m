function [COPY_new]=control_distort2(COPY,COPY_new)
[m,n] = size(COPY);
for i = 1:m
    for j = 1:n
        if  COPY(i,j)~= COPY_new(i,j)    
            if double(COPY_new(i,j))>= 125
                COPY_new(i,j) = 163;
            
            else if double(COPY_new(i,j))< 125
                COPY_new(i,j) = 14;
            end
        end
    end
end

end
