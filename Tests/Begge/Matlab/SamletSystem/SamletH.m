
clc;
clear all;

Samlet_generel = readmatrix("SamletH_generelt.txt");
Samlet_Lunge = readmatrix("SamletH_lunge.txt");
Samlet_S1S2 = readmatrix("SamletH_s1s2.txt");


addpath('GenererFilter\');



f_Meas_Generel = Samlet_generel(:,1);
f_Meas_Lunge = Samlet_Lunge(:,1);
f_Meas_S1S2 = Samlet_S1S2(:,1);

A_Meas_Generel = Samlet_generel(:,3);
A_Meas_Lunge = Samlet_Lunge(:,3);
A_Meas_S1S2 = Samlet_S1S2(:,3);



model_Klokke = H_Klokke();
model_Rekon = Rekon();
model_Generel = Generel();
model_Lunge = Lunge();
model_S1S2 = S1S2();

%ZOH filter model
s_ZOH=tf('s');
Ts=1.05e-4; %replace with desired value
%sys=(1-e(-s*Ts))/s
ZOH=(1-exp(-s_ZOH*Ts))/(s_ZOH*Ts)

%sys_ZOH = tf([(1-exp(-s_ZOH*Ts))], [(s_ZOH*Ts)])


model_total_generel = 0.2*model_Klokke*ZOH*model_Rekon*3*model_Generel/0.2
model_total_Lunge = 0.2*model_Klokke*ZOH*model_Rekon*3*model_Lunge/0.2
model_total_S1S2 = 0.2*model_Klokke*ZOH*model_Rekon*3*model_S1S2/0.2


[A_model_total_generel, p_model] = SimModel(model_total_generel, f_Meas_Generel);
[A_model_total_Lunge, p_model] = SimModel(model_total_Lunge, f_Meas_Lunge);
[A_model_total_S1S2, p_model] = SimModel(model_total_S1S2, f_Meas_S1S2);



semilogx(f_Meas_Generel, A_Meas_Generel, f_Meas_Generel, A_model_total_generel-12, "--")
hold on

semilogx(f_Meas_Lunge, A_Meas_Lunge, f_Meas_Lunge, A_model_total_Lunge-12, "--")

semilogx(f_Meas_S1S2, A_Meas_S1S2, f_Meas_S1S2, A_model_total_S1S2-12, "--")

hold off

grid on
ylim([-35,5])
legend('|Målt|', '|Simuleret|')
ylabel("Amplitude [dBV]")
xlabel("Frekvens [Hz]")
x = [0.47 0.5];
y = [0.55 0.5];
annotation('textarrow',x,y,'String','Lunge filter ')

x = [0.55 0.57];
y = [0.85 0.78];
annotation('textarrow',x,y,'String','Generel filter ')

x = [0.6 0.64];
y = [0.3 0.34];
annotation('textarrow',x,y,'String','S1S2 filter ')
title("Amplituderespons for samlet system")
