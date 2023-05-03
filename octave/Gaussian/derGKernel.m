function k = derGKernel(sigma, o)
%
% function k = derGKernel(sigma, o)
%
% Construye un kernel (filtro) a partir de la primera o segunda derivada
% de una funcion gaussiana. El tamaño del kernel, n, se define a partir del
% parámetro sigma, se tal manera que se consideren [-3*sigma, 3*sigma] los
% límites máximo y mínimos el intervalo en el cual se va a evaluar la función.
%
% La función recibe dos parámetros:
%
% sigma: La desviación estandar que define la gaussiana.
%
% o    : Parámetro que solo debe tomar los valores 1 o 2 y que indica si se
%        va a evaluar la primera o la segunda derivada.
%
% La función regresa una arreglo unidimensional horizontal (1 renglon 
% de N columnas) que contiene la parametros del kernel.
%

	n = ceil(6 * sigma);
	if mod(n, 2) == 0
		n += 1;
	end
	c = (n+1)/2;
	k = zeros(1, n);
	if o == 1
		k(c) = 0;
		j = c-1;
		x = 0.5;
		for i = c+1:n
			k(i) = 0.5 *(derGaussian(x, sigma, 1) + derGaussian(x + 1, sigma, 1));
			k(j) = -k(i);
			j -= 1;
			x += 1;
		end
	else
		if o == 2
			k(c) = (derGaussian(0,sigma,2)+derGaussian(0.5, sigma, 2))/2;
			j = c-1;
			x = 0.5;
			for i = c+1:n
				k(i) = 0.5 *(derGaussian(x, sigma, 2) + derGaussian(x + 1, sigma, 2));
				k(j) = k(i);
				j -= 1;
				x += 1;
			end
		end
	end
end
