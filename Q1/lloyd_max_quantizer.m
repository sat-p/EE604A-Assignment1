%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  EE604A : Digital Image Processing
%  Assignment 1, Question 1
%  Satya Prakash Panuganti - 14610
%  lloyd_max_quatizer.m
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [mses, q_level, q_boundary] = lloyd_max_quantizer (sorted_signal, resolution)
    
    % [mses, q_level, q_boundary] = lloyd_max_quantizer (sorted_signal, resolution). It
    % returns the MSE values at every iteration; and the final representation and
    % transition levels.
    % 
    % mses       : The MSE valus at every iteration.
    % q_level    : The representation levels (2^resolution levels)
    % q_boundary : The transition levels ((2^resolution) + 1 levels)
    %
    % signal     : Typical signal for which quantization is to be performed.
    % resolution : log_2 (Number of representation levels)
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    convergence_threshold = 1e-7;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    num_levels = 2 ^ resolution;
    
    sorted_signal = sort (signal);
    
    lower_bound = sorted_signal (1);
    upper_bound = sorted_signal (end);
    
    init_q_width = (upper_bound - lower_bound) / num_levels;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    q_level = zeros (1, num_levels);
    q_boundary = lower_bound : init_q_width : upper_bound;
    num_values = length (sorted_signal);

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % The Lloyd-Max Quantization Algorithm
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    it = 1;
    mse = 0;
 
    while true

        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Calculation of Quantization levels
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        signal_idx = 1;
        
        for idx = 1 : num_levels
            
            n = 0;
            sum = 0;

            while (signal_idx <= num_values && ...
                   sorted_signal (signal_idx) < q_boundary (idx + 1))
                
                sum = sum + sorted_signal (signal_idx);
                
                n = n + 1;
                signal_idx = signal_idx + 1;
            end
            
            % Update Quantization value if there are signal points
            % lying within Quantization boundaries.
            if (n)
                mean = sum / n;
                q_level (idx) = mean;
            elseif (~q_level (idx))
                % Set quantization value to the middle of the
                % quantization boundaries if there are not points
                % belonging to this quatization level
                q_level (idx) = (q_boundary (idx) + q_boundary (idx + 1)) / 2;
            end
        end

        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Calculation of MSE
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        signal_idx = 1;        
        sum_se = 0;

        for idx = 1 : num_levels
            while (signal_idx <= num_values && ...
                    sorted_signal (signal_idx) < q_boundary (idx + 1))
                
                diff = sorted_signal (signal_idx) - q_level (idx);
                sum_se = sum_se + diff * diff;
                
                signal_idx = signal_idx + 1;
            end
        end

        mse_ = sum_se / num_values;
        mses (it) = mse_;
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Checking for convergence.
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        if (abs (mse_ - mse) < convergence_threshold)
            break;
        else
            mse = mse_;
        end
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Updation of Quantization boundaries for next iteration
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        idx = 2;
        while idx <= num_levels
            q_boundary (idx) = (q_level (idx - 1) + q_level (idx)) / 2;
            
            idx = idx + 1;
        end
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        it = it + 1;
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%