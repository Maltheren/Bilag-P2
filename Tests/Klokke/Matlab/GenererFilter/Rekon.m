function sysRekon = Rekon()

omega0 = 2*pi*1400;
QLP = 1/sqrt(2);
numLP = [omega0^2];
denLP = [1 (omega0/QLP) omega0^2];
sysLP = tf(numLP,denLP);


sysRekon = sysLP

end