<?php

require_once './GnuPlot.php';

use Gregwar\GnuPlot\GnuPlot;

$plots = [new GnuPlot(), new GnuPlot(), new GnuPlot(), new GnuPlot()];
$yLabels = ["Precision/n %", "Recall/n %", "Accuracy %", "Tiempo (s)"];
$archivos = ["prec", "rec", "acc", "tiempo"];

foreach ($plots as $i => $plot) {
    $plot->enableHistogram();
    $plot->setXLabel("Cantidad de Componentes Principales");
    $plot->setYLabel($yLabels[$i]);

    $plot->setGraphTitle("Variación en \u{03B1}");
    $plot->setTitle(0, "2-Fold");
    $plot->setTitle(1, "5-Fold");
    $plot->setTitle(2, "10-Fold");
}

$folds = [2, 5, 10];
$ks = range(1, 50, 2);
//$alfas = range(5,100,5);
$alfas = range(5,60,5);
$dirResultados = __DIR__ . "/../resultados";
$archivo = "resultados.csv";

$metodo = ($argc > 1) ? $argv[1] : 0;
$k = ($argc > 2) ? $argv[2] : 1;
$maxs = [];
//$superAlfa=[0,0,0,0];
foreach ($alfas as $alfa) {
    $maxs[$alfa] =[0,0,0];
    foreach ($folds as $ik => $k_fold) {
        $tiemposum = 0;
        for ($it = 1; $it <= $k_fold; $it++) {
            $file = "$dirResultados/metodo_$metodo/k_$k/alfa_$alfa/k_fold_$k_fold/iteracion_$it/ejecucion.log";
            $f = file_get_contents($file);
            $lineas = explode(PHP_EOL, $f);
            list($_, $tiempo) = explode(": ", $lineas[6]);
            $tiemposum += $tiempo;
        }
        $tiempoProm = $tiemposum / $k_fold;
        $filename = "$dirResultados/metodo_$metodo/k_$k/alfa_$alfa/k_fold_$k_fold/$archivo";
        $handle = fopen($filename, "r");
        foreach ($plots as $i => $plot) {
            if ($i == 3) {
                $plot->push($alfa, $tiempoProm, $ik);
            } else {
                list($_, $y) = fgetcsv($handle, 0, " ");
                if($y > $maxs[$alfa][$ik]){
                    $maxs[$alfa][$ik]=$y;
                }
                $plot->push($alfa, $y, $ik);
            }
        }
        fclose($handle);
    }
}

foreach ($plots as $i => $plot) {
    $plot->writePng("m$metodo" . "_k$k"."_salida_" . $archivos[$i] . ".png");
}
$handle = fopen("resultados_m$metodo" . "_k$k.csv","w");
foreach ($maxs as $alfa => $maxis) {
    list($prec,$rec,$acc) = $maxis;
    fwrite($handle, "$alfa $prec $rec $acc\n");
}
fclose($handle);
