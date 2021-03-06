/* Copyright (c) 2012, 2013  BlackBerry Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "TrackManager.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>

#include <QLocale>
#include <QTranslator>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "dictaphone_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

//! [0]
    // Load the UI description from main.qml
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(&app);

    // Make the TrackManager object available to the UI as context property
    qml->setContextProperty("_trackManager", new TrackManager(&app));
//! [0]

    // Create the application scene
    AbstractPane *appPage = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(appPage);

    return Application::exec();
}
