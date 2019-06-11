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

#include "websockettransport.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <QtWebSockets/QWebSocket>



QT_BEGIN_NAMESPACE

/*!
构造传输对象并包装给定的套接字。
套接字还被设置为传输对象的父对象。
*/
WebSocketTransport::WebSocketTransport(QWebSocket *socket)
: QWebChannelAbstractTransport(socket)
, m_socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived,
            this, &WebSocketTransport::textMessageReceived);
    connect(socket, &QWebSocket::disconnected,
            this, &WebSocketTransport::deleteLater);
}

/*!
    Destroys the WebSocketTransport.
*/
WebSocketTransport::~WebSocketTransport()
{
    m_socket->deleteLater();
}

/*!
    Serialize the JSON message and send it as a text message via the WebSocket to the client.
    序列化JSON消息并将其作为文本消息通过WebSocket发送到客户机
*/
void WebSocketTransport::sendMessage(const QJsonObject &message)
{
    QJsonDocument doc(message);
    m_socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

/*!
    Deserialize the stringified JSON messageData and emit messageReceived.
    反序列化经过字符串化的JSON消息数据并发出接收到的消息。
*/
void WebSocketTransport::textMessageReceived(const QString &messageData)
{
    QJsonParseError error;
    QJsonDocument message = QJsonDocument::fromJson(messageData.toUtf8(), &error);
    if (error.error) {
        qWarning() << tr(u8"无法将文本消息解析为JSON对象:") << messageData
                   << "Error is:" << error.errorString();
        return;
    } else if (!message.isObject()) {
        qWarning() << tr(u8"接收到的消息不是JSON对象: ") << messageData;
        return;
    }
    emit messageReceived(message.object(), this);//当接受到信息时必须发射
}

QT_END_NAMESPACE
