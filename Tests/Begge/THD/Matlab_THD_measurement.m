%Henter de 32 samples fra mappen
samples = LoadSamples("THD waveform\THD waveform_XX.mat");
disp("fs");
disp(1/samples(1).Tinterval);
THD_dB = 0;
THD_linear = 0;
i = 1;

for sample = samples

    THD_dB(i) = thd(sample.A, 1/sample.Tinterval, 6); %%Sample.A er output Sample.B er input. THD funktionen giver dog et resultat i dB.
    THD_linear(i) = 10^(THD_dB(i)/20) * 100; %Konverterer til procent
    i = i + 1;
end

details(THD_linear);

disp("THD: ");
disp(mean(THD_linear));
disp("S: ");
disp(std(THD_linear));
disp("95% konfidensinterval");
disp(mean(THD_linear)+[1.96, -1.96]*std(THD_linear));


function Sample=LoadSamples(input) %henter alle samples i en mappe til et array med navnet og erstatter XX
    for i = 1:32
        if(i < 10)
            filename = strrep(input, 'XX', strcat('0', int2str(i)));
        else
            filename = strrep(input, 'XX', int2str(i));
        end
        Sample(i) = load(filename);
        disp(filename);
    end
end