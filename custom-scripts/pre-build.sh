#!/bin/sh

cp $BASE_DIR/../custom-scripts/S41network-config $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S41network-config

cp $BASE_DIR/../custom-scripts/webserver.py $BASE_DIR/target/usr/bin
chmod +x $BASE_DIR/target/usr/bin/webserver.py

cp $BASE_DIR/../custom-scripts/S50server $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S50server