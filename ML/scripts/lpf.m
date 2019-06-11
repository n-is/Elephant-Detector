% Transfer Function of RC circuit
% H = 1 / (1 + sRC)

function [out] = lpf(in, time, fc)
% Apply Discrete Low Pass Filter to data

        out = zeros(size(in));
        out(1) = in(1);
        
        RC = 1 / (2*pi*fc);
        
        for i = 2:length(in)
                dt = time(i) - time(i-1);
                alpha = dt / (RC + dt);
                
                out(i) = alpha * in(i) + (1 - alpha) * out(i-1);
        end

end