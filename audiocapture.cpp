#include "audiocapture.h"

static const int MAX_SECONDS = 600;

AudioCapturer::AudioCapturer(QWidget* parent)
    :QWidget(parent)
{
    _recorder = new QAudioRecorder;
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/vorbis");
    audioSettings.setQuality(QMultimedia::HighQuality);
    _recorder->setContainerFormat("ogg");
    _recorder->setEncodingSettings(audioSettings);
    connect(_recorder, &QAudioRecorder::durationChanged, 
            this, &AudioCapturer::onDurationUpdated);
    qDebug() << _recorder->supportedAudioCodecs();
    qDebug() << _recorder->audioInputs();
    qDebug() << _recorder->supportedContainers();

    _pbRecord = new QPushButton(tr("Start &Record"));
    connect(_pbRecord, &QPushButton::clicked, this, &AudioCapturer::buttonClicked);

    _progress = new QProgressBar;
    // range in seconds
    _progress->setRange(0, MAX_SECONDS);
    _progress->setFormat("recording %v seconds");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_pbRecord);
    layout->addWidget(_progress);

    this->setMinimumWidth(400);
    this->setLayout(layout);
}

void AudioCapturer::buttonClicked()
{
    if (_state == Stopped) {
        startRecording();
    } else {
        stopRecording();
    }
}


void AudioCapturer::startRecording()
{
    qDebug() << __PRETTY_FUNCTION__;
    _tmpAudioFile = "/tmp/irecorder_clip01.mkv";
    QFile f(_tmpAudioFile);
    f.open(QIODevice::WriteOnly|QIODevice::Truncate);
    f.close();
    if (!_recorder->setOutputLocation(_tmpAudioFile)) {
        qDebug() << _recorder->errorString();
        return;
    }
    _recorder->record();
    _pbRecord->setText(tr("Stop &Recording"));
    _state = Recording;
}

void AudioCapturer::stopRecording()
{
    qDebug() << __PRETTY_FUNCTION__;
    //popup dialog to save it
    _recorder->stop();
    _state = Stopped;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Recording"),
            QDir::homePath(), tr("Audio (*.*)"));
    if (!fileName.isEmpty()) {
        qDebug() << "save to " << fileName;
        QFile::copy(_tmpAudioFile, fileName);
    }
    
    _pbRecord->setText(tr("&Start Recording"));
    _progress->setValue(0);
}

void AudioCapturer::onDurationUpdated(qint64 val)
{
    qDebug() << "elapsed: " << val / 1000.0f; 
    _progress->setValue(val / 1000);
    if (val / 1000 > MAX_SECONDS) {
        _pbRecord->click();
    }
}
