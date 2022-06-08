#include "colourselector.h"
#include <iostream>
#include "paletteretriever.h"
#include <QColor>

ColourSelector::ColourSelector(QWidget *parent) : QMenu(parent) {
    setPalette(QVector<QColor>());

    QObject::connect(this, &QMenu::triggered,
                     this, &ColourSelector::emitColourChange);
}

void ColourSelector::emitColourChange(QAction *action) {
    emit colourSelected(actionToColour.value(action));
}

void ColourSelector::extractColours(QStandardItem* imgItem) {
    currImgItem = imgItem;

    if (itemToPalette.contains(imgItem)) {
        updateMenu(*itemToPalette.value(imgItem));
    } else {
        QPixmap* temp = new QPixmap(imgItem->data(Qt::UserRole).value<QPixmap>());
        PaletteRetriever *p = new PaletteRetriever(temp);
        p->generatePalette();
        QObject::connect(p, &PaletteRetriever::paletteReadyForUse,
                         this, &ColourSelector::setPalette);
        //!!!p leaks memory
        //!!!temp leaks memory
    }
}

void ColourSelector::setPalette(QVector<QColor> palette) {
    QVector<QColor> *newPalette = new QVector<QColor>();

    newPalette->append(QColor(Qt::blue));
    newPalette->append(QColor(Qt::red));

    for (QColor c : palette) {
        QColor inverse(255-c.red(), 255-c.green(), 255-c.blue());
        newPalette->append(inverse);
    }

    itemToPalette.insert(currImgItem,newPalette);
    updateMenu(*newPalette);
}

void ColourSelector::updateMenu(QVector<QColor> coloursToAdd) {
    this->clear();
    for (QColor c : coloursToAdd) {
        QAction *action = new QAction();
        QPixmap icon(10,10);
        icon.fill(c);
        action->setIcon(QIcon(QPixmap(icon)));
        actionToColour.insert(action,c);
        this->addAction(action);
    }
}
