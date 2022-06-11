#ifndef COLOURSELECTOR_H
#define COLOURSELECTOR_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QStandardItem>
#include "paletteretriever.h"

/*
 * menu widget that displays a selection of pen colours
 */
class ColourSelector : public QMenu {
    Q_OBJECT
public:
    /*
     * EFFECTS:     constructor
     *              sets up colour menu with default colours
     */
    ColourSelector(QWidget *parent = nullptr);

    /*
     * EFFECTS:     destructor
     */
    ~ColourSelector();

public slots:
    /*
     * MODIFIES:    this
     * EFFECTS:     creates a list of colours by calculating the inverse of all the colours in palette
     *              calls updateMenu with this list of inverse colours
     */
    void setPalette(QVector<QColor> palette);

    /*
     * REQUIRES:    imgItem is not null
     * MODIFIES:    this
     * EFFECTS:     takes the original screenshot from imgItem and sets the current colour menu to the inverse of the main colours of the screenshot
     *              adds a maximum of 5 colours to the default menu colour(s)
     */
    void extractColours(QStandardItem* imgItem);

    /*
     * REQUIRES:    action is a key in actionToColour
     * EFFECTS:     emits colourSelected signal with the associated value of action in the actionToColour hashmap
     */
    void emitColourChange(QAction *action);

signals:
    void colourSelected(QColor c);

private:
    QHash<QAction*, QColor> actionToColour;
    QHash<QStandardItem*, QVector<QColor>*> itemToPalette;
    QStandardItem* currImgItem;
    PaletteRetriever* retriever;

    /*
     * MODIFIES:    this
     * EFFECTS:     sets up colour menu with default colours and the given list of colours
     */
    void updateMenu(QVector<QColor> coloursToAdd);
};

#endif // COLOURSELECTOR_H
