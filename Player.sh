#!/bin/sh

/etc/init.d/S99demo stop
/etc/init.d/S90weston stop

QMLSCENE_DEVICE=softwarecontext \
QT_LOGGING_RULES=qt.qpa.*=true \
QT_QPA_EGLFS_KMS_CONNECTOR_INDEX=0 \
QT_QPA_EGLFS_KMS_PLANE_INDEX=2 \
QT_QPA_FB_DRM=1 \
QT_QPA_FB_DRM_FORMAT=18 \
/opt/VideoPlayer/player -platform linuxfb -plugin tslib:/dev/input/event1 \
               -plugin evdevkeyboard:/dev/input/event0 $1

/etc/init.d/S90weston start
/etc/init.d/S99demo start
