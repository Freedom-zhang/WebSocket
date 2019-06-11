/****************************************************************************
**
** Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Milian Wolff <milian.wolff@kdab.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWebChannel module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/
//#include "qwebchannel.h"
#include <QApplication>
#include <QDialog>
#include <QVariantMap>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include <QtWebSockets/QWebSocketServer>
#include "websocketclientwrapper.h"
#include "websockettransport.h"
#include "./ui_dialog.h"
#include <QWebChannel>
#include "dialog.h"
#include <QUrl>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
//    QFileInfo jsFileInfo(QDir::currentPath() + "/qwebchannel.js");
//    if (!jsFileInfo.exists())
//        QFile::copy(":/qtwebchannel/qwebchannel.js",jsFileInfo.absoluteFilePath());
    //这只是为了能把qwebchannel.js放到指定目录能让index.html找到,在我这然并卵.手动复制
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"), QWebSocketServer::NonSecureMode); //NonSecureMode非安全模式
    //创建webSocket服务端,第二个参数应该是和关闭防火墙类似的操作,不进行安全检测
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }
    //创建完后肯定要绑定啦,地址端口号要和HTML中的一样
    WebSocketClientWrapper clientWrapper(&server);
    /* 为了能将接受到的新连接的套接字包装成WebSocketTransport用信号传递给
    ** QWebChannel的void QWebChannel::connectTo(QWebChannelAbstractTransport *transport)
    ** 而接受参数正好是QWebChannelAbstractTransport，WebSocketTransport就是它的子类
    */
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);
    /*
    ** 当有新连接即html端打开,serve将获得与之相连的新socket,接着触发WebSocketClientWrapper槽
    ** 将socket作为WebSocketTransport参数实例化这个对象,然后作为信号参数传递给QWebChannel
    ** QWebChannel就获得了与html通话的能力
    */
    Dialog dialog;
    channel.registerObject(QStringLiteral("dialog"), &dialog);//注册后能在HTML中使用
    //感觉就是这了,将Dialog的信号,函数等信息发给qwebchannel让其处理
    QUrl url = QUrl::fromLocalFile(":/index.html");
    //QDesktopServices::openUrl(url);
    //这两句只是自动打开html而已,可以手动打开的哟
    //为了照顾下面那一行代码才没有将其删除
    dialog.displayMessage(QObject::tr("Initialization complete, opening browser at %1.").arg(url.toDisplayString()));
    return app.exec();
}
/*
 * 一般情况下，你的类会单独写，一个 ***.h, 一个 ***.cpp 。 类的定义在 头文件中，qmake可以调用moc自动处理（生成moc_***.h）并自动包含。
但你要是偷懒，比如把main函数和类的定义及实现都放到一个文件内，比如取名 main.cpp ，这时就不那么走运了，moc处理后生成 同名 的 .moc 文件，但这时你必须自己包含它了。
*/
