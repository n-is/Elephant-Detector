N = 1200;
Fs = 200;
Fp = 20;
Ap = 0.01;
Ast = 100;

Rp  = (10^(Ap/20) - 1)/(10^(Ap/20) + 1);
Rst = 10^(-Ast/20);

NUM = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge');
% fvtool(NUM,'Fs',Fs)

LP_FIR = dsp.FIRFilter('Numerator',NUM);

d = Accel_x(1:10000);
x = d;
n = length(x);
dt = 1/Fs;
t = (0:n-1)/Fs;

y = fft(x);
f = (0:n-1)*(Fs/n);
amp = abs(y);

figure
subplot(2,1,1);
plot(f(1:floor(n/2)),amp(1:floor(n/2)));
title('Before Filter');

x = LP_FIR(d);
% sound(x,Fs);

y = fft(x);
f = (0:n-1)*(Fs/n);
amp = abs(y);

subplot(2,1,2);
plot(f(1:floor(n/2)),amp(1:floor(n/2)));
title('After Filter');


figure
subplot(2,1,1);
plot(t, d);
ylim([-1,1]);
subplot(2,1,2);
plot(t,x);
ylim([-1,1]);