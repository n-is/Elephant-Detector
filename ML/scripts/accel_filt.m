n = 2000;
t = Timestamp - Timestamp(1);
t = t(1:n);

ax_off = mean(Accel_x(1:1000));
ay_off = mean(Accel_y(1:1000));
az_off = mean(Accel_z(1:1000));

Ax = Accel_x - ax_off;
Ay = Accel_y - ay_off;
Az = Accel_z - az_off;

Ax = Ax(1:n);
Ay = Ay(1:n);
Az = Az(1:n);

order = 20;

Ax_F = tust_lpf_n(Ax, t, 100, order);
Ay_F = tust_lpf_n(Ay, t, 100, order);
Az_F = tust_lpf_n(Az, t, 100, order);
