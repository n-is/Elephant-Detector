data = Accel_x(2:10001);

off = mean(data);
data = data - off;

Ts = Timestamp(2:10001);
t = Ts - Ts(1);
Fs = 400;

num_samples = 64;

n = length(data);
num_window = floor(n / num_samples);

if (num_window > 10000)
    num_window = 10000;
end

E = zeros(2*num_window, 1);

for i = 1:(2*num_window - 1)
    num = (i-1)*(num_samples/2) + 1;
    d = data(num: num + (num_samples-1));

    num_d = length(d);
    
    y = fft(d);
    amp = abs(y);
    if (amp < 0.01)
        amp = 0;
    end
    E(i, 1) = amp' * amp;
end

y = fft(data);
P2 = abs(y/n);
P1 = P2(1:n/2+1);
P1(2:end-1) = 2*P1(2:end-1);
P1(abs(P1) < 0.001) = 0;

f = Fs*(0:(n/2))/n;
plot(f,P1)
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')

figure
plot(t, data);

figure
plot(E);
