#ifndef DRAW_WIDGET_H_
#define DRAW_WIDGET_H_

#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QWidget>

namespace Ui
{
class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    DrawWidget(QWidget*);     // constructor
    ~DrawWidget() = default;  // destructor
    int    penWidth = 5;
    QColor penColour = Qt::black;

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;

private:
    void drawLine(QPoint, QPoint);
    void clearImage();
    void resizeImage(QImage*, const QSize&);

    bool   drawing = false;  // if user is drawing
    QPoint lastPoint;        // last point, to draw smooth lines
    QImage image;            // image being drawn
};
}  // namespace Ui

#endif  // DRAW_WIDGET_H_
