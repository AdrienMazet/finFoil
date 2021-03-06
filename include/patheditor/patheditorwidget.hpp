/****************************************************************************
  
 Copyright (c) 2013, Hans Robeers
 All rights reserved.
 
 BSD 2-Clause License
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
   * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   
   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
   
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
****************************************************************************/

#ifndef PATHEDITORWIDGET_HPP
#define PATHEDITORWIDGET_HPP

#include "patheditor/fwd/patheditorfwd.hpp"
#include "hrlib/fwd/qtfwd.hpp"

#include <QWidget>
#include <memory>
#include <QFlags>

namespace patheditor
{
    struct Features
    {
        enum e
        {
            None = 0x0,
            HorizontalAxis = 0x1,
            VerticalAxis = 0x2,
            DragImageHereText = 0x4
        };
    };

    class PathEditorWidget : public QWidget
    {
        Q_OBJECT
    public:
        explicit PathEditorWidget(QWidget *parent = 0);

        /**
         * Returns a pointer to the QGraphicsScene used in this PathEditorWidget
         */
        QGraphicsScene* scene();

        /**
         * Adds an EditablePath object to this widget.
         * This widget takes ownership of the item.
         *
         * @param path The EditablePath to add
         */
        void addPath(EditablePath *path);
        void addGraphicsItem(QGraphicsItem *item);

        void clear();

        /**
         * Enables a specific feature
         *
         * @param features to enable
         */
        void enableFeatures(QFlags<Features::e> features);

        /**
         * Returns a Restrictor that can be used to pin PathPoints to the origin
         */
        std::shared_ptr<Restrictor> originRestrictor();
        /**
         * Returns a Restrictor that can be used to pin PathPoints to the horizontal axis
         */
        std::shared_ptr<Restrictor> horizontalAxisRestrictor();
        /**
         * Returns a Restrictor that can be used to pin PathPoints to the vertical axis
         */
        std::shared_ptr<Restrictor> verticalAxisRestrictor();

        void setImage(const QString &path);

        virtual ~PathEditorWidget() {}

    signals:
        void pathChange(Path *path);

    public slots:
        void setGridUnitSize(qreal pxPerUnit);
        void onPointRemove(PathPoint *toRemove, EditablePath *sender);
        void onPointSplit(PathPoint *toSplit, EditablePath *sender);
        void onPointPathTypeToggle(PathPoint* toToggle, EditablePath* sender);
        void onZoomIn();
        void onZoomOut();

    private slots:
        void onSceneRectChanged ( const QRectF & rect );

    private:
        PathEditorView* _view;
        QGraphicsScene* _scene;
        QVBoxLayout* _mainLayout;

        // Features
        QFlags<Features::e> _enabledFeatures;
        QGraphicsLineItem* _horizontalAxis;
        QGraphicsLineItem* _verticalAxis;

        // Restrictors
        std::shared_ptr<Restrictor> _originRestrictor;
        std::shared_ptr<Restrictor> _horizontalAxisRestrictor;
        std::shared_ptr<Restrictor> _verticalAxisRestrictor;
    };
}

#endif // PATHEDITORWIDGET_HPP
