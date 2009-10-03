/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Håvard Tautra Knutsen <havtknut@tihlde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "config.h"
#include "shoutcastmodel.h"
#include "fileview.h"
#include "iconmanager.h"
#include "mpdcache.h"
#include "mpddirectory.h"
#include "mpdsonglist.h"
#include "shoutcastview.h"
#include <QMenu>

ShoutcastView::ShoutcastView(QWidget *parent) : AbstractTree(parent) {
	Q_ASSERT(m_menu);
	setObjectName("shoutcastview");
	setModel(m_model = new ShoutcastModel(this));
	m_model->refresh();

	// playlist m_menu
	m_enqueueAction = addMenuAction("enqueue", this, SLOT(enqueue()));
	m_playAction = addMenuAction("play", this, SLOT(play()));
	m_menu->addSeparator();
	m_rescanAction = addMenuAction("rescan", this, SLOT(rescan()));
	m_menu->addSeparator();
	m_informationAction = addMenuAction("information", this, SLOT(information()));

	connect(MPDCache::instance(), SIGNAL(directoriesUpdated(const MPDDirectory &)), this, SLOT(setRoot(const MPDDirectory &)));

	clearSelection();
}

void ShoutcastView::setFileView(FileView *fw) {
	m_fileView = fw;
}

void ShoutcastView::updateTranslation() {
	Q_ASSERT(m_enqueueAction);
	Q_ASSERT(m_informationAction);
	Q_ASSERT(m_rescanAction);
	Q_ASSERT(m_playAction);
	m_enqueueAction->setText(tr("&Enqueue"));
	m_informationAction->setText(tr("&Information..."));
	m_rescanAction->setText(tr("&Rescan directory"));
	m_playAction->setText(tr("&Play"));
}
