#include "draw_widget.hpp"

#include <QPainter>

Ui::DrawWidget::DrawWidget(QWidget* parent) : QWidget(parent)
{
    // do not change contents on resize
    setAttribute(Qt::WA_StaticContents);
    drawing = false;
    penColour = Qt::black;
    penWidth = 4;
}

void Ui::DrawWidget::setPenColour(QColor newColour) { penColour = newColour; }

void Ui::DrawWidget::setPenWidth(int newWidth) { penWidth = newWidth; }

void Ui::DrawWidget::mousePressEvent(QMouseEvent* event)
{
    // if pressed left click
    if (event->button() == Qt::LeftButton) {
        // update position and show that user is drawing
        lastPoint = event->pos();
        drawing = true;
    }
}

void Ui::DrawWidget::mouseMoveEvent(QMouseEvent* event)
{
    // if left button is being held down and user is drawing
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        // draw line and update position
        drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
    }
}

void Ui::DrawWidget::mouseReleaseEvent(QMouseEvent* event)
{
    // if left button has been released
    if (event->button() == Qt::LeftButton && drawing) {
        // finish drawing
        drawLine(lastPoint, event->pos());
        drawing = false;
    }
}

void Ui::DrawWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect    dirtyRect = event->rect();  // where changes have occured
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void Ui::DrawWidget::resizeEvent(QResizeEvent* event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
}

void Ui::DrawWidget::drawLine(QPoint from, QPoint to)
{
    QPainter painter(&image);
    painter.setPen(     // settings for pen with which to draw
      QPen(penColour,   // line colour
        penWidth,       // line width
        Qt::SolidLine,  // solid line pattern
        Qt::RoundCap,   // how to end lines
        Qt::RoundJoin   // how to join lines
        ));
    painter.drawLine(from, to);
    // update screen to show this change
    int rad = (penWidth / 2) + 2;
    update(QRect(from, to).normalized().adjusted(-rad, -rad, rad, rad));
}

void Ui::DrawWidget::clearImage()
{
    image.fill(qRgb(255, 255, 255));  // fill image with white
    update();                         // update full image
}

void Ui::DrawWidget::resizeImage(QImage* image, const QSize& newSize)
{
    if (image->size() == newSize) return;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
