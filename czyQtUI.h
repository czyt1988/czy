#ifndef CZYQTUI_H
#define CZYQTUI_H

#include <QStandardItemModel>
#include <functional>
#include <QDialog>
#include <QMainWindow>
#include <QLabel>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

#include <limits>
namespace czy{
	namespace QtUI
	{
		class StandardItemModel
		{
		public:
			StandardItemModel(){}
			~StandardItemModel(){}
			typedef std::function<void(QStandardItem*)> callback_ergodicFun_ptr;
			//typedef void(*callback_ergodicFun_ptr)(QStandardItem*);
			static void ergodicAllItem(QStandardItemModel* model,callback_ergodicFun_ptr pFun);
			static void ergodicItem(QStandardItem* item,callback_ergodicFun_ptr pFun);
		private:
		};

		class NumberInputDialog:public QDialog{
		public:
			NumberInputDialog(QWidget* par = nullptr):QDialog(par){
                if (objectName().isEmpty())
                            setObjectName(QStringLiteral("NumberInputDialog"));
                resize(335, 97);
				horizontalLayout1 = new QHBoxLayout();
				horizontalLayout1->setSpacing(6);
				horizontalLayout1->setContentsMargins(11, 11, 11, 11);
				horizontalLayout1->setObjectName(QStringLiteral("horizontalLayout1"));
				label_front = new QLabel(this);
				label_front->setObjectName(QStringLiteral(""));

				doubleSpinBox = new QDoubleSpinBox(this);
				doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
				QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
				sizePolicy.setHorizontalStretch(0);
				sizePolicy.setVerticalStretch(0);
				sizePolicy.setHeightForWidth(doubleSpinBox->sizePolicy().hasHeightForWidth());
				doubleSpinBox->setSizePolicy(sizePolicy);

				label_back = new QLabel(this);
				label_back->setObjectName(QStringLiteral("label_back"));

				

				horizontalLayout2 = new QHBoxLayout();
				horizontalLayout2->setSpacing(6);
				horizontalLayout2->setObjectName(QStringLiteral("horizontalLayout2"));
				pushButtonOk = new QPushButton(this);
				pushButtonOk->setObjectName(QStringLiteral("pushButtonOk"));
				pushButtonOk->setText(QStringLiteral("确定"));
				pushButtonCannel = new QPushButton(this);
				pushButtonCannel->setObjectName(QStringLiteral("pushButtonCannel"));
				pushButtonCannel->setText(QStringLiteral("取消"));

				horizontalLayout1->addWidget(label_front);
				horizontalLayout1->addWidget(doubleSpinBox);
				horizontalLayout1->addWidget(label_back);
				horizontalLayout2->addWidget(pushButtonOk);
				horizontalLayout2->addWidget(pushButtonCannel);

				verticalLayout = new QVBoxLayout(this);
				verticalLayout->setSpacing(6);
				verticalLayout->setContentsMargins(11, 11, 11, 11);
				verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
				verticalLayout->addLayout(horizontalLayout1);
				verticalLayout->addLayout(horizontalLayout2);



//                doubleSpinBox->setMaximum(DBL_MAX);
//                doubleSpinBox->setMinimum(DBL_MIN);
				connect(pushButtonOk,&QAbstractButton::clicked,this,&QDialog::accept);
				connect(pushButtonCannel,&QAbstractButton::clicked,this,&QDialog::reject);
                resize(335, 97);
			}
			~NumberInputDialog(){}
			double getInputData(){return doubleSpinBox->value();}
			void setDefaultValue(double val){doubleSpinBox->setValue(val);}
			void setMaximum(double max){doubleSpinBox->setMaximum(max);}
			void setMinimum(double min){doubleSpinBox->setMinimum(min);}
			void setSingleStep(double val){doubleSpinBox->setSingleStep(val);}
			void setFrontText(const QString& text){label_front->setText(text);}
			void setBackText(const QString& text){label_back->setText(text);}
			QString frontText(){return label_front->text();}
			QString backText(){return label_back->text();}
		private:
			QLabel* label_front;
			QLabel* label_back;
			QDoubleSpinBox *doubleSpinBox;
			QHBoxLayout *horizontalLayout1;
			QHBoxLayout *horizontalLayout2;
			QVBoxLayout *verticalLayout;
			QPushButton *pushButtonOk;
			QPushButton *pushButtonCannel;
		};

		class MainWindowEx : public QMainWindow{
			Q_OBJECT
		public:
			explicit MainWindowEx(QWidget *parent = 0):QMainWindow(parent){}
			~MainWindowEx(){}
		signals:
			//! Emitted when the window was closed
			void closingWindow(MainWindowEx* wnd);
			void closedWindow(MainWindowEx* wnd);
		protected:
			void closeEvent( QCloseEvent *e)
			{
				emit closingWindow(this);
				QMainWindow::closeEvent(e);
				emit closedWindow(this);
			}
		};
	}
}


#endif // CZYQTUI_H
