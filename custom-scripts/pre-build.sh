#!/bin/sh

cp $BASE_DIR/../custom-scripts/S41network-config $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S41network-config

cp $BASE_DIR/../custom-scripts/webserver.py $BASE_DIR/target/usr/bin
chmod +x $BASE_DIR/target/usr/bin/webserver.py

cp $BASE_DIR/../custom-scripts/S50server $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S50server

cp $BASE_DIR/../custom-scripts/read_tests $BASE_DIR/target/usr/bin
chmod +x $BASE_DIR/target/usr/bin/read_tests

make -C $BASE_DIR/../modules/sstf-iosched-skeleton/

make -C $BASE_DIR/../modules/simple_driver/

tracefs /sys/kernel/tracing tracefs 0 0

cp $BASE_DIR/../custom-scripts/trace $BASE_DIR/target/usr/bin
chmod +x $BASE_DIR/target/usr/bin/trace