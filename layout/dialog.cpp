#include <QtWidgets>

#include "dialog.h"

Dialog::Dialog()
{
    createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("Comments and specification for current run"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Face recognition app"));
}

void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Settings"));
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(tr("Option %1").arg(i + 1));
        layout->addWidget(buttons[i]);
    }
    horizontalGroupBox->setLayout(layout);
}

void Dialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Paths"));
    QGridLayout *layout = new QGridLayout;

    labels[0] = new QLabel(tr("Path to test file:"));
    lineEdits[0] = new QLineEdit;
    layout->addWidget(labels[0], 1, 0);
    layout->addWidget(lineEdits[0], 1, 2);

    labels[1] = new QLabel(tr("Path to learning base:"));
    lineEdits[1] = new QLineEdit;
    layout->addWidget(labels[1], 2, 0);
    layout->addWidget(lineEdits[1], 2, 2);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void Dialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Other"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Save result: ")), new QCheckBox);
    layout->addRow(new QLabel(tr("Attempts:")), new QSpinBox);
    formGroupBox->setLayout(layout);
}
