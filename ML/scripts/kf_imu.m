function [out] = kf_imu(abs_data, rel_data, t)

    n = length(abs_data);
    out = zeros(n, 1);
    x = [abs_data(1); 0];

    P = [10, 0; 0, 10];
    Q = [0.001, 0; 0, 0.003];
    R = 0.04;

    H = [1, 0];
    
    out(1) = x(1,1);

    for i = 2:n
        u = rel_data(i);
        z = abs_data(i);

        dt = t(i) - t(i-1);
        A = [1 -dt; 0 1];
        B = [dt; 0];

        x = A * x + B * u;
        P = A * P * A' + Q;

        K = (P * H') / (H * P * H' + R);

        x = x + K * (z - H * x);
        P = (eye(2) - K * H) * P;
        
        out(i) = x(1,1);

    end


end

