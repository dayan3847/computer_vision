function [val] = gaussian(x, miu, sigma)
%
% function [val] = gaussian(miu, sigma)
%
%
	if sigma == 0
		val = nan;
		return;
	end

	fact = 1./(sqrt(2*pi)*sigma);
	val = fact*exp(-0.5 * (x-miu).^2 /(sigma*sigma));
end

