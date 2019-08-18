#!/bin/sh 
#build docker continers
cp ./app/app.cpp ./debugtool/app.cpp

pushd app
docker build -t testapp:0.1 .
popd

pushd debugtool 
docker build -t debugtool:0.1 .
popd
