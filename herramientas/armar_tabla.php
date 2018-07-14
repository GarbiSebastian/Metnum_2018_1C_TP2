<?php

$folds = [2, 5, 10];
$ks = range(1, 50, 2);
$alfas = range(5, 200, 5);
$dirResultados = __DIR__."/../resultados";
$archivo = "resultados.csv";

$metodo = ($argv[1]) ?: 0;
foreach ($ks as $k) {
    echo "$k";
    foreach ($folds as $k_fold) {
        if ($metodo % 2 == 1) {
            foreach ($alfas as $alfa) {
                $filename = "$dirResultados/metodo_$metodo/k_$k/alfa_$alfa/k_fold_$k_fold/$archivo";
                //echo $filename.PHP_EOL;
                //echo file_get_contents($filename);                
            }
        } else {
            $filename = "$dirResultados/metodo_$metodo/k_$k/k_fold_$k_fold/$archivo";
            //echo $filename.PHP_EOL;
            $handle = fopen($filename, "r");
            list($_, $presicion) = fgetcsv($handle, 0, " ");
            list($_, $recall) = fgetcsv($handle, 0, " ");
            list($_, $acc) = fgetcsv($handle, 0, " ");
            fclose($handle);
            echo " & ";
            echo number_format($presicion, 2, ",","");
            echo " & ";
            echo number_format($recall, 2, ",","");
            echo " & ";
            echo number_format($acc, 2, ",","");
        }
    }
    echo '\\\\';
    echo PHP_EOL;
}


