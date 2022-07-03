
clear ;clc
load('ORL.mat'); 

X = fea;
y = gnd;
sample_num = 15;
%划分训练集和测试集
X_tra = zeros(sample_num*8,1024);
y_tra = zeros(sample_num*8,1);
X_val = zeros (sample_num*2,1024);
y_val = zeros(sample_num*2,1);
for i =1:sample_num 
    a = 1+(i-1)*8;
    b = 8+(i-1)*8;
    c = 1+(i-1)*10;
    d = 8+(i-1)*10;
    X_tra(a: b,:)  = X(c:d,:);
    y_tra(a:b) = y(c:d);
    e = 1+(i-1)*2;
    f = 2+(i-1)*2;
    g = 9+(i-1)*10;
    h = 10+(i-1)*10;
    X_val(e:f,:) =X(g:h,:);
    y_val(e:f) =y(g:h);    
end



input_layer_size  = 1024;  
hidden_layer_size = 60;  
num_labels = sample_num;         
DATA = zeros(20,1);
for i = 1:20
    initial_Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
    initial_Theta2 = randInitializeWeights(hidden_layer_size, num_labels);
    initial_nn_params = [initial_Theta1(:) ; initial_Theta2(:)];
    options = optimset('MaxIter', 4000);
    lambda = 2*i;
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
    DATA(i) = mean(double(pred == y_val));

    
end