/**************************************************************************
 *  Karlyriceditor - a lyrics editor and CD+G / video export for Karaoke  *
 *  songs.                                                                *
 *  Copyright (C) 2009-2013 George Yunaev, support@ulduzsoft.com          *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                   *
 *																	      *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 **************************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(resources);
	
	QApplication app(argc, argv);
    QTranslator appTranslator;

	QCoreApplication::setOrganizationName("karlyriceditor.com");
	QCoreApplication::setOrganizationDomain("karlyriceditor.com");
	QCoreApplication::setApplicationName("karlyriceditor");

    QString translationsDir = QDir( QCoreApplication::applicationDirPath() ).absoluteFilePath( "../ts" );
    QString locale = QLocale::system().name().toLower();
    QString language = QLocale::system().name().section( '_', 0, 0 ).toLower();

    if ( appTranslator.load( QString("karlyriceditor_%1.qm").arg( locale ), translationsDir )
         || appTranslator.load( QString("karlyriceditor_%1.qm").arg( language ), translationsDir ) )
    {
        app.installTranslator( &appTranslator );
    }

	MainWindow wnd;
	wnd.show();

    app.exec();
    return 0;
}
