#ifndef _ONELINECALC_H__INCLUDED_
#define _ONELINECALC_H__INCLUDED_

#include <plasma/applet.h>
#include <plasma/widgets/lineedit.h>

class QScriptEngine;
class ConfigDialog;

class PlasmaOneLineCalculator : public Plasma::Applet
{
	Q_OBJECT
public:
	PlasmaOneLineCalculator(QObject *parent, const QVariantList &args);
	~PlasmaOneLineCalculator();
 
	void paintInterface(QPainter *painter, const QStyleOptionGraphicsItem *option, const QRect& contentsRect); // The paintInterface procedure paints the applet to scree
	void init();
	
	void loadConfig();
	void saveConfig();
	
	void showConfigurationInterface();
public:
	QString initScript;

public slots:
	void lineEditReturnPressed();
	void settingsChanged();
 
private:
	Plasma::LineEdit lineEdit;
	QScriptEngine * scriptEngine;
	ConfigDialog * configDialog;
};

#endif//_ONELINECALC_H__INCLUDED_
