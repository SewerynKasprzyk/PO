data = readtable('symulacja.csv', 'Delimiter', ';');
plot(data.t, data.wartosc_zadana, '--g', 'LineWidth', 1.5);
hold on;
plot(data.t, data.wyjscie, 'b', 'LineWidth', 1.5);
plot(data.t, data.sterowanie, 'r', 'LineWidth', 1.5);
legend('Wartoœæ zadana', 'Wyjœcie', 'Sterowanie');
grid on;