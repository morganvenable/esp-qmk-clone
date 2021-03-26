#!/bin/bash
esp_idf_include_path=$1
keyboard=$2
layout=$3

CPATH=$CPATH:${esp_idf_include_path//;/:} make $keyboard:$layout