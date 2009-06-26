#include "onelinecalc.h"
#include "configdialog.h"

#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QScriptEngine>
 
#include <plasma/svg.h>
#include <plasma/theme.h>
#include <plasma/containment.h>

static QString defaultInitScript = "var abs = Math.abs;\nvar acos = Math.acos;\nvar asin = Math.asin;\nvar atan = Math.atan;\nvar atan2 = Math.atan2;\nvar ceil = Math.ceil;\nvar cos = Math.cos;\nvar\nexp = Math.exp;\nvar floor = Math.floor;\nvar log = Math.log;\nvar max = Math.max;\nvar min = Math.min;\nvar pow = Math.pow;\nvar random = Math.random;\nvar round = Math.round;\nvar sin = Math.sin;\nvar sqrt = Math.sqrt;\nvar tan = Math.tan;\nfunction cool(x) { return x * 12 }";

K_EXPORT_PLASMA_APPLET(onelinecalc, PlasmaOneLineCalculator) // This is the command that links your applet to the .desktop file
 
PlasmaOneLineCalculator::PlasmaOneLineCalculator(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args), lineEdit( this ), scriptEngine( new QScriptEngine( this ) ), configDialog( 0 )
{
	loadConfig();	
	settingsChanged();
	
	setHasConfigurationInterface(true);
	setBackgroundHints(DefaultBackground);
	resize(300, 50);

	connect( &lineEdit, SIGNAL( returnPressed() ), this, SLOT( lineEditReturnPressed() ) );
}

PlasmaOneLineCalculator::~PlasmaOneLineCalculator() {
	if ( configDialog )
		delete configDialog;
}

void PlasmaOneLineCalculator::loadConfig() {
	KConfigGroup cfg = config();
	
	initScript = cfg.readEntry( "InitScript", defaultInitScript );
}

void PlasmaOneLineCalculator::saveConfig() {
	KConfigGroup cfg = config();
	
	cfg.writeEntry( "InitScript", initScript );
}

void PlasmaOneLineCalculator::init() {
}

void PlasmaOneLineCalculator::showConfigurationInterface() {
	if ( !configDialog )
		configDialog = new ConfigDialog( this );
		
	configDialog->show();
}

void PlasmaOneLineCalculator::settingsChanged() {
	scriptEngine->popContext();
	scriptEngine->pushContext();	

	QScriptValue result = scriptEngine->evaluate( initScript );

	if ( scriptEngine->hasUncaughtException() ) {
		lineEdit.setText( result.toString() );
	}
}

void PlasmaOneLineCalculator::lineEditReturnPressed() {
	lineEdit.setText( scriptEngine->evaluate( lineEdit.text() ).toString() );
}

void PlasmaOneLineCalculator::paintInterface(QPainter *p, const QStyleOptionGraphicsItem */*option*/, const QRect &contentsRect) {

	p->setRenderHint(QPainter::SmoothPixmapTransform);
	p->setRenderHint(QPainter::Antialiasing);

	if ( formFactor() == Plasma::Planar || formFactor() == Plasma::MediaCenter ) {
		const int textWidth = 70;

		p->save();
		p->setPen(Qt::white);
		p->drawText(contentsRect,Qt::AlignLeft | Qt::AlignVCenter,"Calculate:");
		p->restore();

		lineEdit.setGeometry(QRect(contentsRect.x() + textWidth,contentsRect.y(),contentsRect.width() - textWidth, contentsRect.height()));
	} else {
		lineEdit.setGeometry(contentsRect);
	}
}
 
