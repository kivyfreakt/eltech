clear;
clc;

DOTS = 5; % количество узлов интерполяции
A = 1; % левая граница 
B = 9; % правая граница

x = A:(B-A)/(DOTS-1):B; % равностоящие узлы интерполяции
i = randi(DOTS); % выбор случайного номера
y = sin(x); % значения интерполируемой функции
y(i) = y(i) + rand; % точка, не совпадающая со значением функции. (СДЕЛАТЬ НОРМ ВЫБОР)

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
