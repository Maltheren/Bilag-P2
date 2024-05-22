function sysS1S2 = S1S2()

omega0 = 2*pi*150;
QLP = 1/sqrt(2);
numLP = [omega0^2];
denLP = [1 (omega0/QLP) omega0^2]
sysLP = tf(numLP,denLP);

omegaHP= 2*pi*20;
QHP = 1/sqrt(2);
numHP = [1 0 0];
denHP = [1 (omegaHP/QHP) omegaHP^2];
sysHP = tf(numHP,denHP);

sysS1S2 = sysLP*sysHP
end