#!/bin/bash
sujetos=41;
imagenes=10;
base=bases/baseCaras.csv;
for k_fold in 2 5 10; do
	fold_tam=$((imagenes/k_fold));
	for iteracion in $(seq -s' ' 1 $k_fold); do
		fold_dir=folds/k_fold_$k_fold/iteracion_$iteracion;
		mkdir -p $fold_dir;
		cat $base | head -n $(( fold_tam*iteracion*sujetos )) | tail -n $(( fold_tam*sujetos )) > $fold_dir/test.csv;
		cat $base $base | tail -n $(( (imagenes*2- fold_tam*iteracion)* sujetos )) | head -n $(( (imagenes-fold_tam)*sujetos )) > $fold_dir/train.csv;
	done;
done;
echo "folds train test finalizado";
