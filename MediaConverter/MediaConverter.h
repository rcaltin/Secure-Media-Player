/*
MediaConverter/MediaConverter.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QMainWindow>
#include <QThread>
#include "ui_MediaConverter.h"

class MediaConverter : public QMainWindow
{
	Q_OBJECT

public:
	MediaConverter(
		QString mediaFileIn = QString(),
		QString passwordIn = QString(),
		QString mediaFileOut = QString(),
		QString mediaPasswordOut = QString(),
		bool startSilent = false, 
		QWidget *parent = Q_NULLPTR
	);
	~MediaConverter();

private:
	Ui::MediaConverterClass ui;
	QThread * m_conversionThread;
	bool m_silentMode;

public slots:
	void on_pushButton_browseIn_clicked();
	void on_pushButton_browseOut_clicked();
	void on_pushButton_startCancel_clicked();

	void converter_mediaConversionStarted();
	void converter_mediaConversionProgress(float percent);
	void converter_mediaConversionFinished(bool succesful = true);
	void converter_mediaConversionError(QString errorMessage);
	void conversionThreadDestroyed();
};