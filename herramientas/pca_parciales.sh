#!/bin/bash
metodo=1
dir_resultados=resultados;
for k in 1 2 3 5 7; do
	for alfa in 1 2 3 5 7 10 20 30; do
		for k_fold in 2 5 10; do
			for iteracion in $(seq -s' ' 1 $k_fold); do
				fold_dir=folds/k_fold_$k_fold/iteracion_$iteracion;
				dir=$dir_resultados/metodo_$metodo/k_$k/alfa_$alfa/k_fold_$k_fold/iteracion_$iteracion;
				dir_parciales=$dir_resultados/metodo_$metodo/parciales/k_fold_$k_fold/iteracion_$iteracion;
				mkdir -p $dir;
				comando="cat $dir_parciales/clasif.csv | grep -e '$k $alfa I' | awk '{print "\$"3  "\"" "\"" "\$"4}' > $dir/clasif.csv";
				echo "";
				echo $comando;
				eval $comando;
			done;
		done;
	done;
done;
echo  "pca parciales finalizado";
