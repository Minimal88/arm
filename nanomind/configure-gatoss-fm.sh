#!/bin/sh
/usr/bin/python waf configure \
	\
	--enable-driver-debug \
	\
	--with-cdh \
	--enable-rrstore \
	--enable-fp-client \
	--enable-fp-server \
	--enable-log-server \
	--enable-log-client \
	--enable-log-node \
	\
	--with-adcs \
	\
	--with-storage \
	--enable-fat \
	--enable-uffs \
	\
	--with-log=cdh \
	--enable-rtc \
	--enable-mpio \
	--enable-sd \
	--config-sd-cs=7 \
	--enable-flash-fs \
	--with-console=0 \
	--rom \
	--sat="FM" \
	--hostname="nanomind" \
	--model="A712D" \
	eclipse
