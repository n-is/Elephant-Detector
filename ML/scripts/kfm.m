gx_off = mean(Gyro_x(1:1000));
Gx = Gyro_x - gx_off;
t = Timestamp - Timestamp(1);

n = 2000;
Fs = 400;

Gx = Gx(1:n);
Ax = Accel_x(1:n);
t = t(1:n);

Gx = Gx / max(Gx);

x = fft(Gx);
f = (0:n-1)*(Fs/n);
amp = abs(x);

figure
subplot(2,1,1);
stem(f(1:floor(n/2)),amp(1:floor(n/2)), 'Marker', '.');
ylim([0,15]);
title('Spectral Analysis Before Filter');
xlabel('Frequency');
ylabel('Magnitude');

order = 20;
Gx_f = tust_lpf_n(Gx, t, 100, order);

y = fft(Gx_f);
f = (0:n-1)*(Fs/n);
amp = abs(y);

y = abs(x) .* abs(y);

subplot(2,1,2);
stem(f(1:floor(n/2)),amp(1:floor(n/2)), 'Marker', '.');
ylim([0,15]);

title('Spectral Analysis After Filter');
xlabel('Frequency');
ylabel('Magnitude');

len_data = 50;

figure
subplot(2,1,1);
plot(t(1:len_data), Gx(1:len_data));
xlabel('Time');
ylabel('Unfiltered Gx');
title('Raw Data');
subplot(2,1,2);
plot(t(1:len_data), Gx_f(1:len_data));
xlabel('Time');
ylabel('Filtered Gx');
title('Filtered Data');

