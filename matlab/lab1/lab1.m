clear;
clc;

DOTS = 5; % количество узлов интерполяции
A = 1; % левая граница 
B = 9; % правая граница

x = A:(B-A)/(DOTS-1):B; % равностоящие узлы интерполяции
y = interpfunc(x); % значения интерполируемой функции
h = 0.001;
X = A:h:B;

% Выбор случайной точки, не совпадающей ни с одним узлом
random_x = rand; % СДЕЛАТЬ ВЫБОР В ДИАПАЗОНЕ A B

% Вычисление теоретической погрешности интерполяции в выбранной точке

omega = 1;
for i = 1 : DOTS
    omega = omega * (random_x - x(i)); 
end

% ДОБАВИТЬ ВЫЧИСЛЕНИЕ n ПРОИЗВОДНОЙ !!!
interpolation_error = abs(omega/factorial(DOTS+1));

% нахождение интерполяционного полинома Лагранжа
lagrange_polynom = lagrange(x,y);
newton_polynom = newton(x,y);

% Вычисление реальной погрешности интерполяции в выбранной точке
real_error = abs(polyval(lagrange_polynom, random_x));

% Сравнение теоретической погрешности и реальной
interpolation_error
real_error

% Построение графиков
f = figure('Color','w');
set(f, 'Position', [200, 100, 1000, 495]) 
% вывод графика sin(x)
subplot(1,2,1)
fplot(@interpfunc,[0 10])
hold on
% вывод графиков полиномов
title('Lagrange');
plot(X,polyval(lagrange_polynom, X),'r')
% вывод узлов интерполяции
plot(x,y,'bo')

% разметка
grid on
xlabel('x');
ylabel('y');

subplot(1,2,2)
fplot(@interpfunc,[0 10])
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
