clear;
figure(1);
test=load('5test.txt');
save_trace = test;
plot3(save_trace(:,1),save_trace(:,2),save_trace(:,3));
grid on;hold on;

