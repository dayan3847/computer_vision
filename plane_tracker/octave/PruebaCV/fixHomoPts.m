function p = fixHomoPts(p)
[r,c]= size(p);
for i=1:c
p(:,i)/=p(3,i);
end
end
