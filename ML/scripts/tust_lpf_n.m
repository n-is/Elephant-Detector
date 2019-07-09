function [out] = tust_lpf_n(in, time, fc, n)
% Performs Low Pass Filtering of 'n' order

    out = in;
    mx = 1;
    for i = 1:n
        mx = max(out);
        out = out / mx;
        out = tust_lpf(out, time, fc);
        out = out * mx;
    end
    out = out / mx;
    out = out * max(in);

end
