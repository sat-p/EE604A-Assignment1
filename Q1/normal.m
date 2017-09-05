%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  EE604A : Digital Image Processing
%  Assignment 1, Question 1
%  Satya Prakash Panuganti - 14610
%  lloyd_max_quatizer.m
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function p = normal (x, mean, variance)
    % p = normal (x, mean, variance). It returns the value at of the
    % gaussian pdf with the provided, mean and variance.
    %
    % x         : scalar input
    % y         : scalar input
    % variance  : scalar input
    %
    % p         : scalar output
    
    INV_ROOT_2PI = 0.3989422804;
    
    diff = x - mean;
    p = exp(-diff' * diff/(2 * variance)) * INV_ROOT_2PI;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%