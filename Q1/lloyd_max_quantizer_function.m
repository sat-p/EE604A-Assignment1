%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  EE604A : Digital Image Processing
%  Assignment 1, Question 1
%  Satya Prakash Panuganti - 14610
%  lloyd_max_quatizer.m
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [mses, q_level, q_boundary] = lloyd_max_quantizer_function (pdf, levels, max, min, isInf)
    % [mses, q_level, q_boundary] = lloyd_max_quantizer_function (pdf, levels, max, min).
    % It returns the MSE values at every iteration; and the final representation
    % and transition levels.
    % 
    % mses       : The MSE valus at every iteration.
    % q_level    : The representation levels
    % q_boundary : The transition levels
    %
    % pdf        : The pdf of the signal
    % levels     : The number of representation levels
    % max        : The maximum value of the signal
    % min        : The minimum value of the signal
    % isInf      : Flag to set extreme transition levels to -Inf and Inf
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    CONVERGENCE_THRESHOLD = 1e-20;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    lower_bound = min;
    upper_bound = max;
    
    init_q_width = (upper_bound - lower_bound) / levels;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    pdf_x = @(x) x * pdf (x);
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    q_level = zeros (1, levels);
    q_boundary = lower_bound : init_q_width : upper_bound;
    
    if (isInf)
        % Forcing the extreme transition levels to be at infinity.
        q_boundary(1) = -Inf;
        q_boundary(end) = Inf;
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % The Lloyd-Max Quantization Algorithm
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    it = 1;
    
    mse_ = 0;
    while true

        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Calculation of Quantization levels
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        for idx = 1 : levels
            denom = integral (pdf, q_boundary (idx), q_boundary (idx + 1),...
                              'ArrayValued', true);
            num = integral (pdf_x, q_boundary (idx), q_boundary (idx + 1),...
                              'ArrayValued', true);
            
            if (denom ~= 0)
                q_level (idx) = num / denom;
            else
                q_level (idx) = (q_boundary (idx) + q_boundary (idx + 1)) / 2;
            end
        end

        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Calculation of MSE
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        mse = 0;
        for idx = 1 : levels
            mse = mse + integral (@(x) (x - q_level (idx))' * (x - q_level (idx))...
                                        * pdf (x),...
                                  q_boundary (idx), q_boundary (idx + 1),...
                                  'ArrayValued', true);
        end
        
        mses (it) = mse;
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Checking for convergence.
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        if (abs (mse_ - mse) < CONVERGENCE_THRESHOLD)
            break;
        end

        mse_ = mse;
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Updation of Quantization boundaries for next iteration
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        for idx = 2 : levels
            q_boundary (idx) = (q_level (idx - 1) + q_level (idx)) / 2;            
        end
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        it = it + 1
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%