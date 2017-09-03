%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  EE604A : Digital Image Processing
%  Assignment 1, Question 1
%  Satya Prakash Panuganti - 14610
%  Q1.m
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% PARAMETERS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

MEAN = 0;
VARIANCE = 1;
L = 4;          % Number of representation levels
MIN = -10;      % Expected minimum of signal
MAX = 10;       % Expected maximum of signal

%% Generating signal with required mean and variance %%%%%%%%%%%

std_dev = sqrt (VARIANCE);
pdf = @(x) normal (x, MEAN, VARIANCE);

%% Calling Lloyd-Max Quantizer %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[mses, q_level, q_boundary] = lloyd_max_quantizer_function (pdf,...
                                                            L,...
                                                            MAX,...
                                                            MIN,...
                                                            true);

%% Output %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                                                   
%% The Representation levels

disp ('The Representation levels are :');
disp (q_level);

%% The Transition levels

disp ('The Transition levels are :');
disp (q_boundary);

%% The MSE values

% disp ('The Mean Square Error values are:');
% disp (mses);

%% Plotting of Mean Square Errors vs Number of iterations %%%%%%

figure;
num_it = length (mses);
x = 1 : num_it;
plot (x, mses, '-');

% Labeling the final value
text (num_it,...
      mses (num_it),...
      num2str (mses (num_it)));

% To label points other than the final one
% for it = 1 : num_it - 1
%     text (it,...
%           mses (it),...
%           num2str (mses (it)));
% end

title ('MSE vs Lloyd-Max Iterations');  
xlabel ('Number of iterations');
ylabel ('MSE');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%