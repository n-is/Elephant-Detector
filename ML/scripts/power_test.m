n = 2000;
t = Timestamp - Timestamp(1);
t = t(1:n);

ax_off = mean(Accel_x(1:1000));

Ax = Accel_x - ax_off;

Ax = Ax(1:n);

Ax_P = Power(Ax, 32, 0.1);

subplot(2,1,1);
plot(t, Ax);
title('Accelerometer Signal');
xlabel('time');
ylabel('Accelerometer Readings');

subplot(2,1,2);
plot(t, Ax_P);
title("Accelerometer Signal's Power");
xlabel('time');
ylabel('Power');