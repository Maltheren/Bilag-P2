function syslung = Lunge()
QLP = 1/sqrt(2);
QHP = 1/sqrt(2);

omegaLPlung = 2*pi*700;
numLPlung = [omegaLPlung^2];
denLPlung = [1 (omegaLPlung/QLP) omegaLPlung^2];
sysLPlung = tf(numLPlung,denLPlung);

omegaHPlung = 2*pi*200;
numHPlung = [1 0 0];
denHPlung = [1 (omegaHPlung/QHP) omegaHPlung^2];
sysHPlung = tf(numHPlung,denHPlung);

syslung = sysHPlung*sysLPlung

end