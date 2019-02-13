#include "MediaConverter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// arg-1 : media-in full path
	// arg-2 : media-in password
	// arg-3 : madia-out full path
	// arg-4 : media-out password
	// arg-5 : -silent?
	MediaConverter w(
		argc > 1 ? argv[1] : QString(),
		argc > 2 ? argv[2] : QString(), 
		argc > 3 ? argv[3] : QString(), 
		argc > 4 ? argv[4] : QString(),
		argc > 5 ? argv[5] == "-silent" : false
	);
	w.show();

	return a.exec();
}