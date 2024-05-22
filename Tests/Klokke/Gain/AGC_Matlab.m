Gain_2 = readmatrix("Integrationstest\Klokke\Gain\forstærkerklokke.txt");
Gain_25 = readmatrix("forstærkerklokke_vin25.txt");
Gain_3 = readmatrix("forstærkerklokke_vin3.txt");
Gain_35 = readmatrix("forstærkerklokke_vin35.txt");
Gain_4 = readmatrix("forstærkerklokke_vin4.txt");

test = Gain_2(1,2)/32


time = Gain_2(:,1)/125;
out_2 = (Gain_2(:, 2)-Gain_2(1,2))/32
in_2 = (Gain_2(:,3)-Gain_2(1,3))/32*0.1+0.05;

out_25 = (Gain_25(:,2)-Gain_25(1,2))/32;
in_25 = (Gain_25(:,3)-Gain_25(1,3))/32*0.1+0.055;

out_3 = (Gain_3(:,2)-Gain_3(1,2))/32;
in_3 = (Gain_3(:,3)-Gain_3(1,3))/32*0.1+0.055;

out_35 = (Gain_35(:,2)-Gain_35(1,2))/32;
in_35 = (Gain_35(:,3)-Gain_35(1,3))/32*0.1+0.055;

out_4 = (Gain_4(:,2)-Gain_4(1,2))/32;
in_4 = (Gain_4(:,3)-Gain_4(1,3))/32*0.1+0.055;

yyaxis left;
hold on
plot(time, out_2, "-", "Color", "red")
plot(time, out_25, "-", "Color", "green")
plot(time, out_3, "-", "Color", "blue")
plot(time, out_35, "-", "Color", "magenta")
plot(time, out_4, "-", "Color", "black")
ylabel("Amplitude Vout [V]")
hold off
xlim([0,15])

yyaxis right;
plot(time, in_2, "--", "Color", "red")
ylim([-0.5, 0.5])
hold on
plot (time, in_25, "--", "Color", "green")
plot (time, in_3, "--", "Color", "blue")
plot (time, in_35, "--", "Color", "magenta")
plot (time, in_4, "--", "Color", "black")
legend ("", "", "", "", "AGC out", "200mV in", "250mV in", "300mV in", "350mV in", "400mV in")
ylabel("Amplitude Vin [V]")
hold off

xlabel ("time [ms]")


