#ifndef COLOURSELECTOR_H
#define COLOURSELECTOR_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QStandardItem>

class ColourSelector : public QMenu
{
    Q_OBJECT
public:
    ColourSelector(QWidget *parent = nullptr);

    //void extractColours(QPixmap* img);

public slots:
    void setPalette(QVector<QColor>);
    void extractColours(QStandardItem* imgItem);
    void emitColourChange(QAction *action);

signals:
    void colourSelected(QColor c);

private:
    QHash<QAction*, QColor> actionToColour;
    QHash<QStandardItem*, QVector<QColor>*> itemToPalette;
    QStandardItem* currImgItem;

    void updateMenu(QVector<QColor> coloursToAdd);
};

#endif // COLOURSELECTOR_H
