function [mix_matrix,accuracy,P,R,F1]  = data_analyse(X_val,y_val,Theta1,Theta2)
% 混淆矩阵
mix_matrix = zeros(2,2);
%预测
pred = predict(Theta1, Theta2, X_val);

m = length(y_val);

% 2 为正例  1 为反例
for i =1:m
    if  y_val(i)==pred(i) && y_val(i)==2
            mix_matrix(1,1) = mix_matrix(1,1)+1;
    elseif y_val(i)==pred(i) && y_val(i)==1
            mix_matrix(2,2) = mix_matrix(2,2) + 1;
    elseif y_val(i) ==2 && pred(i) ==1
            mix_matrix(1,2) = mix_matrix(1,2)+1;
    elseif y_val(i)==1 && pred(i) ==2
            mix_matrix(2,1) = mix_matrix(2,1) +1;
    end
end
% 计算精度
accuracy =( mix_matrix(1,1)+mix_matrix(2,2))/m;

% 计算查准率 ，查全率
P =  mix_matrix(1,1)/(mix_matrix(1,1)+mix_matrix(2,1));
R = mix_matrix(1,1)/(mix_matrix(1,1)+ mix_matrix(1,2));
F1 = 2*P*R/(P+R);
