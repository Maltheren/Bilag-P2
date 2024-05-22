function sysKlokke = H_Klokke()

C1 = 1e-6;
R1 = 200e3;

sys_Filter1 = tf([R1*C1 0], [R1*C1 1]);

omega0 = 2*pi*1400;
QLP = 1/sqrt(2);
numLP = [omega0^2];
denLP = [1 (omega0/QLP) omega0^2];
sys_Filter2 = tf(numLP,denLP);

C2 = 1e-6;
R_par = 1/((1/178e3)+(1/(49.9e3+23.5e3)));

sys_Filter3 = tf([C2*R_par 0], [C2*R_par 1]);

sysKlokke = sys_Filter1 * sys_Filter2 * sys_Filter3

end