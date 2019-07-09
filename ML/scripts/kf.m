n = 2000;
t = Timestamp - Timestamp(1);
t = t(1:n);

gx_off = mean(Gyro_x(1:1000));
gy_off = mean(Gyro_y(1:1000));
gz_off = mean(Gyro_z(1:1000));

Gx = Gyro_x - gx_off;
Gy = Gyro_y - gy_off;
Gz = Gyro_z - gz_off;

Gx = Gx(1:n);
Gy = Gy(1:n);
Gz = Gz(1:n);
Gx_f = tust_lpf_n(Gx, t, 100, 20);
Gy_f = tust_lpf_n(Gy, t, 100, 20);
Gz_f = tust_lpf_n(Gz, t, 100, 20);

Ax = Accel_x(1:n);
Ay = Accel_y(1:n);
Az = -Accel_z(1:n);
Ax_f = tust_lpf_n(Ax, t, 100, 20);
Ay_f = tust_lpf_n(Ay, t, 100, 20);
Az_f = tust_lpf_n(Az, t, 100, 20);


roll = atan2(Ay_f, Az_f) * 57.3;
roll_u = atan2(Ay, Az) * 57.3;

roll_f = kf_imu(roll, Gx_f, t);

% subplot(3,1,1);
% plot(t, roll_u);
% ylim([-200, 200]);
% 
% subplot(3,1,2);
% plot(t, roll);
% ylim([-200, 200]);
% subplot(3,1,3);
% plot(t, roll_f);
% ylim([-200, 200]);

pitch = atan2(-Ax_f, Ay_f .* sin(roll/57.3) + Az_f .* cos(roll/57.3)) * 57.3;

pitch_f = kf_imu(pitch, Gy_f, t);

phi = roll_f(end) / 57.3;
theta = pitch_f(end) / 57.3;
psi = 0;

cphi = cos(phi);
ctheta = cos(theta);
cpsi = cos(psi);

sphi = sin(phi);
stheta = sin(theta);
spsi = sin(psi);

R = [ ctheta*cpsi, -cphi*spsi + sphi*stheta*cpsi, sphi*spsi + cphi*stheta*cpsi;
    ctheta*spsi, cphi*cpsi + sphi*stheta*spsi, -sphi*cpsi + cphi*stheta*spsi;
    -stheta, sphi*ctheta, cphi*ctheta
];

G = [0; 0; -9.81];
A = [Ax, Ay, Az];
A_cmp = R * A';
plot(t, A_cmp);
mean(A)
R * G
