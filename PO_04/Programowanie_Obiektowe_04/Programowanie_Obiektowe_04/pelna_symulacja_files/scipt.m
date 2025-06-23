% Wczytaj dane z pełnej symulacji
data = readtable('pelna_symulacja.csv', 'Delimiter', ';');

% Stwórz wykres
figure;
yyaxis left;  % Dwa osie Y
plot(data.t, data.wartosc_zadana, '--g', 'LineWidth', 1.5);
hold on;
plot(data.t, data.wyjscie, 'b', 'LineWidth', 1.5);
ylabel('Amplituda');

yyaxis right;  % Druga oś Y dla sterowania
plot(data.t, data.sterowanie, 'r', 'LineWidth', 1.5);
ylabel('Sterowanie');

% Konfiguracja wykresu
title('Symulacja systemu sterowania');
xlabel('Czas [krok]');
legend('Wartość zadana', 'Wyjście', 'Sterowanie', 'Location', 'best');
grid on;
set(gcf, 'Color', 'w');  % Białe tło
set(gca, 'GridLineStyle', '--');  % Kreskowana siatka
exportgraphics(gcf, 'simulation_plot.png', 'Resolution', 300);  % Eksportuj jako obraz