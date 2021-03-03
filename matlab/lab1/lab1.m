clear;
clc;

A = 1; % левая граница 
B = 9; % правая граница

x = A:2:B; % узлы интерполяции
y = sin(x); % значения интерполируемой функции

% нахождение интерполяционного полинома Лагранжа
lagrange_polynom = lagrange(x,y);
newton_polynom = newton(x,y);

X = A:0.1:B;

% построение графиков
figure('Color','w')
% вывод графика sin(x)
fplot(@sin,[1 9])
hold on
% вывод графиков полиномов
plot(X,polyval(lagrange_polynom, X),'r', X, polyval(newton_polynom, X), 'g')
% вывод узлов интерполяции
plot(x,y,'bo')
