% Wczytaj dane z generatora
data = readtable('generator.csv', 'Delimiter', ';');

% Stwórz wykres
figure;
plot(data.t, data.wartosc, 'b', 'LineWidth', 1.5);
title('Sygnał wyjściowy generatora');
xlabel('Czas [krok]');
ylabel('Amplituda');
grid on;
set(gcf, 'Color', 'w');  % Białe tło
set(gca, 'GridLineStyle', '--');  % Kreskowana siatka
exportgraphics(gcf, 'generator_plot.png', 'Resolution', 300);  % Eksportuj jako obraz

%straight
%Set: 1.0

%sin 
%Amplitude: 0.5
%Frequency: 0.05

%triangle
%Amplitude: 0.4
%Period: 50
%Symmetry: 0.6