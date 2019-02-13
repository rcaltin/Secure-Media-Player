#include "MediaPlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	// arg-1 : media full path
	// arg-2 : password
	// arg-3 : subtitle full path

	MediaPlayer w(argc > 1 ? argv[1] : QString(), argc > 2 ? argv[2] : QString(), argc > 3 ? argv[3] : QString());
	w.show();

	return a.exec();
}