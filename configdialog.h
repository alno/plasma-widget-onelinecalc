#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "ui_preferences.h"

#include <KConfig>
#include <KConfigGroup>
#include <KDialog>

class PlasmaOneLineCalculator;

class ConfigDialog : public KDialog, public Ui::Preferences
{
Q_OBJECT
public:
	ConfigDialog(PlasmaOneLineCalculator * calc);
	~ConfigDialog();
	   
	void save();

private:
	PlasmaOneLineCalculator * calc;

private slots:
	void buttonClicked( KDialog::ButtonCode button );    
};

#endif
