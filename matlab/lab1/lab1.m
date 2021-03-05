clear;
clc;

DOTS = 5; % количество узлов интерполяции
A = 1; % левая граница 
B = 9; % правая граница

x = A:(B-A)/(DOTS-1):B; % равностоящие узлы интерполяции
y = sin(x); % значения интерполируемой функции

% нахождение интерполяционного полинома Лагранжа
lagrange_polynom = lagrange(x,y);
newton_polynom = newton(x,y);

X = A:0.1:B;

% построение графиков
f = figure('Color','w');
set(f, 'Position', [200, 100, 1000, 495]) 
% вывод графика sin(x)
subplot(1,2,1)
fplot(@sin,[0 10])
hold on
% вывод графиков полиномов
title('Lagrange');
plot(X,polyval(lagrange_polynom, X),'r')
% вывод узлов интерполяции
plot(x,y,'bo')

subplot(1,2,2)
fplot(@sin,[0 10])
hold on
% вывод графиков полиномов
title('Newton');
plot(X, polyval(newton_polynom, X), 'g')
% вывод узлов интерполяции
plot(x,y,'bo')

% разметка
grid on
xlabel('x');
ylabel('y');
