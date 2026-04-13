/**************************************************************************
 *  Karlyriceditor - a lyrics editor and CD+G / video export for Karaoke  *
 *  songs.                                                                *
 *  Copyright (C) 2009-2013 George Yunaev, support@ulduzsoft.com          *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                   *
 *																	      *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 **************************************************************************/

#include <QPainter>
#include <QImage>

#include "lyricswidget.h"
#include "testwindow.h"
#include "settings.h"
#include "textrenderer.h"
#include "cdgrenderer.h"
#include "project.h"

static const unsigned int PADDING_X = 10;
static const unsigned int PADDING_Y = 8;

static int effectiveProjectFontSize( TextRenderer * renderer, const Project * project )
{
    int mode = project->tag( Project::Tag_Video_FontSizeMode, "0" ).toInt();
    int manualSize = qMax( 1, project->tag( Project::Tag_Video_fontsize, QString::number( pSettings->m_previewFontSize ) ).toInt() );

    if ( mode == 0 )
        return manualSize;

    int percent = qBound( 40, project->tag( Project::Tag_Video_FontSizePercent, "100" ).toInt(), 100 );
    QFont baseFont( project->tag( Project::Tag_Video_font, pSettings->m_previewFontFamily ) );
    int maxSize = renderer->autodetectFontSize( QSize( 720, 480 ), baseFont );

    return qMax( 1, ( maxSize * percent ) / 100 );
}

LyricsWidget::LyricsWidget( QWidget *parent )
	: QWidget(parent)
{
	m_renderer = 0;
	m_lastImage = QImage( 720, 480, QImage::Format_ARGB32 );
}

LyricsWidget::~LyricsWidget()
{
	delete m_renderer;
}

QSize LyricsWidget::sizeHint () const
{
	return minimumSizeHint();
}

QSizePolicy	LyricsWidget::sizePolicy() const
{
	return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

QSize LyricsWidget::minimumSizeHint() const
{
	return QSize( m_lastImage.width() + 2 * PADDING_X, m_lastImage.height() + 2 * PADDING_Y );
}

void LyricsWidget::paintEvent( QPaintEvent * )
{
	QPainter p( this );

	p.fillRect( QRect( 0, 0, width() - 1, height() - 1 ), Qt::black );

	int x = (width() - m_lastImage.width()) / 2;
	int y = (height() - m_lastImage.height() ) / 2;
	p.drawImage( x, y, m_lastImage );
}

void LyricsWidget::setLyrics( const Lyrics& lyrics, const QString& artist, const QString& title, const Project * project )
{
	TextRenderer * re = new TextRenderer( 720, 480 );

    if ( project )
    {
        re->setLayoutMode( (TextRenderer::LayoutMode) project->tag( Project::Tag_Video_LayoutMode, QString::number( pSettings->m_previewLayoutMode ) ).toInt() );
        re->setDefaultVerticalAlign( (TextRenderer::VerticalAlignment) project->tag( Project::Tag_Video_TextAlignVertical, QString::number( TextRenderer::VerticalBottom ) ).toInt() );
    }
    else
    {
        re->setLayoutMode( (TextRenderer::LayoutMode) pSettings->m_previewLayoutMode );
        re->setDefaultVerticalAlign( TextRenderer::VerticalBottom );
    }

	re->setLyrics( lyrics );

    if ( project )
    {
        re->setRenderFont( QFont( project->tag( Project::Tag_Video_font, pSettings->m_previewFontFamily ),
                                  effectiveProjectFontSize( re, project ) ) );
        re->setColorBackground( QColor( project->tag( Project::Tag_Video_bgcolor, pSettings->m_previewBackground.name() ) ) );
        re->setColorTitle( QColor( project->tag( Project::Tag_Video_infocolor, QColor( Qt::white ).name() ) ) );
        re->setColorSang( QColor( project->tag( Project::Tag_Video_inactivecolor, pSettings->m_previewTextInactive.name() ) ) );
        re->setColorToSing( QColor( project->tag( Project::Tag_Video_activecolor, pSettings->m_previewTextActive.name() ) ) );
    }

	re->setPreambleData( 5, 5000, 10 );

	if ( !artist.isEmpty() && !title.isEmpty() )
		re->setTitlePageData( artist, title, "", 5000 );

	m_renderer = re;

	updateGeometry();
	update();
}

void LyricsWidget::setCDGdata( const QByteArray& cdgdata )
{
	CDGRenderer * re = new CDGRenderer();
	re->setCDGdata( cdgdata );
	m_renderer = re;

	updateGeometry();
	update();
}

void LyricsWidget::updateLyrics( qint64 tickmark )
{
	if ( isHidden() || !m_renderer )
		return;

	int status = m_renderer->update( tickmark );

	if ( status == LyricsRenderer::UPDATE_NOCHANGE )
		return;

	m_lastImage = m_renderer->image();

	if ( status == LyricsRenderer::UPDATE_RESIZED )
		updateGeometry();

	update();
}
