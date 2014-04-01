#ifndef _audio_capture_h
#define _audio_capture_h 

#include <QtWidgets>
#include <QtMultimedia>

class AudioCapturer: public QWidget
{
    Q_OBJECT
public:
    AudioCapturer(QWidget* parent = 0);

private:
    QAudioRecorder* _recorder;
    QPushButton* _pbRecord;
    QProgressBar* _progress;

    enum State {
        Stopped,
        Recording,
    };

    State _state {Stopped};
    QString _tmpAudioFile;

private slots:
    void buttonClicked();
    void startRecording();
    void stopRecording();
    void onDurationUpdated(qint64 val);
};

#endif
