% puntos originales en metros
pom = load('data/originalCornersM.txt')';
% puntos encontrados en metros
pfm = load('data/f1/corners_found_meter.txt')';
% puntos originales en pixeles
pop = load('data/cornersOriginalPixelM.txt')';
% puntos encontrados en pixeles
pfp = load('data/f1/corners_found_pixel.txt')';

figure(1);
plot(
    pom(1,:),pom(2,:),'bo',
    pfm(1,:),pfm(2,:),'ro'
);
axis equal;
title('Puntos originales y encontrados en metros');

figure(2);
plot(
    pop(1,:),pop(2,:),'bo',
    pfp(1,:),pfp(2,:),'ro'
);
axis equal;
title('Puntos originales y encontrados en pixeles');

K = load('data/K.txt');
iK = load('data/iK.txt');
H = load('data/f1/H_2_orthogonalized.txt');
R = load('data/f1/R.txt');
T = load('data/f1/T.txt');

% Prec=[px;py;ones(size(px))];
% Pi0=[834.16687, 328.14319;
%Pi0(3,:)=ones(1,48);
%cPi0=iK*Pi0;
%H0=[1.208408224311641, -1.176047826805016, 0.5388124791340638;
% 1.141986630549475, 1.040521999712752, 0.02526322350758505;
% 0.1904691900281365, -0.2217878300537925, 1];
% mP=fixHomoPts(H0*Prec);
% H0=H0/norm(H0(:,1));
% T=H0(:,3);
% R=gramSchmidt2(H0);
% R(:,3)=cross(R(:,1),R(:,2));
%

Pp = R * pom(1:3,:) + T;

figure(3);
plot3(
    pom(1,:),pom(2,:),pom(3,:),'bo',
    Pp(1,:),Pp(2,:),Pp(3,:),'ro'
);
plotAxis(eye(3),zeros(3,1),0.1);
plotAxis(R,T,0.1);
axis equal;
title('Puntos originales y encontrados en metros en 3D');
