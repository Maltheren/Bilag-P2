function [magnitude,phase] = SimModel(Model, f_test)
[mag, phase,  wout] = bode(Model, f_test*2*pi);
magnitude = 20*log10(reshape(mag, [], 1));
phase = reshape(phase, [], 1);
end