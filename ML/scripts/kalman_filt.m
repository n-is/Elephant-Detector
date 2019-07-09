function [out] = kalman_filt(abs_data, rel_data, time,...
    state_matrix, control_matrix, obs_matrix)
% Applies Kalman Filter to given set of absolute and relative data

    n = length(abs_data);
    out = abs_data(1,:)';
    out_n = size(out, 1);
    
    sm_c = size(state_matrix, 2);
    cm_c = size(control_matrix, 2);
    om_c = size(obs_matrix, 2);
    
    om_r = size(ons_matrix, 1);
    
    ad_c = size(abs_data, 2);
    rd_c = size(rel_data, 2);
    
    P = ((rand(sm_c).*eye(sm_c)) - 0.5) * 10000;
    Q = (rand(sm_c) .* eye(sm_c)) / 1000;
    R = (rand(om_r) .* eye(om_r)) / 100;
    
    x = [out; zeros(sm_c - ad_c, 1)];
    
    for i = 2:n
        u = [rel_data(i,:)'; zeros(cm_c - rd_c, 1)];
        z = [abs_data(i,:)'; zeros(om_c - ad_c, 1)];
        
        x = A * x + B * u;
        P = A * P * A' + Q;
        
        K = (P * H') / (H * P * H' + R);
        
        x = x + K * (z - H * x);
        P = (eye(om_c) - K * H) * P;
        
    end
    
    out = x(1:out_n, 1);

end

