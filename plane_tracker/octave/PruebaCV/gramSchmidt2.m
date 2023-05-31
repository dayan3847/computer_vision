function [H] = gramSchmidt2(H)
c1 = H(:,1);
c2 = H(:,2);
c2=c2-dot(c2,c1)*c1;
c2/=norm(c2);
H(:,2) = c2;
end
