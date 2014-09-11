#ifndef CZY_QTAPP_H
#define CZY_QTAPP_H
#include <Qt>
#include <QApplication>
#include <QString>
#include <algorithm>

namespace czy{
    namespace QtApp{
		class QWaitCursor
		{
		public:
			QWaitCursor()
			{
				 QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
			}
			~QWaitCursor()
			{
				QApplication::restoreOverrideCursor();
			}
			void setWaitCursor()
			{
				QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
			}
			void setCursor(QCursor cur = QCursor(Qt::WaitCursor))
			{
				QApplication::setOverrideCursor(cur);
			}
			void release()
			{
				QApplication::restoreOverrideCursor();
			}
		};
	
		/// 
		/// \brief 字符串扩展
		class StringEx
		{
		public:
			StringEx(){}
			~StringEx(){}
			static bool is_match_string(const QString& str,const QStringList& key)
			{
				for (auto ite = key.begin();ite != key.end();++ite)
				{
					if (str.contains(*ite))
						return true;
				}
				return false;
			}
		};
	}
}

#endif // QWAITCURSOR_H
