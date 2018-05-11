#!/bin/bash
find ImagenesCaras | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > baseCaras.csv
find ImagenesCarasRed | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > baseCarasRed.csv
find ImagenesCaras | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\2 0\3 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > baseCaras2.csv
find ImagenesCarasRed | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\2 0\3 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > baseCarasRed2.csv
