clc ;
clear all

signal = readmatrix('S1S2.csv');

y_meas = signal(:,1);

x = (1:length(y_meas))*(1/6000);



plot(x,y_meas)
ylim([0,1024])
xlim([1,1.02])

ylabel('Signal kvantiseret med 10 bit opløsning')
xlabel('Tid [s]')
title('MKF visualisering af signal')


