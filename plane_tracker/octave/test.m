
originalCornersM = load("./../tests/data/originalCornersM.txt")
originalCornersM_t = originalCornersM'
figure(1);
plot(originalCornersM_t(1,:), originalCornersM_t(2,:), 'o');
axis equal;

%% Cargar la matrix H de un fichero de texto
%H = load('./../tests/data/f1/H_2_orthogonalized.txt');
%H
