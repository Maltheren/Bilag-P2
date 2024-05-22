close all; clear all;

s = serialport("COM3",921600);
configureTerminator(s,'CR/LF');

fopen(s);


i = 1;
while(1)
    data(i,1) = readline(s);

    data(i,1)
    taldata(i,1) = str2double(data(i,1));
    plot(taldata);
    ylim([0 1024]);
    pause(0.01);
    i=i+1;


end