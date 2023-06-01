function[] = plotAxis(R, T, mag, lw, colors)
%
% function[] = plotAxis(R, T, mag, lw, colors)
%
% Esta función grafica en la figura actual el marco de referencia de un sistema de
% coordenadas situado en las coordenadas almacenadas en el vector T y cuya
% orientación esta descrita por la matriz de rotación R. Por defecto el marco de
% referencia si dibuja como tres lineas ortonormales de con colores rojo, verde y
% azul.
%
% La función puede recibir tres parámetros opcionales que definen respectivamente la
% magnitud de las lineas que representan los vectores (por defecto el valor es igual
% a 1), el ancho de las lineas que representan los vectores (por defecto el valor es
% igual a 0.5) y los colores que se van a utilizar para dibujar cada una de las
% lineas que representan los vectores (valor por defecto: 'r', 'g' y 'b').
%


   if nargin < 5
      colors=['r', 'g', 'b'];
      if nargin < 4
         lw = 0.5;
         if nargin < 3
            mag = 1;
         end
      end
   end
   R *= mag;
   vx = T + R(:, 1);
   vy = T + R(:, 2);
   vz = T + R(:, 3);
   lx = line ([T(1),vx(1)],[T(2),vx(2)],[T(3),vx(3)]);
   set(lx,'color',colors(1));
   set(lx,'linewidth',lw);

   ly = line ([T(1),vy(1)],[T(2),vy(2)],[T(3),vy(3)]);
   set(ly,'color',colors(2));
   set(ly,'linewidth',lw);

   lz = line ([T(1),vz(1)],[T(2),vz(2)],[T(3),vz(3)]);
   set(lz,'color',colors(3));
   set(lz,'linewidth',lw);
   vx=vx';
   vy=vy';
   vz=vz';

end
