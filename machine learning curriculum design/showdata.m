% 数据可视化后，手动对样本进行标记
function showdata(fea)

for i = 1:40
    sel = fea(1+10*(i-1):10+10*(i-1), :);

    displayData(sel);
    
    pause

end