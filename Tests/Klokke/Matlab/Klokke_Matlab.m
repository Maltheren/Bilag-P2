
addpath('GenererFilter\');

%CSV fil af Anti filter
Filter_Anti = readmatrix('Anti_aliasing.csv');

model_Anti = Rekon();


%Målte værdier for Anti Filter
f_Anti = 10.^Filter_Anti(:,1);
A_Anti = Filter_Anti(:,2);
p_Anti = Filter_Anti(:,3);


[A_model_Anti, p_model_Anti] = SimModel(model_Anti, f_Anti);

yyaxis left
semilogx(f_Anti,A_Anti, f_Anti, A_model_Anti, '--') %Plotter både målt generelle filter og model filter
ylim([-35,5]);
ylabel('Amplitude [dBV]');
grid on
xlabel('Frekvens [Hz]');
%Plot Generelle filter, Fase
yyaxis right
semilogx(f_Anti, p_Anti, f_Anti, p_model_Anti, '--')
ylabel('Fase respons [^{o}]')
ylim([-180,180]);
yticks([-180,-90,0,90,180]);
legend({'|Målt|', '|Simuleret|', '\angleMålt', '\angleSimuleret'}, 'Location','southwest');
title('Bodeplot, Klokkemodul - Anti-aliasering');