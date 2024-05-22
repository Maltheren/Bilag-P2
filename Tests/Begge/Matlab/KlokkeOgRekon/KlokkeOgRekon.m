
clc;
clear all;

tf_klokkeRekon = readmatrix("SamletH_Efter_Rekon.txt");
addpath('GenererFilter\');



f_Meas = tf_klokkeRekon(:,1);
A_Meas = tf_klokkeRekon(:,3);

model_Klokke = H_Klokke();
model_Rekon = Rekon();
model_Generel = Generel();
model_Lunge = Lunge();
model_S1S2 = S1S2();
%setoptions(model_Klokke, 'FreqUnits', 'Hz', 'PhaseVisible', 'off')

p = bodeoptions('cstprefs');
p.FreqUnits = 'Hz';
p.Phasevisible = 'off';
p.YLim = {[-50 10]};
%p.XLim = {[0, 1000]};

s_ZOH=tf('s');
Ts=1.05e-4; %replace with desired value
%sys=(1-e(-s*Ts))/s
ZOH=(1-exp(-s_ZOH*Ts))/(s_ZOH*Ts)
ZOH

%sys_ZOH = tf([(1-exp(-s_ZOH*Ts))], [(s_ZOH*Ts)])


model_total = model_Klokke*ZOH*model_Rekon





[A_model_Klokke, p_model_Klokke] = SimModel(model_total, f_Meas); %Model af klokken.

figure,semilogx(f_Meas, A_model_Klokke, f_Meas, A_Meas-2.2, "--")
grid on
ylim([-35,5])
legend('|Målt|', '|Simuleret|')
ylabel("Amplitude [dBV]")
xlabel("Frekvens [Hz]")
title("Gengivelse amplituderespons")


% create a new pair of axes inside current figure
axes('position',[.65 .175 .25 .25])
box on % put box around new pair of axes

indexOfInterest = (f_Meas > 10) & (f_Meas < 30); % range of t near perturbation
f_MeasOfInterest = f_Meas(indexOfInterest)

semilogx(f_meas(f_MeasOfInterest), A_model_Klokke(f_MeasOfInterest))

axis tight


