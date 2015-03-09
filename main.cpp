/*
 * Copyright (C) 2013-2015 Atmel Corporation.
 *
 * This file is licensed under the terms of the Atmel LIMITED License Agreement
 * as written in the COPYING file that is delivered in the project root directory.
 *
 * DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * See the COPYING license file for more details.
 */

#include "player.h"
#include <QApplication>
#include <QThread>


#define LCD_WIDTH   800
#define LCD_HEIGHT  480
#define LAYER       1

QString fPath;

class GMainLoopThread : public QThread
{
    void run()
    {
        GMainLoop *mainloop;
        mainloop = g_main_loop_new(NULL, FALSE);
        g_main_loop_run(mainloop);
    }
};

int main(int argc, char *argv[])
{
    QString current;
    QString currentName;
    QString currentVal;
    int idxOf=0;

    /* Parse command line arguments */
    for(int i=0; i<argc; i++)
    {
        current = argv[i];
        idxOf = current.indexOf("=");
        if(idxOf == -1)
        {
            currentName = current;
            currentVal = QString();
        }else{
            currentName = current.left(idxOf);
            currentVal = current.mid(idxOf+1);
        }

//        if(currentName.count())
//        {
            if(currentName.contains(QString("filePath")))
            {
                fPath = currentVal;
            }else{
                fPath = QString("/opt/VideoPlayer/media/Tech_on_Tour-Atmel_Launches_Mobile_Trailer.mp4");
            }
//        }
    }


    // Enable ovr1 layer for Qt
    Tools *tools = new Tools;

    GMainLoopThread *mainloop = new GMainLoopThread;

    tools->enableLayer(LCD_WIDTH,LCD_HEIGHT,LAYER);

    QApplication a(argc, argv);
    Player w(fPath);
    w.show();

    // Start listener for GStreamer messages
    mainloop->start();

    return a.exec();
}
