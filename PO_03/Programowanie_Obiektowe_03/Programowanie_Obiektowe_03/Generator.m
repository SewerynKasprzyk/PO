% Wczytaj dane
data = readtable('generator_only.csv', 'Delimiter', ';');

% Stwórz wykres
figure;
plot(data.t, data.wartosc, 'b', 'LineWidth', 1.5);
title('Sygnał z generatora');
xlabel('Czas [krok]');
ylabel('Wartość');
grid on;