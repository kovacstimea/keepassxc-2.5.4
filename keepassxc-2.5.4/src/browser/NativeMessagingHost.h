/*
 *  Copyright (C) 2017 Sami Vänttinen <sami.vanttinen@protonmail.com>
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NATIVEMESSAGINGHOST_H
#define NATIVEMESSAGINGHOST_H

#include "BrowserClients.h"
#include "BrowserService.h"
#include "NativeMessagingBase.h"
#include "gui/DatabaseTabWidget.h"

class NativeMessagingHost : public NativeMessagingBase
{
    Q_OBJECT

    typedef QList<QLocalSocket*> SocketList;

public:
    explicit NativeMessagingHost(DatabaseTabWidget* parent = nullptr, const bool enabled = false);
    ~NativeMessagingHost() override;
    int init();
    void run();
    void stop();

signals:
    void quit();

private:
    void readLength() override;
    bool readStdIn(const quint32 length) override;
    void sendReplyToAllClients(const QJsonObject& json);

private slots:
    void databaseLocked();
    void databaseUnlocked();
    void newLocalConnection();
    void newLocalMessage();
    void disconnectSocket();

private:
    QMutex m_mutex;
    BrowserService m_browserService;
    BrowserClients m_browserClients;
    QSharedPointer<QLocalServer> m_localServer;
    SocketList m_socketList;
};

#endif // NATIVEMESSAGINGHOST_H
