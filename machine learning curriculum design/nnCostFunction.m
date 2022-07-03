function [J ,grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

m = size(X, 1);
         

J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));
%forward 
h = eye(num_labels);
y = h(y,:);
for k =1:size(X,1)
    x=X(k,:);
    ah=Theta1(:,2:end)*x';
    b=sigmoid(ah+Theta1(:,1));
    beta=Theta2(:,2:end)*b;
    Y=sigmoid(beta+Theta2(:,1));
    J=J +(-y(k,:)*log(Y)  - (1-y(k,:)) * log(1-Y));
end
reg=lambda/(2*m)*( sum(sum(Theta1(:,2:end).^2))+...
    sum(sum(Theta2(:,2:end).^2)) );
J=1/m*J+reg;

temp2all=zeros(size(Theta2));
temp1all=zeros(size(Theta1));


for k =1:size(X,1)
    x=X(k,:);
    ah=Theta1(:,2:end)*x';
    b=sigmoid(ah+Theta1(:,1));
    beta=Theta2(:,2:end)*b;
    Y=sigmoid(beta+Theta2(:,1)); 
    
    g=-(y(k,:)-Y');
    e=b.*(1-b).*(g*Theta2(:,2:end))';
    %Theta2_grad(:,2:end)=g'*b';
    %Theta2_grad(:,1)=g';
    temp2=g'*[1 b'];
    temp2all=temp2all+temp2;
    %Theta2=Theta2+temp2;
    %Theta1_grad(:,2:end)=e*x;
    %Theta1_grad(:,1)=e;
    temp1=e*[1 x];
    temp1all=temp1all+temp1;
    %Theta1=Theta1+temp1;
%     Theta2=Theta2+Theta2_grad;
%     Theta1=Theta1+Theta1_grad;

end
 Theta2_grad=1/m*temp2all+(lambda/m)*(Theta2);
Theta1_grad=1/m*temp1all+(lambda/m)*(Theta1);
Theta1_grad(:,1) = Theta1_grad(:,1) - ((lambda/m)*(Theta1(:,1)));
Theta2_grad(:,1) = Theta2_grad(:,1) - ((lambda/m)*(Theta2(:,1)));

grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
