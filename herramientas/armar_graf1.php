<?php

require_once './GnuPlot.php';

use Gregwar\GnuPlot\GnuPlot;

$plots = [new GnuPlot(), new GnuPlot(), new GnuPlot(), new GnuPlot()];
$yLabels = ["Precision/n %", "Recall/n %", "Accuracy %", "Tiempo (s)"];
$archivos = ["prec", "rec", "acc", "tiempo"];

foreach ($plots as $i => $plot) {
    $plot->enableHistogram();
    $plot->setXLabel("Cantidad de Vecinos");
    $plot->setYLabel($yLabels[$i]);
//    $plot->setY2Label("tiempo s");
    //$plot->enableHistogram();
//    $plot->sendCommand("set ytics 2.5 nomirror tc");
//    $plot->sendCommand("set y2tics nomirror");
//    $plot->sendCommand("set y2tics nomirror");
//    

    $plot->setGraphTitle('Variación en #vecinos');
    $plot->setTitle(0, "2-Fold");
    $plot->setTitle(1, "5-Fold");
    $plot->setTitle(2, "10-Fold");
}

$folds = [2, 5, 10];
$ks = range(1, 50, 2);
$alfas = range(5, 200, 5);
$dirResultados = __DIR__ . "/../resultados";
$archivo = "resultados.csv";

$metodo = ($argc > 1) ? $argv[1] : 0;
foreach ($ks as $k) {
    foreach ($folds as $ik => $k_fold) {
        $tiemposum = 0;
        for ($it = 1; $it <= $k_fold; $it++) {
            $file = "$dirResultados/metodo_$metodo/k_$k/k_fold_$k_fold/iteracion_$it/ejecucion.log";
            $f = file_get_contents($file);
            $lineas = explode(PHP_EOL, $f);
            list($_, $tiempo) = explode(": ", $lineas[6]);
            $tiemposum += $tiempo;
        }
        $tiempoProm = $tiemposum / $k_fold;
        $filename = "$dirResultados/metodo_$metodo/k_$k/k_fold_$k_fold/$archivo";
        //echo $filename.PHP_EOL;
        $handle = fopen($filename, "r");
        foreach ($plots as $i => $plot) {
            if ($i == 3) {
                $plot->push($k, $tiempoProm, $ik);
            } else {
                list($_, $y) = fgetcsv($handle, 0, " ");
                $plot->push($k, $y, $ik);
            }
        }
        fclose($handle);
    }
}

foreach ($plots as $i => $plot) {
    $plot->writePng("metodo_$metodo" . "salida_" . $archivos[$i] . ".png");
}