#!/bin/bash
bases_dir=bases;
imgdir=ImagenesCaras;
imgreddir=ImagenesCarasRed;
mkdir -p $bases_dir;
find $imgdir | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, \2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > $bases_dir/baseCaras.csv
find $imgreddir | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, \2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > $bases_dir/baseCarasRed.csv
echo "bases creadas";
