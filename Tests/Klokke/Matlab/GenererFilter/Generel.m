function sysLYD = Generel()

QLP = 1/sqrt(2);
QHP = 1/sqrt(2);
omegaHP= 2*pi*20;

omegaLPLYD = 2*pi*1000;
numLPLYD = [omegaLPLYD^2];
denLPLYD = [1 (omegaLPLYD/QLP) omegaLPLYD^2];
sysLPLYD = tf(numLPLYD,denLPLYD);

numHPLYD = [1 0 0];
denHPLYD = [1 (omegaHP/QHP) omegaHP^2];
sysHPLYD = tf(numHPLYD,denHPLYD);

sysLYD = sysLPLYD*sysHPLYD

end