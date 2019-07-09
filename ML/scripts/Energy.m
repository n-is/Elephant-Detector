% Apply Parseval's Theorem to calculate the
% instantaeneous energy(power) of the input signal

function [pars] = Energy(in, win_sz, roll_factor)
% Gives the instantaneous energy (power) of the
% signal according to the win_sz and the roll_factor

    roll_sz = floor(win_sz * roll_factor);
    
    n = length(in);
    pars = zeros(size(in));
    
    % Make 'n' a multiple of window size
    n = win_sz * floor(n / win_sz);
    
    for i = 1:roll_sz:(n - win_sz)
        x = in(i : i+win_sz);
        
        y = fft(x);     % Apply Fast Fourier Transform
        amp = abs(y);   % Get coefficients after transformation

        % Calculate Power using Parseval's Theorem
        % E = sum |X(f)|^2
        % P = (1 / N) * E
        pars(i) = amp' * amp / win_sz;
        
    end

end
