#include "configdialog.h"
#include "onelinecalc.h"

ConfigDialog::ConfigDialog(PlasmaOneLineCalculator * calc) 
	: calc( calc ) 
{
	QWidget * widget = new QWidget( this );
	setupUi( widget );
	
	setCaption( "OneLineCalculator Preferences" );
  	setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Apply );
	setMainWidget( widget );
	
 	connect( this, SIGNAL( buttonClicked( KDialog::ButtonCode ) ), this, SLOT( buttonClicked( KDialog::ButtonCode ) ) );
	
	kcm_InitScript->setPlainText( calc->initScript );
}

ConfigDialog::~ConfigDialog() {	
}

void ConfigDialog::save() {
	calc->initScript = kcm_InitScript->toPlainText();
	calc->saveConfig();
	calc->settingsChanged();
}

void ConfigDialog::buttonClicked( KDialog::ButtonCode button ) {
	switch( button ) {
	case KDialog::Ok:
      		save();
	case KDialog::Cancel:
		hide();
		break;
	case KDialog::Apply:
		save();
		break;
	default:
		break;
	}
}
