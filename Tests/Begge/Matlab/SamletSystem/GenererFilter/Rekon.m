function sysRekon = Rekon()

omega0 = 2*pi*1400;
QLP = 1/sqrt(2);
numLP = [omega0^2];
denLP = [1 (omega0/QLP) omega0^2];
sysLP = tf(numLP,denLP);

R = 16000;
C = 1e-6;
numHP = [R*C 0];
denHP = [R*C 1];

sysHP = tf(numHP, denHP)


sysRekon = sysLP*sysHP

end