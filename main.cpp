#include <QApplication>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QProcess>
#include <QTextEdit>
#include <QPushButton>
#include <QTimer>

class RunApp : public QWidget {
    Q_OBJECT

public:
    RunApp() {
        auto *layout = new QVBoxLayout(this);
        input = new QLineEdit(this);
        input->setPlaceholderText("command: (ex: kwrite, kcalc...)");
        layout->addWidget(input);

        process = new QProcess(this);
        connect(input, &QLineEdit::returnPressed, this, &RunApp::runCommand);
    }

private slots:
   void runCommand() {
        QString cmd = input->text();
        if (cmd.isEmpty()) return;
        input->clear();

        if (cmd == "exit") { QApplication::quit(); return; }

        bool ok = QProcess::startDetached("bash", QStringList() << "-c" << cmd);
        if (!ok) {
            qDebug() << Q_FUNC_INFO << cmd;
        }
        QApplication::quit();
    }

private:
    QLineEdit *input;
    QProcess *process;
};

#include "main.moc" //by QT moc \0/


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RunApp window;
    window.resize(300, 60);
    window.setWindowTitle("Runix");
    window.show();
    QTimer::singleShot(0, [&window]() {
    window.move(100, 100);
});

    return app.exec();
}
