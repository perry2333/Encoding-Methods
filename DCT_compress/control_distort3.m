function [COPY_new]=control_distort3(COPY,COPY_new)
[m,n] = size(COPY);
for i = 1:m
    for j = 1:n
        if  COPY(i,j)~= COPY_new(i,j)    
            if double(COPY_new(i,j))>= 150
                COPY_new(i,j) = 163;
            
            else if double(COPY_new(i,j))<= 100
                COPY_new(i,j) = 14;
                else
                    COPY_new(i,j) = 126;
                end
            end
        end
    end
end

end
