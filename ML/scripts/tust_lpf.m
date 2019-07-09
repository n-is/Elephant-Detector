% Transfer Function of RC circuit
% H = 1 / (1 + sRC)

function [out] = tust_lpf(in, time, fc)
% Apply Low Pass Filter using Tustin's Approximation

    out = zeros(size(in));
    out(1) = in(1);
    
    RC = 1 / (2*pi*fc);
    
    for i = 2:length(in)
        dt = time(i) - time(i-1);
        a = 1 / (dt + 2*RC);
        b = (2*RC - dt);
        out(i) = a * (dt * (in(i) + in(i-1)) ...
                 + b * out(i-1));
    end

end
