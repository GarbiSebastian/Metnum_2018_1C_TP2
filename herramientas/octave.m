A=zeros(1,10304);
for sujeto = 1:41 for imagen = 1:10 file=strcat("ImagenesCaras/s",num2str(sujeto),"/",num2str(imagen),".pgm");A=[A;imread(file)(:)'];endfor;endfor;
A=cast(A(2:end,1:end),"double");
m=sum(A);
M=ones(410,1)*m;
X=(A-M)/sqrt(410-1);
Mx=X'*X;
