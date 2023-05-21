function M = GramSchmidt(M)
%
% function M = GramSchmidt(M)
%
% Esta función realiza la ortonormalización de Gram-Schmidt sobre el
% conjunto de vectores que definen una matrices de tamaño 3x3.
%
% Parametros:
%
% M : Una matriz que se espera que sea ortonormal, e.g. una matriz de 
%     rotación en 3D. Cada columna de esta matriz es uno de los vectores
%     que se va a ortonormalizar
%
% Regresa una matriz de tamaño 3x3 cuyas columnas son ortonomales
%
   v1=M(:,1);
   v2=M(:,2);
   v3=M(:,3);
   u1 = v1;
   u2 = v2 - proj(u1, v2);
   u3 = v3 - proj(u1, v3)-proj(u2, v3);
   M=[u1/norm(u1), u2/norm(u2), u3/norm(u3)];
end
