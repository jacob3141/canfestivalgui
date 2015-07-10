/****************************************************************************
** Form interface generated from reading ui file './processvargui.ui'
**
** Created: Tue Jun 18 15:38:59 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef PROCESSVARGUIFORM_H
#define PROCESSVARGUIFORM_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QGroupBox;
class QLabel;
class QPushButton;
class QSpinBox;
class QTable;

class ProcessVarGui : public QDialog
{ 
    Q_OBJECT

public:
    ProcessVarGui( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ProcessVarGui();

    QLabel* TextLabel4;
    QSpinBox* canopenPVarViewIdentifier;
    QGroupBox* GroupBox6;
    QTable* txTable;
    QTable* rxTable;
    QLabel* TextLabel5;
    QLabel* TextLabel6;
    QPushButton* PushButton1;

public slots:
    virtual void canopenIdChanged( );

};

#endif // PROCESSVARGUIFORM_H
