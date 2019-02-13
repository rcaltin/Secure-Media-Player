#include "MediaConverter.h"
#include "CryptographyManager.h"
#include "MediaFileFactory.h"
#include "MediaFileConverter.h"
#include <QMessageBox>
#include <QFileDialog>

using namespace SecureMediaPlayerLib;

MediaConverter::MediaConverter(
	QString mediaFileIn, 
	QString mediaPasswordIn, 
	QString mediaFileOut, 
	QString mediaPasswordOut, 
	bool startSilent, 
	QWidget *parent
)
	: QMainWindow(parent), m_conversionThread(nullptr), m_silentMode(startSilent)
{
	ui.setupUi(this);

	ui.progressBar_progress->setVisible(false);
	ui.pushButton_startCancel->setEnabled(true);

	ui.lineEdit_browseIn->setText(mediaFileIn);
	ui.lineEdit_browseOut->setText(mediaFileOut);
	ui.lineEdit_passwordIn->setText(mediaPasswordIn);
	ui.lineEdit_passwordOut->setText(mediaPasswordOut);
	ui.lineEdit_passwordValidationOut->setText(mediaPasswordOut);

	if (m_silentMode)
	{
		this->hide();
		on_pushButton_startCancel_clicked();
	}
}

MediaConverter::~MediaConverter()
{
	if (m_conversionThread)
	{
		m_conversionThread->requestInterruption();
		m_conversionThread->wait();
	}
}

void MediaConverter::on_pushButton_browseIn_clicked()
{
	ui.lineEdit_passwordIn->clear();

	ui.lineEdit_browseIn->setText(QFileDialog::getOpenFileName(this, "Open Media File", ui.lineEdit_browseIn->text()));

	ui.lineEdit_passwordIn->setEnabled(ui.lineEdit_browseIn->text().endsWith(MEDIA_FILE_EXTENSION));
}

void MediaConverter::on_pushButton_browseOut_clicked()
{
	ui.lineEdit_passwordIn->clear();
	ui.lineEdit_passwordValidationOut->clear();

	ui.lineEdit_browseOut->setText(QFileDialog::getSaveFileName(this, "Save Media File", ui.lineEdit_browseOut->text()));
	
	bool pwEn = ui.lineEdit_browseOut->text().endsWith(MEDIA_FILE_EXTENSION);
	ui.lineEdit_passwordOut->setEnabled(pwEn);
	ui.lineEdit_passwordValidationOut->setEnabled(pwEn);	
}

void MediaConverter::on_pushButton_startCancel_clicked()
{
	if (!m_conversionThread)
	{
		// check pw validation
		if (ui.lineEdit_passwordOut->text() != ui.lineEdit_passwordValidationOut->text())
		{
			QMessageBox::critical(this, tr("Error"), tr("Output media file password and its validation are not same."));
			return;
		}
		else if (ui.lineEdit_passwordOut->text().isEmpty())
		{
			QMessageBox::critical(this, tr("Error"), tr("Output media file password cannot be empty."));
			return;
		}

		// media file reader
		MediaFileReader * mr = MediaFileFactory::createMediaFileReader(ui.lineEdit_browseIn->text());
		if (mr->isSecureMedia())
			static_cast<EncryptedMediaFileReader *>(mr)->setMediaPasswordHash(CryptographyManager::SHA3_256(ui.lineEdit_passwordIn->text()));
		
		// media file writer
		MediaFileWriter * mw = MediaFileFactory::createMediaFileWriter(ui.lineEdit_browseOut->text());
		if (mw->isSecureMedia())
			static_cast<EncryptedMediaFileWriter *>(mw)->setMediaPasswordHash(CryptographyManager::SHA3_256(ui.lineEdit_passwordOut->text()));

		// converter
		m_conversionThread = new QThread();
		MediaFileConverter * mc = new MediaFileConverter(mr, mw, true);
		mc->moveToThread(m_conversionThread);
		connect(m_conversionThread, SIGNAL(started()), mc, SLOT(process()));
		connect(m_conversionThread, SIGNAL(finished()), m_conversionThread, SLOT(deleteLater()));
		connect(m_conversionThread, SIGNAL(destroyed()), this, SLOT(conversionThreadDestroyed()));
		connect(mc, SIGNAL(finished()), m_conversionThread, SLOT(quit()));
		connect(mc, SIGNAL(finished()), mc, SLOT(deleteLater()));
		connect(mc, SIGNAL(mediaConversionStarted()), this, SLOT(converter_mediaConversionStarted()));
		connect(mc, SIGNAL(mediaConversionProgress(float)), this, SLOT(converter_mediaConversionProgress(float)));
		connect(mc, SIGNAL(mediaConversionFinished(bool)), this, SLOT(converter_mediaConversionFinished(bool)));
		connect(mc, SIGNAL(mediaConversionError(QString)), this, SLOT(converter_mediaConversionError(QString)));
		m_conversionThread->start();
	}
	else
	{
		m_conversionThread->requestInterruption();
	}
}

void MediaConverter::converter_mediaConversionStarted()
{
	ui.pushButton_startCancel->setText(tr("Cancel"));
	ui.progressBar_progress->setVisible(true);
}

void MediaConverter::converter_mediaConversionProgress(float percent)
{
	ui.progressBar_progress->setValue((int)percent);
}

void MediaConverter::converter_mediaConversionFinished(bool succesful)
{
	ui.pushButton_startCancel->setText("Start");

	if (succesful)
	{
		if (m_silentMode)
			qApp->exit();
		else
			QMessageBox::information(this, tr("Completed"), tr("Media conversion succeed."));
	}
	ui.progressBar_progress->setVisible(false);
}

void MediaConverter::converter_mediaConversionError(QString errorMessage)
{
	ui.pushButton_startCancel->setText(tr("Start"));

	if(!m_silentMode)
		QMessageBox::critical(this, tr("Error"), errorMessage);

	ui.progressBar_progress->setVisible(false);
}

void MediaConverter::conversionThreadDestroyed()
{
	m_conversionThread = nullptr;
}
