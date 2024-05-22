
clc;
clear all;

Kvantisering_meas = readmatrix("Kvantisering_test.xlsx");

x = Kvantisering_meas(:,1);
Vin = Kvantisering_meas(:,3);
Vout = Kvantisering_meas(:,4);
VDif = Kvantisering_meas(:,2);


plot(Vin, Vout)
xlim([0,5.5]);
ylim([0,4.5])
grid on
ylabel('Vout [V]');
xlabel('Vin [V]');
title('ADC til DAC, Vin ~ Vout');

%Procent

%ideel = Vin*(4.2./5);
ideel = polyfit(Vin, Vout, 1);
y_ideel = polyval(ideel, Vin);
%y_ideel = ideel(1)*Vin;
%Procentafvigelse af 5V

%{

plot(Vin, y_ideel-Vout);
xlim([0,5]);
ylabel({'Amplitude difference mellem';'ideele og målte værdier [V]'});
xlabel('Vin [V]');
title('Kvantiseringsfejl i forhold til ideel linje');
grid on


%boxchart(y_ideel-Vout, 'Orientation','horizontal')
%grid on
%title('Kvantiseringfejl fra ADC til DAC');
%xlabel('Udgangsamplitude difference (ideel - målt) [V]');
%ylim auto
%nexttile
%plot(Vin, ((Vout./y_ideel)-1)*100)

%boxchart(((Vout./y_ideel)-1)*100, 'Orientation','horizontal')

%}
