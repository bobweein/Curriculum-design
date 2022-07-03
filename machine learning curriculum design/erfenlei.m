% Load Training Data
clear;clc
fprintf('Loading and Visualizing Data ...\n')

load('ORL.mat'); 

% % 展示数据
% showdata(fea);

%X 为数据集
X = fea;
y = load("label.txt","-ascii");


y = y+1;
% y中数据1 表示反例 2 表示正例

m = length (y);
ind = randperm(m);
X = X(ind,:);
y = y(ind);

X_tra = X(1:300,:);
X_val = X(301:400,:);
y_tra = y(1:300);
y_val =  y(301:400);


input_layer_size  = 1024;  %
hidden_layer_size =  60;   % 
num_labels = 2;      % 


initial_Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
initial_Theta2 = randInitializeWeights(hidden_layer_size, num_labels);


initial_nn_params = [initial_Theta1(:) ; initial_Theta2(:)];

fprintf('\nTraining Neural Network... \n')


options = optimset('MaxIter', 2000);

num = 20;
data = zeros(20,8);
for i = 1:20
    
    lambda = i*2;
    
    costFunction = @(p) nnCostFunction(p, ...
                                       input_layer_size, ...
                                       hidden_layer_size, ...
                                       num_labels, X_tra, y_tra, lambda);
    

    [nn_params, cost] = fmincg(costFunction, initial_nn_params, options);

    Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                     hidden_layer_size, (input_layer_size + 1));
    
    Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                     num_labels, (hidden_layer_size + 1));
    
    pred = predict(Theta1, Theta2, X_val);
    [mix_matrix,accuracy,P,R,F1]  = data_analyse(X_val,y_val,Theta1,Theta2);
        data(i,1:4) = mix_matrix(:);
        data(i,5) = P;
        data(i,6) = R;
        data(i,7) = F1;
        data(i,8) = accuracy;
end 