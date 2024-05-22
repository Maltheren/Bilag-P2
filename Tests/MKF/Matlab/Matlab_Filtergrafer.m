clear all;
clc

addpath('GenererFilter\');
Filter_Generel = readmatrix("Generel_Bode_Norm.txt");
Filter_S1S2 = readmatrix("S1_Bode_Norm.txt");
Filter_Lung = readmatrix("Lunger_Bode_Norm.txt");
Filter_Rekon = readmatrix("Rekon_Norm_All.txt");

t = tiledlayout(2,2);

%Modeller af filterbank
model_G = Generel();
model_S1S2 = S1S2();
model_Lung = Lunge();
model_Rekon = Rekon();

%Målt Generelle filter
f_Generel = Filter_Generel(:,1);
A_Generel = Filter_Generel(:,3);
p_Generel = Filter_Generel(:,4);

%Målt S1S2 filter
f_S1S2 = Filter_S1S2(:,1);
A_S1S2 = Filter_S1S2(:,3);
p_S1S2 = Filter_S1S2(:,4);

%Målt Lunge filter
f_Lung = Filter_Lung(:,1);
A_Lung = Filter_Lung(:,3);
p_Lung = Filter_Lung(:,4);

%Målt Rekon filter
f_Rekon = Filter_Rekon(:,1);
A_Rekon = Filter_Rekon(:,3);
p_Rekon = Filter_Rekon(:,4);


%Plot Generelle filter, Amplitude

[A_model_G, p_model_G] = SimModel(model_G, f_Generel); %Model af det generelle filter
nexttile
yyaxis left
semilogx(f_Generel,A_Generel-3, f_Generel, A_model_G, '--') %Plotter både målt generelle filter og model filter
ylim([-35,5]);
ylabel('Amplitude Respons [dBV]');
grid on
xlabel('Frekvens [Hz]');
%Plot Generelle filter, Fase
yyaxis right
semilogx(f_Generel, p_Generel, f_Generel, p_model_G, '--')
ylabel('Fase respons [grader^{o}]')
ylim([-180,180]);
yticks([-180,-90,0,90,180]);
legend({'|Målt|', '|Simuleret|', '\angleMålt', '\angleSimuleret'}, 'Location','southwest');
title('Bodeplot, Filterbank - Generelle filter');


%Plot S1S2 Filter, Amplitude
[A_model_S1S2, p_model_S1S2] = SimModel(model_S1S2, f_S1S2);
nexttile
yyaxis left
semilogx(f_S1S2, A_S1S2-3, f_S1S2, A_model_S1S2, '--')
legend('Målte filter', 'Simuleret filter');
ylim([-35,5]);
ylabel('Amplitude [dBV]');
grid on
xlabel('Frekvens [Hz]');
%Plot S1S2 Filter, Fase
yyaxis right
semilogx(f_S1S2, p_S1S2, f_S1S2, p_model_S1S2, '--')
ylabel('Fase respons [grader^{o}]')
ylim([-180,180]);
yticks([-180,-90,0,90,180]);
legend({'|Målt|', '|Simuleret|', '\angleMålt', '\angleSimuleret'}, 'Location','southwest');
title('Bodeplot, Filterbank - S1S2 filter');


%Plot lunge Filter, Amplitude
[A_model_Lung, p_model_Lung] = SimModel(model_Lung, f_Lung);
nexttile
yyaxis left
semilogx(f_Lung, A_Lung-3, f_Lung, A_model_Lung, '--')
ylim([-35,5]);
ylabel('Amplitude Respons [dBV]');
grid on
xlabel('Frekvens [Hz]');
%Plot Lunge filter, Fase
yyaxis right
semilogx(f_Lung, p_Lung, f_Lung, p_model_Lung, '--')
ylabel('Fase respons [grader^{o}]')
ylim([-180,180]);
yticks([-180,-90,0,90,180]);
legend({'|Målt|', '|Simuleret|', '\angleMålt', '\angleSimuleret'}, 'Location','southwest');
title('Bodeplot, Filterbank - Lunge filter');


%Plot Rekon filter, Amplitude
[A_model_Rekon, p_model_Rekon] = SimModel(model_Rekon, f_Rekon);
nexttile
yyaxis left
semilogx(f_Rekon, A_Rekon-3, f_Rekon, A_model_Rekon)
ylim([-35,5]);
ylabel('Amplitude Respons [dBV]');
grid on
xlabel('Frekvens [Hz]');
%Plot Rekon filter, Fase
yyaxis right
semilogx(f_Rekon, p_Rekon, f_Rekon, p_model_Rekon)
ylabel('Fase respons [grader^{o}]')
ylim([-180,180]);
yticks([-180,-90,0,90,180]);
title('Bodeplot, Rekonstruktions filter');
legend({'|Målt|', '|Simuleret|', '\angleMålt', '\angleSimuleret'}, 'Location','southwest');




