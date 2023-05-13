function [val] = derGaussian(x, sigma, n)
%
% function [val] = derGaussian(x, sigma, n)
%
% Esta funcion evalua y regresa las derivadas (primera y segunda),
% de una funcion Gaussiana centrada en el origen:
%
%         dG(x,s)/dx =  (-x./(sqrt(2*pi)*s^3))*exp(-0.5*x.^2/s^2)
%
%         d2G(x,s)/dx2 =  (1/sqrt(2*pi))*(x^2./s^5)-1/s.^3)*exp(-0.5(x.^2/s^2)
%
% La funcion recibe tres parámetros:
%
% x    : Un escalar un arreglo que contiene los valores en los cuales se va
%        a evaluar la funcion.
%
% sigma: La desviación estandar que define la gaussiana.
%
% n    : Parámetro que solo debe tomar los valores 1 o 2 y que indica si se
%        va a evaluar la primera o la segunda derivada. 
%
% La funcion regresa un valor escalar o un arreglo que contiene la función
% evauada en el parámetro X. si sigma es menor o igual a 0 se regresa nan.

	if sigma <= 0
		val = nan;
		return;
	end

 if n == 1
		val = -(x./(sqrt(2*pi)*sigma.^3)).*exp(-0.5*(x.^2/sigma.^2));
 else
 	if n == 2
		val = ((x.^2/sigma^5)-1/(sigma^3)).*(exp(-0.5*x.^2/(2*sigma))/sqrt(2*pi));
	end
 end
end
